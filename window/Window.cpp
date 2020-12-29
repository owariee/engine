#include "Window.hpp"

#include "../debug/Debug.hpp"

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