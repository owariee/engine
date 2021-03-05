#ifndef AUDIOSOURCE_HPP
#define AUDIOSOURCE_HPP

//#define AL_LIBTYPE_STATIC
#include "AL/al.h"
#include "WAV.hpp"
#include "FilesystemNative.hpp"

class AudioSource
{
    private:
        int num_buffer, num_soucers;
        ALuint buffers[2];
        ALuint source;
        ALenum format;
        PartialWAVHeader wavHeader;
        DataBlock dataBlock;
        int bufferSize;
        FileInterface* audioFile;
        char* bufferData;
        void LoadWavData();
        void fillBuffer(ALint buffer);
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

#endif//AUDIOSOURCE_HPP
