#include "Window.hpp"

#include "Debug.hpp"
#include "GLFW/glfw3.h"
#include "Renderer2D.hpp"

#include <chrono>
#include <thread>
#include <cmath>

bool Window::isGamepadConnected(int gamepad)
{
    int gamepadConected = glfwJoystickPresent(gamepad);
    if(gamepadConected == 1)
    {
        return true;
    }
    {        
        std::string message = "Gamepad" + std::to_string(gamepad + 1) + " is unplugged.";
        Debug::print(Debug::Flags::Warning, Debug::Subsystem::Window, message);
        return false;
    }
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    Window* winInstance = static_cast<Window*>(glfwGetWindowUserPointer(window));
    winInstance->renderer2d->camera->updateProjectionMatrix(width, height);
}  

Window::Window(const char* title, Window::Mode mode, Window::Resolution res)
: mode(mode)
, vsyncMs(0)
{
    GLFWmonitor* primary_monitor = NULL;

    if (!glfwInit())
    {
        Debug::print(Debug::Flags::Error,
                     Debug::Subsystem::Window,
                     "Cannot intialize Window Subsystem!");
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
        Debug::print(Debug::Flags::Error,
                     Debug::Subsystem::Window,
                     "Cannot create window!");
        return;
    }

    glfwMakeContextCurrent(Window::window);
    Window::shouldClose = false;

    glfwSetFramebufferSizeCallback(window, (Window::framebufferSizeCallback));  
    glfwSetWindowUserPointer(window, this);
    //glfwSetInputMode(Window::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Debug::print(Debug::Flags::Error, Debug::Subsystem::Graphics, "Failed to initialize GLAD");
    }

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    Window::fs = new FilesystemNative("./resources/");
    Window::renderer2d = new Renderer2D(res.width, res.height, Window::fs);

    Window::frameStart = std::chrono::steady_clock::now();
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

    glfwSwapBuffers(Window::window);
    glfwPollEvents();
   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return !(glfwWindowShouldClose(Window::window) || Window::shouldClose);
}

void Window::close()
{
    Window::shouldClose = true;
}

Window::~Window()
{
    glfwTerminate();
}

Window::MousePosition Window::getMousePosition()
{
    Window::MousePosition mousepostemp = { 0, 0 };
    glfwGetCursorPos(Window::window, &(mousepostemp.x), &(mousepostemp.y));
    return mousepostemp;
}

Window::Resolution Window::getResolution()
{
    Window::Resolution restemp = { 0, 0 };
    glfwGetWindowSize(Window::window, &(restemp.height),&(restemp.width));
    return restemp;
}
Window::Mode Window::getMode()
{
    return Window::mode;
}

//Session: keyboard inputs
bool Window::isKeyPressed(int key)
{
    int state = glfwGetKey(Window::window, key);
    if(state == GLFW_PRESS){ return true; }
    else { return false; }
}

bool Window::isKeyBeingPressed(int key)
{
    int state = glfwGetKey(Window::window, key);
    if(state == GLFW_REPEAT) { return true; }
    else { return false; }
}

bool Window::isKeyReleased(int key)
{
    int state = glfwGetKey(Window::window, key);
    if(state == GLFW_RELEASE) { return true; }
    else { return false; }
}

//Session: gamepad entries
bool Window::isGamepadButtonPressed(int gamepad, int button)
{
    if(Window::isGamepadConnected(gamepad))
    {
        int count = 0;
        const  unsigned  char * buttons = glfwGetJoystickButtons ( gamepad , & count);
        if(buttons[button] == GLFW_PRESS) { return true; }
        else { return false; }
    }
    else{ return false; } 
}
bool Window::isGamepadButtonBeingPressed(int gamepad, int button)
{    
    if(Window::isGamepadConnected(gamepad))
    {
        int count = 0;
        const  unsigned  char * buttons = glfwGetJoystickButtons ( gamepad , & count);
        if(buttons[button] == GLFW_REPEAT) { return true; }
        else { return false; }
    }
    else{ return false; }
}
bool Window::isGamepadButtonReleased(int gamepad, int button)
{     
    if(Window::isGamepadConnected(gamepad))
    {
        int count = 0;
        const  unsigned  char * buttons = glfwGetJoystickButtons ( gamepad , & count);
        if(buttons[button] == GLFW_RELEASE) { return true; }
        else { return false; }
    }
    else{ return false; }
}
int Window::getGamepadAxis(int gamepad, int axis)
{    
    if(Window::isGamepadConnected(gamepad))
    {
        int count = 0;
        const float* jaxis = glfwGetJoystickAxes(gamepad, & count);
        return jaxis[axis];
    }
    else{ return false; }
}
//Session: Mouse inputs
bool Window::isMousePressed(int mouseButton)
{
    int state = glfwGetMouseButton(Window::window, mouseButton);
    if(state == GLFW_PRESS) { return true;}
    else { return false; }
}
bool Window::isMouseBeingPressed(int mouseButton)
{
    int state = glfwGetMouseButton(Window::window, mouseButton);
    if(state == GLFW_REPEAT) { return true;}
    else { return false; }
}
bool Window::isMouseReleased(int mouseButton)
{
    int state = glfwGetMouseButton(Window::window, mouseButton);
    if(state == GLFW_RELEASE) { return true;}
    else { return false; }
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
