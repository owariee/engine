#include "Keyboard.hpp"

#include "GLFW/glfw3.h"

Keyboard::Keyboard(Window* window)
:Input(window)
{
}
Keyboard::~Keyboard()
{
}
bool Keyboard::keyPressed(Keyboard::Keys key)
{
    if(Keyboard::hasAWindow()){
        int state = glfwGetKey(reinterpret_cast<GLFWwindow*>(Keyboard::window), key);
        if(state == GLFW_PRESS) { 
            return true;
        }
    }
    return false;
}
bool Keyboard::keyBeingPressed(Keyboard::Keys key)
{
    if(Keyboard::hasAWindow()){
        int state = glfwGetKey(reinterpret_cast<GLFWwindow*>(Keyboard::window), key);
        if(state == GLFW_REPEAT) { 
            return true;
        }
    }
    return false;
}
bool Keyboard::keyReleased(Keyboard::Keys key)
{
    if(Keyboard::hasAWindow()){
        int state = glfwGetKey(reinterpret_cast<GLFWwindow*>(Keyboard::window), key);
        if(state == GLFW_RELEASE) { 
            return true;
        }
    }
    return false;
}