#include "Gamepad.hpp"

#include <iostream>
#include "GLFW/glfw3.h"

Gamepad::Gamepad(Window* window,Gamepads gamepadID)
:Input(window),
id(gamepadID)
{
}
Gamepad::~Gamepad()
{
}
bool Gamepad::isConnected()
{
    if(Gamepad::hasAWindow()){
        int gamepadConected = glfwJoystickPresent(Gamepad::id);
        if(gamepadConected == 1){
            return true;
        }
        std::string message = "Gamepad" + std::to_string(Gamepad::id + 1) + " is unplugged.";
        std::cout << "[Input] " << message << std::endl;
    }
    return false;
}
bool Gamepad::buttonPressed(Gamepad::Buttons button)
{
    if(Gamepad::hasAWindow()){
        if(Gamepad::isConnected()){
            int count = 0;
            const  unsigned  char * buttons = glfwGetJoystickButtons (Gamepad::id , & count);
            if(buttons[button] == GLFW_PRESS) { 
                return true; 
            }
        }
    }
    return false;
}
bool Gamepad::buttonBeingPressed(Gamepad::Buttons button)
{
    if(Gamepad::hasAWindow()){
        if(Gamepad::isConnected()){
            int count = 0;
            const  unsigned  char * buttons = glfwGetJoystickButtons(Gamepad::id , & count);
            if(buttons[button] == GLFW_REPEAT) { 
                return true; 
            }
        }
    }
    return false;
}
bool Gamepad::buttonReleased(Gamepad::Buttons button)
{
    if(Gamepad::hasAWindow()){
        if(Gamepad::isConnected()){
            int count = 0;
            const  unsigned  char * buttons = glfwGetJoystickButtons(Gamepad::id , & count);
            if(buttons[button] == GLFW_RELEASE) { 
                return true; 
            }
        }
    }
    return false;
}
int Gamepad::getAxis(Gamepad::Axis axis)
{
    if(Gamepad::hasAWindow()){
        if(Gamepad::isConnected()){
            int count = 0;
            const float* jaxis = glfwGetJoystickAxes(Gamepad::id, & count);
            return jaxis[axis];
        }
    }
    return 0;
}