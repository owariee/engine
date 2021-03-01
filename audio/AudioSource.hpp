//#define AL_LIBTYPE_STATIC
#include "AL/al.h"
#include <string>
#include "wavheader.hpp"
#include "FilesystemNative.hpp"

class AudioSource
{
    private:
        int num_buffer, num_soucers;
        ALuint buffer;
        ALuint source;
        ALenum format;
        ALsizei size;
        ALsizei frequency;
        ALvoid* data;
        void LoadWavData(FileInterface* audiofile);
    public:
        AudioSource(FileInterface* audiofile);
        ~AudioSource();
        void SetPosition(float x,  float y, float z);
        void SetVelocity(float x, float y,  float z);
        void SetOrientation(float x, float y, float z);
        void Play();
        void Pause();
        void Stop();
};
