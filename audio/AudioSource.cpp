#include "AudioSource.hpp"
#include "Debug.hpp"

#include <chrono>
#include <cstring>
#include <thread>

using namespace std::chrono_literals;

ALuint AudioSource::clearBuffer()
{
    ALuint buffer;
    alSourceUnqueueBuffers(AudioSource::source, 1, &buffer);
    return buffer;
}

void AudioSource::fillBuffer(ALuint* buffer)
{
    int bufferSizeBackup = bufferSize;
    uint64_t actualPos = AudioSource::audioFile->tell();
    if (actualPos + AudioSource::bufferSize > AudioSource::dataEndPos)
    {
        AudioSource::bufferSize = AudioSource::dataEndPos - actualPos;
    }

    audioFile->read(reinterpret_cast<uint8_t*>(AudioSource::bufferData), AudioSource::bufferSize);
    alBufferData(*buffer, AudioSource::format, AudioSource::bufferData,
                 AudioSource::bufferSize, AudioSource::sampleRate);
    alSourceQueueBuffers(AudioSource::source, 1, buffer);
    AudioSource::bufferSize = bufferSizeBackup;
}

AudioSource::AudioSource(FileInterface* audiofile) 
: audioFile(audiofile)
, bufferSize(176400)
, dataEndPos(0)
, dataStartPos(0)
, format(0)
, sampleRate(0)
, playing(false)
, paused(false)
, stopped(true)
{
    alGenSources(1, &(AudioSource::source));
    alGenBuffers(2, &(AudioSource::buffers[0])); 

    alSourcei(AudioSource::source, AL_LOOPING, AL_FALSE);
    
    if(!(AudioSource::audioFile->isOpen()))
    {
        Debug::print(Debug::Flags::Error, Debug::Subsystem::Sound,
            "The audio file must be open for reading.");
        return;
    }

    uint64_t fileSize = AudioSource::audioFile->getSize();
    uint8_t readChunks = 0;
    while(readChunks != 3 ||
          AudioSource::audioFile->tell() + sizeof(AudioSource::RiffHeader) < fileSize)
    {
        AudioSource::RiffHeader riffHeader;
        AudioSource::audioFile->read(reinterpret_cast<uint8_t*>(&riffHeader),
                                     sizeof(AudioSource::RiffHeader));

        if(!strncmp(reinterpret_cast<char*>(riffHeader.id), "RIFF", sizeof(riffHeader.id)))
        {
            char riffType[4];
            AudioSource::audioFile->read(reinterpret_cast<uint8_t*>(&riffType), sizeof(riffType));

            if(strncmp(reinterpret_cast<char*>(riffType), "WAVE", sizeof(riffType)))
            {
                Debug::print(Debug::Flags::Error, Debug::Subsystem::Sound,
                    "Invalid riff chunk: type parameter is not \"WAVE\"");
            }

            readChunks++;
        }
        else if(!strncmp(reinterpret_cast<char*>(riffHeader.id), "fmt ", sizeof(riffHeader.id))) 
        {
            AudioSource::FormatChunk formatChunk;
            AudioSource::audioFile->read(reinterpret_cast<uint8_t*>(&formatChunk),
                                         sizeof(AudioSource::FormatChunk));

            if(formatChunk.audioFormat != 0x0001) //Format is not PCM
            {
                Debug::print(Debug::Flags::Error, Debug::Subsystem::Sound,
                    "Invalid audio format: internal reader only supports uncompressed PCM");
            }

            AudioSource::sampleRate = formatChunk.sampleRate;

            bool stereo = (formatChunk.numChannels > 1);
            switch(formatChunk.bitsPerSample)
            {
                case 16:
                    AudioSource::format = stereo ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
                    break;
                case 8:
                    AudioSource::format = stereo ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8;
                    break;
                default:
                    AudioSource::format = -1;
                    break;
            }

            readChunks++;
        }
        else if(!strncmp(reinterpret_cast<char*>(riffHeader.id), "data", sizeof(riffHeader.id)))
        {
            AudioSource::dataStartPos = AudioSource::audioFile->tell();
            AudioSource::dataEndPos = AudioSource::audioFile->tell() + riffHeader.size;
            readChunks++;
        }
        else
        {
            AudioSource::audioFile->seek(riffHeader.size, FileInterface::Origin::Middle);
        }
    }

    AudioSource::bufferData = static_cast<char*>(std::malloc(AudioSource::bufferSize));
    AudioSource::audioFile->seek(AudioSource::dataStartPos, FileInterface::Origin::Begin);
}

AudioSource::~AudioSource()
{
    alDeleteBuffers(2, &(AudioSource::buffers[0]));
    alDeleteSources(1, &(AudioSource::source));
    std::free(AudioSource::bufferData);
}

void AudioSource::setPosition(float x,  float y, float z)
{
    ALfloat position[] = { x, y, z };
    alSourcefv(AudioSource::source, AL_POSITION, position);
}

void AudioSource::setVelocity(float x,  float y, float z)
{
    ALfloat velocity[] = { x, y, z };
    alSourcefv(AudioSource::source, AL_VELOCITY, velocity);
}

void AudioSource::setOrientation(float x,  float y, float z)
{
    ALfloat orientation[] = { x, y, z };
    alSourcefv(AudioSource::source, AL_ORIENTATION, orientation);
}

void AudioSource::play()
{
    if (AudioSource::stopped)
    {
        for(int i = 0; i < 2; i++)
        {
            AudioSource::fillBuffer(&(AudioSource::buffers[i]));
        }
    }

    alSourcePlay(AudioSource::source);

    AudioSource::playing = true;
    AudioSource::stopped = false;
    AudioSource::paused = false;
}
#include <iostream>

void AudioSource::updateBuffers()
{
    if (!(AudioSource::playing))
    {
        return;
    }

    if (AudioSource::audioFile->tell() >= AudioSource::dataEndPos)
    {
        return;
    }

    ALint processed;
    alGetSourcei(AudioSource::source, AL_BUFFERS_PROCESSED, &processed);
    while(processed--)
    {
        ALuint buffer = clearBuffer();
        fillBuffer(&buffer);
    }
}

void AudioSource::stop()
{
    AudioSource::audioFile->seek(AudioSource::dataStartPos, FileInterface::Origin::Begin);

    alSourceStop(AudioSource::source);

    for (int i = 0; i != 2; i++)
    {
        AudioSource::clearBuffer();
    }

    AudioSource::playing = false;
    AudioSource::stopped = true;
    AudioSource::paused = false;
}

void AudioSource::pause()
{
    alSourceStop(AudioSource::source);

    AudioSource::playing = false;
    AudioSource::stopped = false;
    AudioSource::paused = true;
}
