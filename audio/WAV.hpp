#ifndef WAV_HPP
#define WAV_HPP

#include <cstdint>

struct RiffHeader {
    uint32_t id;
    int32_t size;
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
