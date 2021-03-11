#include "Shader.hpp"
#include "Mesh.hpp"
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
    FilesystemNative fs("./");
    AudioManager audioManager;
    Window win("Sound loop", Window::Mode::Windowed, {800, 600});

    win.setVsync(60);
    
    FileInfo arquivo("music.wav");
    FileInterface* file = fs.openFile(arquivo, FileInterface::Mode::Read);
    AudioSource* audio0 = audioManager.addSound(file);
    audio0->play();

    FileInfo vertexShaderPath("shader.vs");
    FileInterface* vertexFile = fs.openFile(vertexShaderPath, FileInterface::Mode::Read);
    FileInfo fragmentShaderPath("shader.fs");
    FileInterface* fragmentFile = fs.openFile(fragmentShaderPath, FileInterface::Mode::Read);
    Shader sh0(vertexFile, fragmentFile);


    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    Mesh mesh0(vertices, 12, indices, 6);

    while(win.isRunning())
    {
        //input
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

        //audio
        audioManager.processSounds(win.getFrameTime());

        //logic
        //draw
        sh0.use();
        mesh0.draw();
    }
    
    fs.closeFile(file);
    fs.closeFile(vertexFile);
    fs.closeFile(fragmentFile);
    delete file;
    delete vertexFile;
    delete fragmentFile;
    return 0;
}
