#ifndef CAMERA3D_HPP
#define CAMERA3D_HPP

#include "Window.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

class Camera3D
{
    private:
        glm::vec3 cameraPosition;
        glm::vec3 cameraTarget;
        glm::vec3 generalUp;
        glm::vec3 cameraRight;
        glm::vec3 cameraUp;
        glm::mat4 projection;

        double yaw;
        double pitch;

        float fov;
        float oldFov;

        int width;
        int height;

        bool firstIteration;

        Mouse::Position oldMousePosition;
    public:
        Camera3D(int width, int height, float fov);
        ~Camera3D();

        glm::mat4 getViewMatrix();

        void processInput(Window* win, Keyboard* keyboard, Mouse* mouse);
};

#endif//CAMERA3D_HPP