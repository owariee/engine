#include "AudioSource.hpp"
#include "Window.hpp"
#include "glm/mat4x4.hpp"

#include <glm/ext/matrix_float4x4.hpp>
#include <iostream>

int main() {
    Window win("Test", Window::Mode::Windowed, {800, 600});
    glm::mat4x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    while(win.isRunning()) {
        if(win.mouse->getClick(Mouse::Buttons::Button1)) {
            std::cout << "cringe" << std::endl;
        }
    }

    return 0;
}

