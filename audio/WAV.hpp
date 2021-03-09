#ifndef WAV_HPP
#define WAV_HPP

#include <cstdint>

struct RiffHeader {
    char id[4];
    uint32_t size;
};

struct RiffChunk
{
    char type[4];
};

struct FormatChunk
{
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAling;
    uint16_t bitsPerSample;
};

struct PartialWAVHeader {
    RiffHeader riffHeader;
    uint32_t riffFormat;
    RiffHeader fmtHeader;
    int16_t fmtAudioFormat;
    int16_t fmtNumChannels;
    int32_t fmtSampleRate;
    int32_t fmtByteRate;
    int16_t fmtBlockAling;
    int16_t fmtBitsPerSample;
    RiffHeader listHeader;
    uint32_t listFormat;
};

typedef RiffHeader DataBlock;

#endif//WAV_HPP
