#include "AudioListener.hpp"

#include "AL/al.h"

#include <iostream>

AudioListener::AudioListener()
{
    device = alcOpenDevice(NULL);
    if(!device)
    {
        std::cout << "[Audio] Cannot create the default device." << std::endl;
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
    ALfloat position[] = { x, y, z };
    alListenerfv(AL_POSITION, position);
}

void AudioListener::setVelocity(float x, float y, float z)
{
    ALfloat velocity[] = { x, y, z };
    alListenerfv(AL_VELOCITY, velocity);
}

void AudioListener::setOrientation(float x, float y, float z)
{
    ALfloat orientation[] = { x, y, z };
    alListenerfv(AL_ORIENTATION, orientation);
}
