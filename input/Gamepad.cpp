#include "Gamepad.hpp"

#include <iostream>
#include "GLFW/glfw3.h"

Gamepad::Gamepad(Ids gamepadID)
:id(gamepadID)
{
}
Gamepad::~Gamepad()
{
}
bool Gamepad::isConnected()
{
    int gamepadConected = glfwJoystickPresent(Gamepad::id);
    if(gamepadConected == 1){
        return true;
    }
    std::string message = "Gamepad is unplugged.";
    std::cout << "[Input] " << message << std::endl;
    return false;
}
int Gamepad::getAxis(Gamepad::Axis axis)
{
    if(Gamepad::isConnected()){
        int count = 0;
        const float* jaxis = glfwGetJoystickAxes(Gamepad::id, & count);
        return jaxis[axis];
    }
    return 0;
}
bool Gamepad::getButtonDown(Gamepad::Buttons button)
{
    if(Gamepad::isConnected()){
        int count;
        const unsigned char* buttons = glfwGetJoystickButtons(Gamepad::id, &count);
        if(buttons[button] == GLFW_PRESS){
            return true;
        }
    }
    return false;
}
bool Gamepad::getButtonUp(Gamepad::Buttons button)
{
    if(Gamepad::isConnected()){
        int count;
        const unsigned char* buttons = glfwGetJoystickButtons(Gamepad::id, &count);
        if(buttons[button] == GLFW_RELEASE){
            return true;
        }
    }
    return false;
}