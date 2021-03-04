//#include "Windows.hpp"
#include "Graphics.hpp"
#include "FileInfo.hpp"
#include "FilesystemZip.hpp"
#include "AudioListener.hpp"
#include "AudioSource.hpp"
#include "AL/al.h"
#include "AL/alc.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) 
{
    std::string caminho = "../../../../Downloads/";
    FilesystemNative* fs = new FilesystemNative(caminho);
    FileInfo arquivo("teste.wav");

    fs->initialize();

    FileInterface* file = fs->openFile(arquivo, FileInterface::Mode::Read);

    AudioListener* listener = new AudioListener();
    AudioSource* source = new AudioSource(file);
    
    source->Play();
        
    delete listener;
    delete source;
    
    fs->closeFile(file);

    delete file;

    fs->shutdown();

    delete fs;

    return 0;   
}


