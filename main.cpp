#include "Graphics.hpp"
#include "FileInfo.hpp"
#include "FilesystemNative.hpp"
#include "FileNative.hpp"
#include "Debug.hpp"
#include "Window.hpp"
#include "AudioManager.hpp"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) 
{
    std::string caminho = "./";
    FilesystemNative* fs = new FilesystemNative(caminho);
    FileInfo arquivo("music.wav");

    fs->initialize();

    FileNative* file = dynamic_cast<FileNative*>(fs->openFile(arquivo, FileInterface::Mode::Read));

    AudioManager audioManager;
    AudioSource* audio0 = audioManager.addSound(file);

    Window win("Sound loop", Window::Mode::Windowed, {800, 600});

    win.setVsync(60);
    
    audio0->play();

    while(win.isRunning())
    {
        if (win.isKeyPressed(Window::Keys::S))
        {
            audio0->stop();
        }

        if (win.isKeyPressed(Window::Keys::P))
        {
            audio0->play();
        }

        if (win.isKeyPressed(Window::Keys::O))
        {
            audio0->pause();
        }

        audioManager.processSounds(win.getFrameTime());
    }
    
    fs->closeFile(file);
    delete file;

    fs->shutdown();
    delete fs;

    return 0;
}
