#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "Window.hpp"
#include "Input.hpp"

class Mouse : public Input
{
    public:
        typedef struct { double x, y; } Position;
        typedef enum{ Button1, Button2, Button3, Button4, Button5, Button6,Button7, Button8} Buttons;
        Mouse(Window** window);
        ~Mouse();
        Mouse::Position getPosition();     
        bool getButtonClick(Mouse::Buttons button);
        bool getButtonUnclick(Mouse::Buttons button);
};

#endif //MOUSE_HPP