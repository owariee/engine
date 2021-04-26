#include "Mouse.hpp"

#include "GLFW/glfw3.h"

Mouse::Mouse(Window* window)
:Input(window)
{
    
}
Mouse::~Mouse()
{
}
Mouse::Position Mouse::getPosition() 
{
    Mouse::Position mousepostemp = { 0, 0 };
    if(Mouse::hasAWindow()){        
        glfwGetCursorPos(reinterpret_cast<GLFWwindow*>(Mouse::window),
                &(mousepostemp.x), &(mousepostemp.y));
        return mousepostemp;
    }
    return mousepostemp;
}
bool Mouse::buttonPressed(Mouse::Buttons button)
{
    if(Mouse::hasAWindow()){
        int state = glfwGetMouseButton(reinterpret_cast<GLFWwindow*>(Mouse::window), button);
        if(state == GLFW_PRESS) { 
            return true;
        }
    }
    return false;
}
bool Mouse::buttonBeingPressed(Mouse::Buttons button)
{
    if(Mouse::hasAWindow()){
        int state = glfwGetMouseButton(reinterpret_cast<GLFWwindow*>(Mouse::window), button);
        if(state == GLFW_REPEAT) { 
            return true;
        }
    }
    return false;
}
bool Mouse::buttonReleased(Mouse::Buttons button)
{
    if(Mouse::hasAWindow()){
        int state = glfwGetMouseButton(reinterpret_cast<GLFWwindow*>(Mouse::window), button);
        if(state == GLFW_RELEASE) { 
            return true;
        }
    }
    return false;
}