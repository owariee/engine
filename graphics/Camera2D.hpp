#ifndef CAMERA2D_HPP
#define CAMERA2D_HPP

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

class Camera2D
{
    private:
        glm::vec3 cameraPosition;
        glm::vec3 cameraTarget;
        glm::vec3 generalUp;
        glm::vec3 cameraRight;
        glm::vec3 cameraUp;
        glm::mat4 projection;
    public:
        Camera2D(int width, int height);
        ~Camera2D();

        glm::mat4 getViewMatrix();
        void updateProjectionMatrix(int width, int height);
};

#endif//CAMERA2D_HPP

