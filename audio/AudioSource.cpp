#include "AudioSource.hpp"
#include "Debug.hpp"

void AudioSource::LoadWavData(FileInterface* audiofile)
{
    WAVHeader wavheader;
    if(!audiofile->isOpen())
    {
        Debug::print(Debug::Flags::Error, Debug::Sound, "The audio file must be open for reading.");
    }
    else
    {
        const int wavsize = sizeof(wavheader);
        char filedata[wavsize] = {};
        audiofile->read(reinterpret_cast<uint8_t*>(filedata), wavsize);
        wavheader.ChunkID[0] = filedata[0];
        wavheader.ChunkID[1] = filedata[1];
        wavheader.ChunkID[2] = filedata[2];
        wavheader.ChunkID[3] = filedata[3];
        wavheader.ChunkSize = (filedata[4] + filedata[5] + filedata[6] + filedata[7]);
        wavheader.Format[0] = filedata[8];
        wavheader.Format[1] = filedata[9];
        wavheader.Format[2] = filedata[10];
        wavheader.Format[3] = filedata[11];
        wavheader.Subchunk1ID[0] = filedata[12];
        wavheader.Subchunk1ID[1] = filedata[13];
        wavheader.Subchunk1ID[2] = filedata[14];
        wavheader.Subchunk1ID[3] = filedata[15];
        wavheader.Subchunk1Size = (filedata[16] + filedata[17] + filedata[18] + filedata[19]);
        wavheader.AudioFormat = (filedata[20] + filedata[21]);
        wavheader.NumChannels = (filedata[22] + filedata[23]);
        wavheader.SampleRate = (filedata[24] + filedata[25] + filedata[26]+ filedata[27]);
        wavheader.ByteRate = (filedata[28] + filedata[29] + filedata[30]+ filedata[31]);
        wavheader.BlockAling = (filedata[32] + filedata[33]);
        wavheader.BitsPerSample = (filedata[34] + filedata[35]);
        wavheader.Subchunk2ID[0] = filedata[36];
        wavheader.Subchunk2ID[1] = filedata[37];
        wavheader.Subchunk2ID[2] = filedata[38];
        wavheader.Subchunk2ID[3] = filedata[39];
        wavheader.Subchunk2Size = (filedata[40] + filedata[41] + filedata[42] + filedata[43]);
        audiofile->read(reinterpret_cast<uint8_t*>(AudioSource::data), wavheader.Subchunk2Size);
        AudioSource::format = AL_FORMAT_STEREO16;
        AudioSource::size = wavheader.Subchunk2Size;
        AudioSource::frequency = wavheader.SampleRate;
    }    
}

AudioSource::AudioSource(FileInterface* audiofile)
{
    num_buffer = 1;
    num_soucers = 1;
    LoadWavData(audiofile);
    alGenBuffers(num_buffer, AudioSource::buffer); //generate the buffer
    alBufferData(AudioSource::buffer[0], AudioSource::format, AudioSource::data, AudioSource::size, AudioSource::frequency); //fills a buffer with audio data
    alGenSources(num_soucers, AudioSource::source); //generate the source
    alSourcei(AudioSource::source[0], AL_BUFFER, AudioSource::buffer[0]); //anex buffer to a source
}

AudioSource::~AudioSource()
{
    alDeleteBuffers(num_buffer, AudioSource::buffer); //delete buffer
    alDeleteSources(num_soucers, AudioSource::source); //delete source
}
void AudioSource::SetPosition(float x,  float y, float z)
{
    ALfloat position[] ={x, y, x};
    alSourcefv(AudioSource::source[0], AL_POSITION, position);
}
void AudioSource::SetVelocity(float x,  float y, float z)
{
    ALfloat velocity[] ={x, y, x};
    alSourcefv(AudioSource::source[0], AL_VELOCITY, velocity);
}
void AudioSource::SetOrientation(float x,  float y, float z)
{
    ALfloat orientation[] ={x, y, x};
    alSourcefv(AudioSource::source[0], AL_ORIENTATION, orientation);
}
void AudioSource::Play()
{
    alSourcePlay(AudioSource::source[0]);
}
void AudioSource::Stop()
{
    alSourceStop(AudioSource::source[0]);
}
void AudioSource::Pause()
{
    alSourcePause(AudioSource::source[0]);
}