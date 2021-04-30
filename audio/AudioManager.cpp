#include "AudioManager.hpp"

#include <thread>

AudioManager::AudioManager()
: accumulatedFrameTime(0)
{
    
}

AudioManager::~AudioManager()
{
    for(auto i = AudioManager::sourceList.begin(); i != AudioManager::sourceList.end(); i++)
    {
        delete (*i);
    }
}

AudioSource* AudioManager::addSound(FileInterface* file)
{
    AudioSource* tempInstance = new AudioSource(file);
    AudioManager::sourceList.push_back(tempInstance);
    return tempInstance;
}

bool AudioManager::removeSound(AudioSource* instance)
{
    bool deleted = false;
    for(auto i = AudioManager::sourceList.begin(); i != AudioManager::sourceList.end(); i++)
    {     
        if((*i) == instance)
        {
            AudioSource* temp = *i;
            temp->stop();
            AudioManager::sourceList.erase(i);
            deleted = true;
            break;
        }
    }
    return deleted;
}

void AudioManager::processSounds()
{
    for(;;)
    {
        auto timeStart = std::chrono::steady_clock::now();
        for(auto i = AudioManager::sourceList.begin(); i != AudioManager::sourceList.end(); i++)
        {
            AudioSource* temp = *i;
            temp->updateBuffers();
        }
        auto timeFinal = (std::chrono::steady_clock::now() - timeStart).count();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 - timeFinal));
    }
}
