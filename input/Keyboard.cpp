#include "Keyboard.hpp"

#include "GLFW/glfw3.h"

Keyboard::~Keyboard()
{
}
bool Keyboard::getKeyDown(Keyboard::Keys key)
{
    if(Keyboard::hasAWindow()){
        int state = glfwGetKey(reinterpret_cast<GLFWwindow*>(Keyboard::window), key);
        if(state == GLFW_PRESS) { 
            return true;
        }
    }
    return false;
}
bool Keyboard::getKeyUp(Keyboard::Keys key)
{
    if(Keyboard::hasAWindow()){
        int state = glfwGetKey(reinterpret_cast<GLFWwindow*>(Keyboard::window), key);
        if(state == GLFW_RELEASE) { 
            return true;
        }
    }
    return false;
}