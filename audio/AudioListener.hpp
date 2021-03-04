//#define AL_LIBTYPE_STATIC
#include "AL/alc.h"
#include "AL/al.h"
#include "stdlib.h"

class AudioListener
{
    private:
        ALCdevice *device;
        ALCcontext *context;            
    public:                
        AudioListener(/* args */);
        ~AudioListener();
        void SetPosition(float x, float y, float z);
        void SetVelocity(float x, float y, float z);
        void SetOrientation(float x, float y, float z);
};