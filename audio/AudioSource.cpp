#include "AudioSource.hpp"
#include "Debug.hpp"
#include "fmt/core.h"
#include <cstdlib>
#include <thread>
using namespace std::chrono_literals;

void AudioSource::LoadWavData()
{
    if(!(audioFile->isOpen()))
    {
        Debug::print(Debug::Flags::Error, Debug::Sound, "The audio file must be open for reading.");
        return;
    }
    audioFile->read(reinterpret_cast<uint8_t*>(&(AudioSource::wavHeader)), sizeof(PartialWAVHeader));
    audioFile->seek(AudioSource::wavHeader.listHeader.size - sizeof(wavHeader.listFormat), FileInterface::Origin::Middle);
    audioFile->read(reinterpret_cast<uint8_t*>(&(AudioSource::dataBlock)), sizeof(DataBlock));
    bool stereo = (AudioSource::wavHeader.fmtNumChannels > 1);
    switch(AudioSource::wavHeader.fmtBitsPerSample)
    {
        case 16:
            AudioSource::format = stereo ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
            break;
        case 8:
            AudioSource::format ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8;
            break;
        default:
            AudioSource::format = -1;
            break;
    }
}
void AudioSource::fillBuffer(ALint buffer)
{
    audioFile->read(reinterpret_cast<uint8_t*>(bufferData), bufferSize);
    alBufferData(buffer,format, bufferData, bufferSize, wavHeader.fmtSampleRate);
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
    while(true)
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