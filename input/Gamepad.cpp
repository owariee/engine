#include "Gamepad.hpp"

#include <iostream>
#include "GLFW/glfw3.h"

Gamepad::Gamepad(Ids gamepadID)
:id(gamepadID)
{
    for (int i = 0; i < 15; i++) {
        Gamepad::clicked[i] = false;
        Gamepad::noClicked[i] = false;
    }
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
void Gamepad::internalButtonDown(Gamepad::Buttons button)
{
    if (Gamepad::isConnected()) {
        int count;
        const unsigned char* buttons = glfwGetJoystickButtons(Gamepad::id, &count);
        if (buttons[button] == GLFW_PRESS) {
            if (!Gamepad::noClicked[button]) {
                Gamepad::noClicked[button] = true;
            }
        }
    }
}
void Gamepad::internalButtonUp(Gamepad::Buttons button)
{
    if (Gamepad::isConnected()) {
        int count;
        const unsigned char* buttons = glfwGetJoystickButtons(Gamepad::id, &count);
        if (buttons[button] == GLFW_RELEASE) {
            if (Gamepad::clicked[button]) {
                Gamepad::clicked[button] = false;
            }
        }
    }
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
    bool result = false;
    if(Gamepad::isConnected()){
        int count;
        const unsigned char* buttons = glfwGetJoystickButtons(Gamepad::id, &count);
        if(buttons[button] == GLFW_PRESS){
            if (!Gamepad::clicked[button]) {
                result = true;
                Gamepad::clicked[button] = true;
            }
        }
    }
    Gamepad::internalButtonUp(button);
    return result;
}
bool Gamepad::getButton(Gamepad::Buttons button)
{
    if (Gamepad::isConnected()) {
        int count;
        const unsigned char* buttons = glfwGetJoystickButtons(Gamepad::id, &count);
        if (buttons[button] == GLFW_PRESS) {
            return true;
        }
    }
    return false;
}
bool Gamepad::getButtonUp(Gamepad::Buttons button)
{
    Gamepad::internalButtonDown(button);
    bool result = false;
    if(Gamepad::isConnected()){
        int count;
        const unsigned char* buttons = glfwGetJoystickButtons(Gamepad::id, &count);
        if(buttons[button] == GLFW_RELEASE){
            if (Gamepad::noClicked[button]) {
                result = true;
                Gamepad::noClicked[button] = false;
            }
        }
    }
    return result;
}