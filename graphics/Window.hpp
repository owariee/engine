#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "FilesystemNative.hpp"
#include "Renderer2D.hpp"

#include <chrono>

class Window
{
    friend class Input;
    public:
        typedef enum {Fullscreen, Windowed, Borderless} Mode;
        typedef struct { int width, height; } Resolution;
        Renderer2D* renderer2d;
        FilesystemNative* fs;

        Window(const char* title, Window::Mode mode, Window::Resolution res);
        ~Window();
        bool isRunning();
        void close();
        Window::Resolution getResolution();
        Window::Mode getMode();
        void* getFuncProcAddress();
        double getFrameTime();
        void setVsync(int fps);
    
    private:
        void* window;
        static void framebufferSizeCallback(void* window, int width, int height);
        bool shouldClose;
        Window::Mode mode;
        std::chrono::time_point<std::chrono::steady_clock> frameStart;
        std::chrono::duration<double, std::milli> frameTime;
        std::chrono::duration<double, std::milli> vsyncMs;        
};

#endif//WINDOW_HPP