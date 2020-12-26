#include "Window.hpp"

#include "../debug/Debug.hpp"

Window::Window(const char* title, Window::Mode mode, Window::Resolution res)
{
    if (!glfwInit())
    {
        Debug::print(Debug::Flags::Error,
                     Debug::Subsystem::Window,
                     "Cannot intialize Window Subsystem!");
        return;
    }

    Window::window = glfwCreateWindow(res.width, res.height, title, NULL, NULL);
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
}

bool Window::isRunning()
{
    // end of an frame

    glfwSwapBuffers(Window::window);
    glfwPollEvents();

    // process events (Keyboard, mouse, gamepad, controller)

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // start of new frame
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
    
}