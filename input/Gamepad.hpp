#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

#include "Window.hpp"
#include "Input.hpp"

class Gamepad : public Input
{
    public:
        typedef enum {LeftX, LeftY, RightX, RightY, LeftTrigger, RightTrigger} Axis;
        typedef enum {Gamepad1, Gamepad2,  Gamepad3, Gamepad4, Gamepad5, Gamepad6, Gamepad7,
                      Gamepad8, Gamepad9, Gamepad10, Gamepad11, Gamepad12, Gamepad13, 
                      Gamepad14, Gamepad15, Gamepad16
                     } Gamepads;        
        typedef enum {ButtonA, ButtonB, ButtonX, ButtonY, LeftBumper, RightBumper, Back,
                      Start, Guide, LeftThumb, RightThumb, DpadUP, DpadRight, DpadDown,
                      DpadLeft
                     } Buttons;
        Gamepad(Window* window, Gamepad::Gamepads gamepadID);
        ~Gamepad();
        bool buttonPressed(Gamepad::Buttons button);
        bool buttonBeingPressed(Gamepad::Buttons button);
        bool buttonReleased(Gamepad::Buttons button);
        int getAxis(Gamepad::Axis axis);
    private:
        Gamepad::Gamepads id;
        bool isConnected();
};

#endif