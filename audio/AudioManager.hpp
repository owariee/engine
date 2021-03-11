#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include "AudioListener.hpp"
#include "AudioSource.hpp"
#include <vector>

class AudioManager
{
    private:
    AudioListener listener;
    std::vector<AudioSource*> sourceList;
    double accumulatedFrameTime;

    public:
    AudioManager();
    ~AudioManager();

    AudioSource* addSound(FileInterface* file);
    bool removeSound(AudioSource* instance);
    void processSounds(double frameTime);
};

#endif//AUDIOMANAGER_HPP