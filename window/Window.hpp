#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "glad/glad.h"
#include "glfw/glfw3.h"

class Window
{
    private:
        bool shouldClose;
        GLFWwindow* window;        

    public:
        typedef enum {Fullscreen, Windowed, Borderless} Mode;
        typedef struct { int width, height; } Resolution;
        typedef struct { double x, y; } MousePosition;

        Window(const char* title, Window::Mode mode, Window::Resolution res);
        ~Window();

        bool isRunning();
        void close();
        Window::MousePosition getMousePosition();
        Window::Resolution getResolution();
        Window::Mode getMode();
        bool isKeyPressed(int key);
        bool isKeyBeingPressed(int key);
        bool isKeyReleased(int key);
};

#endif//WINDOW_HPP
