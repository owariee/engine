#include "AudioSource.hpp"
#include "Debug.hpp"
#include "fmt/core.h"
#include <cstdlib>

void AudioSource::LoadWavData(FileInterface* audiofile)
{
    WAVHeader* wavheader = new WAVHeader();
    if(audiofile->isOpen())
    {
        audiofile->read(reinterpret_cast<uint8_t*>(wavheader), sizeof(WAVHeader));
        format = AL_FORMAT_STEREO16;
        int t = audiofile->tell();
        size = wavheader->ChunkSize + 8 - t;
        frequency = wavheader->SampleRate;
        data = (ALvoid*) std::malloc(size);
        audiofile->read(reinterpret_cast<uint8_t*>(data), size);
        //delete wavheader;
        return;
    }
    Debug::print(Debug::Flags::Error, Debug::Sound, "The audio file must be open for reading.");
}

AudioSource::AudioSource(FileInterface* audiofile)
{
    num_buffer = 1;
    num_soucers = 1;
    LoadWavData(audiofile);
    alGenBuffers(num_buffer, &buffer); //generate the buffer
    alBufferData(buffer, format, data, 176, frequency); //fills a buffer with audio data
    alGenSources(num_soucers, &source); //generate the source
    alSourcei(source, AL_BUFFER, buffer); //anex buffer to a source
    int* frequencia = new int();
    int * bits= new int();
    int * channels= new int(); 
    int * size= new int();
    int* data= new int();
    alGetBufferiv(buffer, AL_FREQUENCY, frequencia);
    alGetBufferiv(buffer, AL_BITS, bits);
    alGetBufferiv(buffer, AL_CHANNELS, channels);
    alGetBufferiv(buffer, AL_SIZE, size);
}

AudioSource::~AudioSource()
{
    alDeleteBuffers(num_buffer, &buffer); //delete buffer
    alDeleteSources(num_soucers, &source); //delete source
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
    alSourcePlay(source);
}
void AudioSource::Stop()
{
    alSourceStop(source);
}
void AudioSource::Pause()
{
    alSourcePause(source);
}