#include "Graphics.hpp"
#include "FileInfo.hpp"
#include "FilesystemZip.hpp"
#include "Debug.hpp"
#include "Window.hpp"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) 
{
    Window win("Raycaster", Window::Mode::Windowed, {800, 600});

    win.setVsync(60);

    while(win.isRunning())
    {
        std::cout << win.getFrameTime() << std::endl;
    }

    return 0;
}
