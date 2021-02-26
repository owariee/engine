#include <cstdint>

struct WAVHeader
{
    //the RIF chunk descriptor
    char ChunkID[4];
    int32_t ChunkSize;
    char Format[4];
    //the "fmt" sub-chunk
    char Subchunk1ID[4];
    int32_t Subchunk1Size;
    int16_t AudioFormat;
    int16_t NumChannels;
    int32_t SampleRate;
    int32_t ByteRate;
    int16_t BlockAling;
    int16_t BitsPerSample;
    //the "data" sub-chunk
    char Subchunk2ID[4];
    int32_t Subchunk2Size;
    //Data missing;
};