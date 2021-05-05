#include "Mouse.hpp"

#include "GLFW/glfw3.h"

Mouse::Mouse(void* window)
:window(window)
{
    for(int i = 0; i < 8; i++){
        clicked[i] = false;
        noClicked[i] = false;
    }
}
Mouse::~Mouse()
{
}
void Mouse::internalClickDown(Mouse::Buttons button)
{
    int state = glfwGetMouseButton(reinterpret_cast<GLFWwindow*>(Mouse::window), button);
    if (state == GLFW_PRESS) {
        if (!Mouse::noClicked[button]) {
            Mouse::noClicked[button] = true;
        }
    }
}
void Mouse::internalClickUp(Mouse::Buttons button)
{
    int state = glfwGetMouseButton(reinterpret_cast<GLFWwindow*>(Mouse::window), button);
    if (state == GLFW_RELEASE) {
        if (Mouse::clicked[button]) {
            Mouse::clicked[button] = false;
        }
    }
}
Mouse::Position Mouse::getPosition() 
{
    Mouse::Position mousepostemp = { 0, 0 };       
    glfwGetCursorPos(reinterpret_cast<GLFWwindow*>(Mouse::window),
            &(mousepostemp.x), &(mousepostemp.y));
    return mousepostemp;
}
bool Mouse::getClickDown(Mouse::Buttons button)
{
    bool result = false;    
    int state = glfwGetMouseButton(reinterpret_cast<GLFWwindow*>(Mouse::window), button);
    if(state == GLFW_PRESS) {
        if(!Mouse::clicked[button]){
            result = true;
            Mouse::clicked[button] = true;
        }
    }
    Mouse::internalClickUp(button);
    return result;
}
bool Mouse::getClick(Mouse::Buttons button)
{
    int state = glfwGetMouseButton(reinterpret_cast<GLFWwindow*>(Mouse::window), button);
    if(state == GLFW_PRESS) { 
        return true;
    }
    return false;
}
bool Mouse::getClickUp(Mouse::Buttons button)
{
    Mouse::internalClickDown(button);
    bool result = false;
    int state = glfwGetMouseButton(reinterpret_cast<GLFWwindow*>(Mouse::window), button);
    if(state == GLFW_RELEASE) {
        if(Mouse::noClicked[button]){
            result = true;
            Mouse::noClicked[button] = false;
        }
    }
    return result;
}