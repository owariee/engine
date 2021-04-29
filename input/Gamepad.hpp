#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

class Gamepad
{
    public:
        typedef enum {LeftX, LeftY, RightX, RightY, LeftTrigger, RightTrigger} Axis;
        typedef enum {Gamepad1, Gamepad2,  Gamepad3, Gamepad4, Gamepad5, Gamepad6, Gamepad7,
                      Gamepad8, Gamepad9, Gamepad10, Gamepad11, Gamepad12, Gamepad13, 
                      Gamepad14, Gamepad15, Gamepad16
                     } Ids;
        typedef enum {ButtonA, ButtonB, ButtonX, ButtonY, LeftBumper, RightBumper, Back,
                      Start, Guide, LeftThumb, RightThumb, DpadUP, DpadRight, DpadDown,
                      DpadLeft
                     } Buttons;
        Gamepad(Gamepad::Ids gamepadID);
        ~Gamepad();
        int getAxis(Gamepad::Axis axis);
        bool getButtonDown(Gamepad::Buttons button);
        bool getButtonUp(Gamepad::Buttons button);
    private:
        Gamepad::Ids id;        
        bool isConnected();
};

#endif