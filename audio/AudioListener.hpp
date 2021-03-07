#ifndef AUDIOLISTENER_HPP
#define AUDIOLISTENER_HPP

#include "AL/alc.h"

class AudioListener
{
    private:
        ALCdevice* device;
        ALCcontext* context;            
    public:                
        AudioListener();
        ~AudioListener();
        void setPosition(float x, float y, float z);
        void setVelocity(float x, float y, float z);
        void setOrientation(float x, float y, float z);
};

#endif//AUDIOLISTENER_HPP
