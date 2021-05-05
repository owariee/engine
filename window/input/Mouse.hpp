#ifndef MOUSE_HPP
#define MOUSE_HPP

class Mouse
{
    friend class Window;
    public:
        typedef struct { double x, y; } Position;
        typedef enum{ Button1, Button2, Button3, Button4, Button5, Button6,Button7, Button8} Buttons;
        Mouse::Position getPosition();     
        bool getClickDown(Mouse::Buttons button);
        bool getClick(Mouse::Buttons button);
        bool getClickUp(Mouse::Buttons button);
    private:
        void* window;
        bool clicked[8];
        bool noClicked[8];
        void internalClickDown(Mouse::Buttons button);
        void internalClickUp(Mouse::Buttons button);
        Mouse(void* window);
        ~Mouse();
};

#endif //MOUSE_HPP