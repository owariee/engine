#include "window/Window.hpp"
#include "graphics/Graphics.hpp"

int main(int argc, char* argv[]) 
{
    Window win("Teste", Window::Mode::Windowed, { 640, 480 });
    Graphics gfx;


    while(win.isRunning())
    {

    }

    return 0;
}


