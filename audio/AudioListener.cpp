#include "AudioListener.hpp"

#include "Debug.hpp"

#include "AL/al.h"

AudioListener::AudioListener()
{
    device = alcOpenDevice(NULL);
    if(!device)
    {
        Debug::print(Debug::Flags::Error, Debug::Sound,
            "It was not possible to create a device nor a context.");
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

void AudioListener::setPosition(float x, float y, float z)
{
    ALfloat position[] = {x,y,z};
    alListenerfv(AL_POSITION, position);
}

void AudioListener::setVelocity(float x, float y, float z)
{
    ALfloat velocity[] = {x,y,z};
    alListenerfv(AL_VELOCITY, velocity);
}

void AudioListener::setOrientation(float x, float y, float z)
{
    ALfloat orientation[] = {x,y,z};
    alListenerfv(AL_ORIENTATION, orientation);
}
