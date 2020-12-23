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

        Window(const char* title, Window::Mode mode, Window::Resolution res);
        ~Window();

        bool isRunning();
        void close();

};

#endif//WINDOW_HPP
