#include "Input.hpp"
#include <iostream>

Input::Input(Window* window)
:window(window->window)
{
}
Input::~Input()
{
}
bool Input::hasAWindow()
{
    if(Input::window == nullptr)
    {
        std::string message = "No associated window on this entry. Maybe was deleted before the method call";
        std::cout << "[Input] " << message << std::endl;
        return false;
    }
    return true;
}