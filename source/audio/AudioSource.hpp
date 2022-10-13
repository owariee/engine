#ifndef AUDIOSOURCE_HPP
#define AUDIOSOURCE_HPP

#include "AL/al.h"
#include "FileInterface.hpp"

class AudioSource
{
    private:
        struct RiffHeader {
            char id[4];
            uint32_t size;
        };

        struct FormatChunk
        {
            uint16_t audioFormat;
            uint16_t numChannels;
            uint32_t sampleRate;
            uint32_t byteRate;//
            uint16_t blockAling;//
            uint16_t bitsPerSample;
        };

        FileInterface* audioFile;

        ALuint source;
        ALuint buffers[2];

        ALenum format;
        ALsizei sampleRate;

        uint64_t dataStartPos;
        uint64_t dataEndPos;

        uint64_t dataActualPos;
        
        int bufferSize;
        char* bufferData;

        ALuint clearBuffer();
        void fillBuffer(ALuint* buffer);
        void threadPlay();

        bool paused;
        bool playing;
        bool stopped;

    public:
        AudioSource(FileInterface* audiofile);
        ~AudioSource();
        void setPosition(float x,  float y, float z);
        void setVelocity(float x, float y,  float z);
        void setOrientation(float x, float y, float z);
        void play();
        void pause();
        void stop();
        void updateBuffers();
};

#endif//AUDIOSOURCE_HPP
