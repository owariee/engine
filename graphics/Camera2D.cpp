#include "Camera2D.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Camera2D::Camera2D(int width, int height)
{
    Camera2D::cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    Camera2D::cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
    Camera2D::generalUp = glm::vec3(0.0f, 1.0f, 0.0f);

    Camera2D::cameraRight = glm::normalize(glm::cross(Camera2D::cameraTarget, Camera2D::generalUp));
    Camera2D::cameraUp = glm::cross(Camera2D::cameraRight, Camera2D::cameraTarget);

    Camera2D::projection = glm::ortho(
        0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, 0.1f, 100.0f);
}

Camera2D::~Camera2D()
{

}

glm::mat4 Camera2D::getViewMatrix()
{
    return Camera2D::projection * glm::lookAt(
        Camera2D::cameraPosition,
        Camera2D::cameraPosition + Camera2D::cameraTarget,
        Camera2D::cameraUp);
}

void Camera2D::processInput(Window* win)
{
    float velocity = 0.5f * win->getFrameTime();
    if (win->isKeyPressed(Window::Keys::W))
    {
        Camera2D::cameraPosition -= Camera2D::cameraUp * velocity;     
    }
    if (win->isKeyPressed(Window::Keys::S))
    {
        Camera2D::cameraPosition += Camera2D::cameraUp * velocity;     
    }
    if (win->isKeyPressed(Window::Keys::A))
    {
        Camera2D::cameraPosition -= Camera2D::cameraRight * velocity;     
    }
    if (win->isKeyPressed(Window::Keys::D))
    {
        Camera2D::cameraPosition += Camera2D::cameraRight * velocity;     
    }
}
