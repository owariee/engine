#include "AudioSource.hpp"
#include "Debug.hpp"
#include "WAV.hpp"
#include "fmt/core.h"
#include <cstdlib>
#include <cstring>
#include <thread>
#include <iostream>

using namespace std::chrono_literals;

void AudioSource::LoadWavData()
{
    if(!(audioFile->isOpen()))
    {
        Debug::print(Debug::Flags::Error, Debug::Sound,
            "The audio file must be open for reading.");
        return;
    }

    uint8_t readChunks = 0;
    while(readChunks != 3)
    {
        RiffHeader riffHeader;
        //std::cout << audioFile->tell() << std::endl;
        /*std::cout << */audioFile->read(reinterpret_cast<uint8_t*>(&riffHeader), sizeof(RiffHeader)) /*<< std::endl*/;
        //std::cout << audioFile->tell() << std::endl;

        if(!strncmp(reinterpret_cast<char*>(riffHeader.id), "RIFF", sizeof(riffHeader.id)))
        {
            RiffChunk riffChunk;
            audioFile->read(reinterpret_cast<uint8_t*>(&riffChunk), sizeof(RiffChunk));

            if(!strncmp(reinterpret_cast<char*>(riffChunk.type), "WAVE", sizeof(riffChunk.type)))
            {
                Debug::print(Debug::Flags::Error, Debug::Subsystem::Sound,
                    "Invalid riff chunk: type parameter is not \"WAVE\"");
            }

            readChunks++;
        }
        else if(!strncmp(reinterpret_cast<char*>(riffHeader.id), "fmt ", sizeof(riffHeader.id))) 
        {
            FormatChunk formatChunk;
            audioFile->read(reinterpret_cast<uint8_t*>(&formatChunk), sizeof(FormatChunk));

            if(formatChunk.audioFormat != 0x0001) //Format is not PCM
            {
                Debug::print(Debug::Flags::Error, Debug::Subsystem::Sound,
                    "Invalid audio format: internal reader only supports uncompressed PCM");
            }

            wavHeader.fmtSampleRate = formatChunk.sampleRate;

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
            readChunks++;
        }
        else
        {
            audioFile->seek(riffHeader.size - sizeof(RiffHeader), FileInterface::Origin::Middle);
        }
    }
    
    // audioFile->read(reinterpret_cast<uint8_t*>(&(AudioSource::wavHeader)), sizeof(PartialWAVHeader));
    // audioFile->seek(AudioSource::wavHeader.listHeader.size - sizeof(wavHeader.listFormat), FileInterface::Origin::Middle);
    // audioFile->read(reinterpret_cast<uint8_t*>(&(AudioSource::dataBlock)), sizeof(DataBlock));
    // bool stereo = (AudioSource::wavHeader.fmtNumChannels > 1);
    // switch(AudioSource::wavHeader.fmtBitsPerSample)
    // {
    //     case 16:
    //         AudioSource::format = stereo ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
    //         break;
    //     case 8:
    //         AudioSource::format = stereo ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8;
    //         break;
    //     default:
    //         AudioSource::format = -1;
    //         break;
    // }
}
void AudioSource::fillBuffer(ALint buffer)
{
    int bufferSizeBackup = bufferSize;
    if (AudioSource::audioFile->tell() + bufferSize > AudioSource::audioFile->getSize())
    {
        bufferSize = AudioSource::audioFile->getSize() - AudioSource::audioFile->tell();
    }

    audioFile->read(reinterpret_cast<uint8_t*>(bufferData), bufferSize);
    alBufferData(buffer,format, bufferData, bufferSize, wavHeader.fmtSampleRate);
    bufferSize = bufferSizeBackup;
}
AudioSource::AudioSource(FileInterface* audiofile) 
: audioFile(audiofile)
{
    num_buffer = 2;
    num_soucers = 1;
    bufferSize = 44100;
    alGenBuffers(num_buffer, &(AudioSource::buffers[0])); //generate the buffer    
    LoadWavData();
    alGenSources(num_soucers, &source); //generate the source
}

AudioSource::~AudioSource()
{
    alDeleteBuffers(num_buffer, &(AudioSource::buffers[0])); //delete buffers
    alDeleteSources(num_soucers, &(AudioSource::source)); //delete source
}
void AudioSource::SetPosition(float x,  float y, float z)
{
    ALfloat position[] ={x, y, x};
    alSourcefv(source, AL_POSITION, position);
}
void AudioSource::SetVelocity(float x,  float y, float z)
{
    ALfloat velocity[] ={x, y, x};
    alSourcefv(source, AL_VELOCITY, velocity);
}
void AudioSource::SetOrientation(float x,  float y, float z)
{
    ALfloat orientation[] ={x, y, x};
    alSourcefv(source, AL_ORIENTATION, orientation);
}
void AudioSource::Play()
{
    bufferData = static_cast<char*>(std::malloc(bufferSize));
    for(int i =0; i<2; i++)
    {
        fillBuffer(buffers[i]);
    }
    alSourceQueueBuffers(source, 2, &buffers[0]);
    alSourcePlay(source);
    uint64_t fileSize = AudioSource::audioFile->getSize();
    while(AudioSource::audioFile->tell() < fileSize)
    {
        ALint processed;
        alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
        std::this_thread::sleep_for(100ms);
        while(processed--)
        {
            ALuint bufferID;
            alSourceUnqueueBuffers(source, 1, &bufferID);
            fillBuffer(bufferID);
            alSourceQueueBuffers(source, 1, &bufferID);
            //std::cout << AudioSource::audioFile->tell() << std::endl;
            //std::cout << fileSize << std::endl;
        }
    }
}
void AudioSource::Stop()
{
    alSourceStop(source);
}
void AudioSource::Pause()
{
    alSourcePause(source);
}
