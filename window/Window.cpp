#include "Window.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Renderer2D.hpp"

#include <chrono>
#include <thread>
#include <cmath>
#include <iostream>

void Window::framebufferSizeCallback(void* window, int width, int height)
{
    glViewport(0, 0, width, height);
    Window* winInstance = static_cast<Window*>(glfwGetWindowUserPointer(reinterpret_cast<GLFWwindow*>(window)));
    winInstance->renderer2d->camera->updateProjectionMatrix(width, height);
    
}  

Window::Window(const char* title, Window::Mode mode, Window::Resolution res)
: mode(mode)
, vsyncMs(0)
{
    GLFWmonitor* primary_monitor = NULL;

    if (!glfwInit())
    {
        std::cout << "[Graphics] Cannot intialize Window Subsystem!" << std::endl;
        return;
    }
    
    if(mode == Window::Mode::Fullscreen || mode == Window::Mode::Borderless)
    {
        primary_monitor = glfwGetPrimaryMonitor();
    }
    if(mode == Window::Mode::Borderless)
    {
        const GLFWvidmode* glfwvidmode = glfwGetVideoMode(primary_monitor);
        glfwWindowHint(GLFW_RED_BITS, glfwvidmode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, glfwvidmode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, glfwvidmode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, glfwvidmode->refreshRate);
        res.width = glfwvidmode->width;
        res.height = glfwvidmode->height;
    }

    Window::window = glfwCreateWindow(res.width, res.height, title, primary_monitor, NULL);

    if (!Window::window)
    {
        glfwTerminate();
        std::cout << "[Graphics] Cannot create window!" << std::endl;
        return;
    }

    glfwMakeContextCurrent(reinterpret_cast<GLFWwindow*>(Window::window));
    Window::shouldClose = false;

    glfwSetFramebufferSizeCallback(reinterpret_cast<GLFWwindow*>(window),
            reinterpret_cast<void(*)(GLFWwindow*, int, int)>(Window::framebufferSizeCallback));  
    glfwSetWindowUserPointer(reinterpret_cast<GLFWwindow*>(window), this);
    //glfwSetInputMode(Window::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "[Graphics] Failed to initialize GLAD" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    Window::fs = new FilesystemNative("./game/resources/");
    Window::renderer2d = new Renderer2D(res.width, res.height, Window::fs);

    Window::frameStart = std::chrono::steady_clock::now();
    Window::keyboard = new Keyboard(Window::window);
    Window::mouse = new Mouse(Window::window);
}

bool Window::isRunning()
{
    Window::frameTime = std::chrono::steady_clock::now() - Window::frameStart;
    
    if (Window::vsyncMs.count() != 0 && Window::frameTime < Window::vsyncMs)
    {
        std::this_thread::sleep_for(Window::vsyncMs - Window::frameTime);
        Window::frameTime = Window::vsyncMs;
    }
    
    Window::frameStart = std::chrono::steady_clock::now();

    glfwSwapBuffers(reinterpret_cast<GLFWwindow*>(Window::window));
    glfwPollEvents();
   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return !(glfwWindowShouldClose(reinterpret_cast<GLFWwindow*>(Window::window)) || Window::shouldClose);
}

void Window::close()
{
    Window::shouldClose = true;
}

Window::~Window()
{
    glfwTerminate();
    delete Window::keyboard;
    delete Window::mouse;
}

Window::Resolution Window::getResolution()
{
    Window::Resolution restemp = { 0, 0 };
    glfwGetWindowSize(reinterpret_cast<GLFWwindow*>(Window::window),
            &(restemp.height), &(restemp.width));
    return restemp;
}
Window::Mode Window::getMode()
{
    return Window::mode;
}

void* Window::getFuncProcAddress()
{
    return (void*)glfwGetProcAddress;
}

double Window::getFrameTime()
{
    return Window::frameTime.count();
}

void Window::setVsync(int fps)
{
    if (fps == 0)
    {
        Window::vsyncMs = std::chrono::microseconds(fps);
        return;
    }
    
    int idealFrameTime = static_cast<int>(std::roundf((1.0f/fps)*1000000));
    Window::vsyncMs = std::chrono::microseconds(idealFrameTime);
}