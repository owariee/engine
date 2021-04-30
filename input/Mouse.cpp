#include "Mouse.hpp"

#include "GLFW/glfw3.h"

Mouse::Mouse(Window** window)
:Input(window)
{
    for(int i = 0; i < 8; i++){
        clicked[i] = false;
        noClicked[i] = true;
    }
}
Mouse::~Mouse()
{
}
void Mouse::internalClickDown(Mouse::Buttons button)
{
    if (Mouse::hasAWindow()) {
        int state = glfwGetMouseButton(((GLFWwindow*)(((Window*)(*(Mouse::window)))->getWindowId())), button);
        if (state == GLFW_PRESS) {
            if (!Mouse::noClicked[button]) {
                Mouse::noClicked[button] = true;
            }
        }
    }
}
void Mouse::internalClickUp(Mouse::Buttons button)
{
    if (Mouse::hasAWindow()) {
        int state = glfwGetMouseButton(((GLFWwindow*)(((Window*)(*(Mouse::window)))->getWindowId())), button);
        if (state == GLFW_RELEASE) {
            if (Mouse::clicked[button]) {
                Mouse::clicked[button] = false;
            }
        }
    }
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
bool Mouse::getClickDown(Mouse::Buttons button)
{
    bool result = false;    
    if(Mouse::hasAWindow()){
        int state = glfwGetMouseButton(((GLFWwindow*)(((Window*)(*(Mouse::window)))->getWindowId())), button);
        if(state == GLFW_PRESS) {
            if(!Mouse::clicked[button]){
                result = true;
                Mouse::clicked[button] = true;
            }
        }
    }
    Mouse::internalClickUp(button);
    return result;
}
bool Mouse::getClick(Mouse::Buttons button)
{
    if(Mouse::hasAWindow()){
        int state = glfwGetMouseButton(((GLFWwindow*)(((Window*)(*(Mouse::window)))->getWindowId())), button);
        if(state == GLFW_PRESS) { 
            return true;
        }
    }
    return false;
}
bool Mouse::getClickUp(Mouse::Buttons button)
{
    Mouse::internalClickDown(button);
    bool result = false;
    if(Mouse::hasAWindow()){
        int state = glfwGetMouseButton(((GLFWwindow*)(((Window*)(*(Mouse::window)))->getWindowId())), button);
        if(state == GLFW_RELEASE) {
            if(Mouse::noClicked[button]){
                result = true;
                Mouse::noClicked[button] = false;
            }
        }
    }
    return result;
}











// 1 forma de fazer funcionar
// Window* tmpWindow = reinterpret_cast<Window*>(*(Mouse::window));
// GLFWwindow* tmpGLFW = reinterpret_cast<GLFWwindow*>(tmpWindow->getWindowId());

// 2 forma de fazer funcionar
// ((GLFWwindow*)(((Window*)(*(Mouse::window)))->getWindowId()))

// as duas fazem a mesma coisa, so terminar de trocar dos outros BELEZA