#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "glad/glad.h"
#include "glfw/glfw3.h"

class Window
{
    private:
        bool shouldClose;
        GLFWwindow* window;
        bool isGamepadConnected(int gamepad);   

    public:
        typedef enum {Fullscreen, Windowed, Borderless} Mode;
        typedef struct { int width, height; } Resolution;
        typedef struct { double x, y; } MousePosition;
        typedef enum {Unknow = -1, Space = 32, Apostrophe = 39, Comma = 44, Minus = 45,
                      Period = 46, Slash = 47, Number0 = 48, Number1 = 49, Number2 =50,
                      Number3 = 51, Number4 = 52, Number5 = 53, Number6 = 54, Number7 =55,
                      Number8 = 56, Number9 = 57, Semicolon = 59, Equal = 61, A = 65, 
                      B = 66, C = 67, D = 68, E = 69 , F = 70, G = 71, H = 72, I = 73,
                      J = 74, K = 75, L = 76, M = 77,N = 78, O = 79, P = 80,Q = 81,R = 82,
                      S = 83, T = 84, U = 85, V =86, W = 87, X = 88, Y = 89, Z = 90,
                      LeftBracket = 91, Backslash = 92, RightBracket = 93, GraveAccent = 96,
                      Escape = 256, Enter = 257, Tab = 258, Backspace = 259, Insert = 260,
                      Delete = 261, RightArrow = 262, LeftArrow = 263, DownArrow = 264,
                      UpArrow = 265, PageUp = 266, PageDown = 267, Home = 268, End = 269,
                      CapsLock = 280, ScrollLock = 281, NumLock = 282, PrintSc = 283,
                      Pause = 284, F1 = 290, F2 = 291, F3 = 292, F4 = 293, F5 = 294, 
                      F6 = 295, F7 = 296, F8 = 297, F9 = 298, F10 = 299, F11 = 300,
                      F12 = 301, F13 = 302, F14 = 303, F15 = 304, F16 = 305, F17 = 306,
                      F18 = 307, F19 = 308, F20 = 309, F21 = 310, F22 = 311, F23 = 312,
                      F24 = 313, F25 = 314, KP0 = 320, KP1 = 321, KP2 = 322, KP3 = 323,
                      KP4 = 324, KP5 = 325, KP6 = 326, KP7 = 327, KP8 = 328, KP9 = 329,
                      KPDecimal = 330, KPDivide = 331, KPMultiply = 332, KPSubtract = 333, 
                      KPAdd = 334, KPEnter = 335, KPEqual = 336, LeftShift = 340,
                      LeftControl = 341, LeftAlt = 342, LeftSuper = 343, RightShift = 344,
                      RighControl = 345, RightAlt = 346, RightSuper = 347, Menu = 348
                     } Keys;
        typedef enum {LeftX, LeftY, RightX, RightY, LeftTrigger, RightTrigger} GamepadAxis;
        typedef enum {Gamepad1, Gamepad2,  Gamepad3, Gamepad4, Gamepad5, Gamepad6, Gamepad7,
                      Gamepad8, Gamepad9, Gamepad10, Gamepad11, Gamepad12, Gamepad13, 
                      Gamepad14, Gamepad15, Gamepad16
                     } Gamepads;        
        typedef enum {ButtonA, ButtonB, ButtonX, ButtonY, LeftBumper, RightBumper, Back,
                      Start, Guide, LeftThumb, RightThumb, DpadUP, DpadRight, DpadDown,
                      DpadLeft
                     } GamepadButtons;
        typedef enum {Button1, Button2, Button3, Button4, Button5, Button6,Button7, Button8} MouseButtons;

        Window(const char* title, Window::Mode mode, Window::Resolution res);
        ~Window();

        bool isRunning();
        void close();
        Window::MousePosition getMousePosition();
        Window::Resolution getResolution();
        Window::Mode getMode();
        bool isKeyPressed(int key);
        bool isKeyBeingPressed(int key);
        bool isKeyReleased(int key);
        bool isGamepadButtonPressed(int gamepad, int button);
        bool isGamepadButtonBeingPressed(int gamepad, int button);
        bool isGamepadButtonReleased(int gamepad, int button);
        int getGamepadAxis(int gamepad, int axis);
        bool isMousePressed(int mouseButton);
        bool isMouseBeingPressed(int mouseButton);
        bool isMouseReleased(int mouseButton);
};

#endif//WINDOW_HPP
