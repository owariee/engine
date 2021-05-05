#include "Keyboard.hpp"

#include "GLFW/glfw3.h"

Keyboard::Keyboard(void* window)
    :window(window)
{
    Keyboard::clicked[Keyboard::Unknow] = false;
    Keyboard::noClicked[Keyboard::Unknow] = false;
    Keyboard::clicked[Keyboard::Space] = false;
    Keyboard::noClicked[Keyboard::Space] = false;
    Keyboard::clicked[Keyboard::Apostrophe] = false;
    Keyboard::noClicked[Keyboard::Apostrophe] = false;
    Keyboard::clicked[Keyboard::Comma] = false;
    Keyboard::noClicked[Keyboard::Comma] = false;
    Keyboard::clicked[Keyboard::Minus] = false;
    Keyboard::noClicked[Keyboard::Minus] = false;
    Keyboard::clicked[Keyboard::Period] = false;
    Keyboard::noClicked[Keyboard::Period] = false;
    Keyboard::clicked[Keyboard::Slash] = false;
    Keyboard::noClicked[Keyboard::Slash] = false;
    Keyboard::clicked[Keyboard::Number0] = false;
    Keyboard::noClicked[Keyboard::Number0] = false;
    Keyboard::clicked[Keyboard::Number1] = false;
    Keyboard::noClicked[Keyboard::Number1] = false;
    Keyboard::clicked[Keyboard::Number2] = false;
    Keyboard::noClicked[Keyboard::Number2] = false;
    Keyboard::clicked[Keyboard::Number3] = false;
    Keyboard::noClicked[Keyboard::Number3] = false;
    Keyboard::clicked[Keyboard::Number4] = false;
    Keyboard::noClicked[Keyboard::Number4] = false;
    Keyboard::clicked[Keyboard::Number5] = false;
    Keyboard::noClicked[Keyboard::Number5] = false;
    Keyboard::clicked[Keyboard::Number6] = false;
    Keyboard::noClicked[Keyboard::Number6] = false;
    Keyboard::clicked[Keyboard::Number7] = false;
    Keyboard::noClicked[Keyboard::Number7] = false;
    Keyboard::clicked[Keyboard::Number8] = false;
    Keyboard::noClicked[Keyboard::Number8] = false;
    Keyboard::clicked[Keyboard::Number9] = false;
    Keyboard::noClicked[Keyboard::Number9] = false;
    Keyboard::clicked[Keyboard::Semicolon] = false;
    Keyboard::noClicked[Keyboard::Semicolon] = false;
    Keyboard::clicked[Keyboard::A] = false;
    Keyboard::noClicked[Keyboard::A] = false;
    Keyboard::clicked[Keyboard::B] = false;
    Keyboard::noClicked[Keyboard::B] = false;
    Keyboard::clicked[Keyboard::C] = false;
    Keyboard::noClicked[Keyboard::C] = false;
    Keyboard::clicked[Keyboard::D] = false;
    Keyboard::noClicked[Keyboard::D] = false;
    Keyboard::clicked[Keyboard::E] = false;
    Keyboard::noClicked[Keyboard::E] = false;
    Keyboard::clicked[Keyboard::F] = false;
    Keyboard::noClicked[Keyboard::F] = false;
    Keyboard::clicked[Keyboard::G] = false;
    Keyboard::noClicked[Keyboard::G] = false;
    Keyboard::clicked[Keyboard::H] = false;
    Keyboard::noClicked[Keyboard::H] = false;
    Keyboard::clicked[Keyboard::I] = false;
    Keyboard::noClicked[Keyboard::I] = false;
    Keyboard::clicked[Keyboard::J] = false;
    Keyboard::noClicked[Keyboard::J] = false;
    Keyboard::clicked[Keyboard::K] = false;
    Keyboard::noClicked[Keyboard::K] = false;
    Keyboard::clicked[Keyboard::L] = false;
    Keyboard::noClicked[Keyboard::L] = false;
    Keyboard::clicked[Keyboard::M] = false;
    Keyboard::noClicked[Keyboard::M] = false;
    Keyboard::clicked[Keyboard::N] = false;
    Keyboard::noClicked[Keyboard::N] = false;
    Keyboard::clicked[Keyboard::O] = false;
    Keyboard::noClicked[Keyboard::O] = false;
    Keyboard::clicked[Keyboard::P] = false;
    Keyboard::noClicked[Keyboard::P] = false;
    Keyboard::clicked[Keyboard::Q] = false;
    Keyboard::noClicked[Keyboard::Q] = false;
    Keyboard::clicked[Keyboard::R] = false;
    Keyboard::noClicked[Keyboard::R] = false;
    Keyboard::clicked[Keyboard::S] = false;
    Keyboard::noClicked[Keyboard::S] = false;
    Keyboard::clicked[Keyboard::T] = false;
    Keyboard::noClicked[Keyboard::T] = false;
    Keyboard::clicked[Keyboard::U] = false;
    Keyboard::noClicked[Keyboard::U] = false;
    Keyboard::clicked[Keyboard::V] = false;
    Keyboard::noClicked[Keyboard::V] = false;
    Keyboard::clicked[Keyboard::W] = false;
    Keyboard::noClicked[Keyboard::W] = false;
    Keyboard::clicked[Keyboard::X] = false;
    Keyboard::noClicked[Keyboard::X] = false;
    Keyboard::clicked[Keyboard::Y] = false;
    Keyboard::noClicked[Keyboard::Y] = false;
    Keyboard::clicked[Keyboard::Z] = false;
    Keyboard::noClicked[Keyboard::Z] = false;
    Keyboard::clicked[Keyboard::LeftBracket] = false;
    Keyboard::noClicked[Keyboard::LeftBracket] = false;
    Keyboard::clicked[Keyboard::Backslash] = false;
    Keyboard::noClicked[Keyboard::Backslash] = false;
    Keyboard::clicked[Keyboard::RightBracket] = false;
    Keyboard::noClicked[Keyboard::RightBracket] = false;
    Keyboard::clicked[Keyboard::GraveAccent] = false;
    Keyboard::noClicked[Keyboard::GraveAccent] = false;
    Keyboard::clicked[Keyboard::Escape] = false;
    Keyboard::noClicked[Keyboard::Escape] = false;
    Keyboard::clicked[Keyboard::Enter] = false;
    Keyboard::noClicked[Keyboard::Enter] = false;
    Keyboard::clicked[Keyboard::Tab] = false;
    Keyboard::noClicked[Keyboard::Tab] = false;
    Keyboard::clicked[Keyboard::Backspace] = false;
    Keyboard::noClicked[Keyboard::Backspace] = false;
    Keyboard::clicked[Keyboard::Insert] = false;
    Keyboard::noClicked[Keyboard::Insert] = false;
    Keyboard::clicked[Keyboard::Delete] = false;
    Keyboard::noClicked[Keyboard::Delete] = false;
    Keyboard::clicked[Keyboard::RightArrow] = false;
    Keyboard::noClicked[Keyboard::RightArrow] = false;
    Keyboard::clicked[Keyboard::LeftArrow] = false;
    Keyboard::noClicked[Keyboard::LeftArrow] = false;
    Keyboard::clicked[Keyboard::DownArrow] = false;
    Keyboard::noClicked[Keyboard::DownArrow] = false;
    Keyboard::clicked[Keyboard::UpArrow] = false;
    Keyboard::noClicked[Keyboard::UpArrow] = false;
    Keyboard::clicked[Keyboard::PageUp] = false;
    Keyboard::noClicked[Keyboard::PageUp] = false;
    Keyboard::clicked[Keyboard::PageDown] = false;
    Keyboard::noClicked[Keyboard::PageDown] = false;
    Keyboard::clicked[Keyboard::Home] = false;
    Keyboard::noClicked[Keyboard::Home] = false;
    Keyboard::clicked[Keyboard::End] = false;
    Keyboard::noClicked[Keyboard::End] = false;
    Keyboard::clicked[Keyboard::CapsLock] = false;
    Keyboard::noClicked[Keyboard::CapsLock] = false;
    Keyboard::clicked[Keyboard::ScrollLock] = false;
    Keyboard::noClicked[Keyboard::ScrollLock] = false;
    Keyboard::clicked[Keyboard::NumLock] = false;
    Keyboard::noClicked[Keyboard::NumLock] = false;
    Keyboard::clicked[Keyboard::PrintSc] = false;
    Keyboard::noClicked[Keyboard::PrintSc] = false;
    Keyboard::clicked[Keyboard::Pause] = false;
    Keyboard::noClicked[Keyboard::Pause] = false;
    Keyboard::clicked[Keyboard::F1] = false;
    Keyboard::noClicked[Keyboard::F1] = false;
    Keyboard::clicked[Keyboard::F2] = false;
    Keyboard::noClicked[Keyboard::F2] = false;
    Keyboard::clicked[Keyboard::F3] = false;
    Keyboard::noClicked[Keyboard::F3] = false;
    Keyboard::clicked[Keyboard::F4] = false;
    Keyboard::noClicked[Keyboard::F4] = false;
    Keyboard::clicked[Keyboard::F5] = false;
    Keyboard::noClicked[Keyboard::F5] = false;
    Keyboard::clicked[Keyboard::F6] = false;
    Keyboard::noClicked[Keyboard::F6] = false;
    Keyboard::clicked[Keyboard::F7] = false;
    Keyboard::noClicked[Keyboard::F7] = false;
    Keyboard::clicked[Keyboard::F8] = false;
    Keyboard::noClicked[Keyboard::F8] = false;
    Keyboard::clicked[Keyboard::F9] = false;
    Keyboard::noClicked[Keyboard::F9] = false;
    Keyboard::clicked[Keyboard::F10] = false;
    Keyboard::noClicked[Keyboard::F10] = false;
    Keyboard::clicked[Keyboard::F11] = false;
    Keyboard::noClicked[Keyboard::F11] = false;
    Keyboard::clicked[Keyboard::F12] = false;
    Keyboard::noClicked[Keyboard::F12] = false;
    Keyboard::clicked[Keyboard::F13] = false;
    Keyboard::noClicked[Keyboard::F13] = false;
    Keyboard::clicked[Keyboard::F14] = false;
    Keyboard::noClicked[Keyboard::F14] = false;
    Keyboard::clicked[Keyboard::F15] = false;
    Keyboard::noClicked[Keyboard::F15] = false;
    Keyboard::clicked[Keyboard::F16] = false;
    Keyboard::noClicked[Keyboard::F16] = false;
    Keyboard::clicked[Keyboard::F17] = false;
    Keyboard::noClicked[Keyboard::F17] = false;
    Keyboard::clicked[Keyboard::F18] = false;
    Keyboard::noClicked[Keyboard::F18] = false;
    Keyboard::clicked[Keyboard::F19] = false;
    Keyboard::noClicked[Keyboard::F19] = false;
    Keyboard::clicked[Keyboard::F20] = false;
    Keyboard::noClicked[Keyboard::F20] = false;
    Keyboard::clicked[Keyboard::F21] = false;
    Keyboard::noClicked[Keyboard::F21] = false;
    Keyboard::clicked[Keyboard::F22] = false;
    Keyboard::noClicked[Keyboard::F22] = false;
    Keyboard::clicked[Keyboard::F23] = false;
    Keyboard::noClicked[Keyboard::F23] = false;
    Keyboard::clicked[Keyboard::F24] = false;
    Keyboard::noClicked[Keyboard::F24] = false;
    Keyboard::clicked[Keyboard::F25] = false;
    Keyboard::noClicked[Keyboard::F25] = false;
    Keyboard::clicked[Keyboard::KP0] = false;
    Keyboard::noClicked[Keyboard::KP0] = false;
    Keyboard::clicked[Keyboard::KP1] = false;
    Keyboard::noClicked[Keyboard::KP1] = false;
    Keyboard::clicked[Keyboard::KP2] = false;
    Keyboard::noClicked[Keyboard::KP2] = false;
    Keyboard::clicked[Keyboard::KP3] = false;
    Keyboard::noClicked[Keyboard::KP3] = false;
    Keyboard::clicked[Keyboard::KP4] = false;
    Keyboard::noClicked[Keyboard::KP4] = false;
    Keyboard::clicked[Keyboard::KP5] = false;
    Keyboard::noClicked[Keyboard::KP5] = false;
    Keyboard::clicked[Keyboard::KP6] = false;
    Keyboard::noClicked[Keyboard::KP6] = false;
    Keyboard::clicked[Keyboard::KP7] = false;
    Keyboard::noClicked[Keyboard::KP7] = false;
    Keyboard::clicked[Keyboard::KP8] = false;
    Keyboard::noClicked[Keyboard::KP8] = false;
    Keyboard::clicked[Keyboard::KP9] = false;
    Keyboard::noClicked[Keyboard::KP9] = false;
    Keyboard::clicked[Keyboard::KPDecimal] = false;
    Keyboard::noClicked[Keyboard::KPDecimal] = false;
    Keyboard::clicked[Keyboard::KPDivide] = false;
    Keyboard::noClicked[Keyboard::KPDivide] = false;
    Keyboard::clicked[Keyboard::KPMultiply] = false;
    Keyboard::noClicked[Keyboard::KPMultiply] = false;
    Keyboard::clicked[Keyboard::KPSubtract] = false;
    Keyboard::noClicked[Keyboard::KPSubtract] = false;
    Keyboard::clicked[Keyboard::KPAdd] = false;
    Keyboard::noClicked[Keyboard::KPAdd] = false;
    Keyboard::clicked[Keyboard::KPEnter] = false;
    Keyboard::noClicked[Keyboard::KPEnter] = false;
    Keyboard::clicked[Keyboard::KPEqual] = false;
    Keyboard::noClicked[Keyboard::KPEqual] = false;
    Keyboard::clicked[Keyboard::LeftShift] = false;
    Keyboard::noClicked[Keyboard::LeftShift] = false;
    Keyboard::clicked[Keyboard::LeftControl] = false;
    Keyboard::noClicked[Keyboard::LeftControl] = false;
    Keyboard::clicked[Keyboard::LeftAlt] = false;
    Keyboard::noClicked[Keyboard::LeftAlt] = false;
    Keyboard::clicked[Keyboard::LeftSuper] = false;
    Keyboard::noClicked[Keyboard::LeftSuper] = false;
    Keyboard::clicked[Keyboard::RightShift] = false;
    Keyboard::noClicked[Keyboard::RightShift] = false;
    Keyboard::clicked[Keyboard::RighControl] = false;
    Keyboard::noClicked[Keyboard::RighControl] = false;
    Keyboard::clicked[Keyboard::RightAlt] = false;
    Keyboard::noClicked[Keyboard::RightAlt] = false;
    Keyboard::clicked[Keyboard::RightSuper] = false;
    Keyboard::noClicked[Keyboard::RightSuper] = false;
    Keyboard::clicked[Keyboard::Menu] = false;
    Keyboard::noClicked[Keyboard::Menu] = false;
}
Keyboard::~Keyboard()
{
}
void Keyboard::internalKeyDown(Keyboard::Keys key)
{
    int state = glfwGetKey(reinterpret_cast<GLFWwindow*>(Keyboard::window), key);
    if (state == GLFW_PRESS) {
        if (!Keyboard::noClicked[key]) {
            Keyboard::noClicked[key] = true;
        }
    }
}
void Keyboard::internalKeyUp(Keyboard::Keys key)
{
    int state = glfwGetKey(reinterpret_cast<GLFWwindow*>(Keyboard::window), key);
    if (state == GLFW_RELEASE) {
        if (Keyboard::clicked[key]) {
            Keyboard::clicked[key] = false;
        }
    }
}
bool Keyboard::getKeyDown(Keyboard::Keys key)
{
    bool result = false;
    int state = glfwGetKey(reinterpret_cast<GLFWwindow*>(Keyboard::window), key);
    if(state == GLFW_PRESS) {
        if (!Keyboard::clicked[key]) {
            result = true;
            Keyboard::clicked[key] = true;
        }
    }
    Keyboard::internalKeyUp(key);
    return result;
}
bool Keyboard::getKey(Keyboard::Keys key)
{
    int state = glfwGetKey(reinterpret_cast<GLFWwindow*>(Keyboard::window), key);
    if (state == GLFW_PRESS) {
        return true;
    }
    return false;
}
bool Keyboard::getKeyUp(Keyboard::Keys key)
{
    Keyboard::internalKeyDown(key);
    bool result = false;
    int state = glfwGetKey(reinterpret_cast<GLFWwindow*>(Keyboard::window), key);
    if (state == GLFW_RELEASE) {
        if (Keyboard::noClicked[key]) {
            result = true;
            Keyboard::noClicked[key] = false;
        }
    }
    return result;
}