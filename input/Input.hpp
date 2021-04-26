#ifndef INPUT_HPP
#define INPUT_HPP

#include "Window.hpp"

class Input
{
    protected:
        void* window;
        bool hasAWindow();
    public:
        Input(Window* window);
        ~Input();
};

#endif