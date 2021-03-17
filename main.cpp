#include "Shader.hpp"
#include "Mesh.hpp"
#include "Camera2D.hpp"
#include "Camera3D.hpp"
#include "Texture.hpp"
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

    win.setVsync(144);
    
    FileInfo arquivo("music.wav");
    FileInterface* file = fs.openFile(arquivo, FileInterface::Mode::Read);
    AudioSource* audio0 = audioManager.addSound(file);
    audio0->play();

    FileInfo vertexShaderPath("shader.vs");
    FileInterface* vertexFile = fs.openFile(vertexShaderPath, FileInterface::Mode::Read);
    FileInfo fragmentShaderPath("shader.fs");
    FileInterface* fragmentFile = fs.openFile(fragmentShaderPath, FileInterface::Mode::Read);
    Shader sh0(vertexFile, fragmentFile);

    FileInfo arquivoBMP("echidna2.bmp");
    FileInterface* bmp = fs.openFile(arquivoBMP, FileInterface::Mode::Read);
    //BMPLoader bmpLoader(bmp);
    Texture tex1(bmp);


    Camera2D cam(800, 600);
    Camera3D cam1(800, 600, 45.0f);

    float vertices3d[] = {
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,  // top right
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  // top left 
         0.5f,  0.5f, 0.5f, 1.0f, 1.0f,  // back top right
         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,  // back bottom right
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  // back bottom left
        -0.5f,  0.5f, 0.5f, 0.0f, 1.0f   // back top left 
    };
    int indices3d[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3,    // second triangle
        7, 5, 4,   // first triangle
        7, 6, 5    // second triangle
    };
    float vertices[] = {
        300.0f,  10.0f, 0.0f, 1.0f, 1.0f, // top right
        300.0f, 300.0f, 0.0f, 1.0f, 0.0f, // bottom right
         10.0f, 300.0f, 0.0f, 0.0f, 0.0f, // bottom left
         10.0f,  10.0f, 0.0f, 0.0f, 1.0f  // top left
    };
    int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    Mesh mesh0(vertices, 20, indices, 6);
    Mesh mesh1(vertices3d, 40, indices3d, 12);

    while(win.isRunning())
    {
        //input
        // if (win.isKeyPressed(Window::Keys::S))
        // {
        //     audio0->stop();
        // }

        // if (win.isKeyPressed(Window::Keys::P))
        // {
        //     audio0->play();
        // }

        // if (win.isKeyPressed(Window::Keys::O))
        // {
        //     audio0->pause();
        // }

        //audio
        audioManager.processSounds(win.getFrameTime());

        //logic
        //draw
        
        sh0.use();
        tex1.use(GL_TEXTURE0);
        
        // for (int i = 0; i < 4 ; i++) 
        // {
        //     for (int j = 0; j < 4 ; j++) 
        //     {
        //         std::cout << teste[i][j] << " ";
        //     }
        //     std::cout << std::endl;
        // }
        cam1.processInput(&win);
        sh0.setUniform("cameraMatrix", cam1.getViewMatrix());
        mesh1.draw();

        //cam.processInput(&win);
        sh0.setUniform("cameraMatrix", cam.getViewMatrix());
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
