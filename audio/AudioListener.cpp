#include "AudioListener.hpp"
#include "Debug.hpp"

AudioListener::AudioListener(/* args */)
{
    device = alcOpenDevice(NULL);
    if(!device)
    {
        Debug::print(Debug::Flags::Error, Debug::Sound, "It was not possible to create a device and consequently it was not possible to create a context.");
        return;
    }
    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);
}

AudioListener::~AudioListener()
{
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

void AudioListener::SetPosition(float x, float y, float z)
{
    ALfloat position[] = {x,y,z};
    alListenerfv(AL_POSITION, position);
}
void AudioListener::SetVelocity(float x, float y, float z)
{
    ALfloat velocity[] = {x,y,z};
    alListenerfv(AL_VELOCITY, velocity);
}
void AudioListener::SetOrientation(float x, float y, float z)
{
    ALfloat orientation[] = {x,y,z};
    alListenerfv(AL_ORIENTATION, orientation);
}