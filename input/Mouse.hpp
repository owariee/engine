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
        bool getClickDown(Mouse::Buttons button);
        bool getClick(Mouse::Buttons button);
        bool getClickUp(Mouse::Buttons button);
    private:
        bool clicked[8];
        bool noClicked[8];        
        void internalClickDown(Mouse::Buttons button);
        void internalClickUp(Mouse::Buttons button);
};

#endif //MOUSE_HPP