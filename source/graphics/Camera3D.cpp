#include "Camera3D.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Camera3D::Camera3D(int width, int height, float fov)
: yaw(-90.0f)
, pitch(0.0f)
, firstIteration(true)
, fov(fov)
, width(width)
, height(height)
{
    Camera3D::cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    Camera3D::cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
    Camera3D::generalUp = glm::vec3(0.0f, 1.0f, 0.0f);

    Camera3D::cameraRight = glm::normalize(glm::cross(Camera3D::cameraTarget, Camera3D::generalUp));
    Camera3D::cameraUp = glm::cross(Camera3D::cameraRight, Camera3D::cameraTarget);

    Camera3D::projection = glm::perspective(
        glm::radians(fov),
        (float)width/(float)height,
        0.1f, 100.0f);
}

Camera3D::~Camera3D()
{

}

glm::mat4 Camera3D::getViewMatrix()
{
    return Camera3D::projection * glm::lookAt(
        Camera3D::cameraPosition,
        Camera3D::cameraPosition + Camera3D::cameraTarget,
        Camera3D::cameraUp);
}

void Camera3D::processInput(Window* win, Keyboard* keyboard, Mouse* mouse)
{
    float velocity = 0.005f * win->getFrameTime();
    if (keyboard->getKeyDown(Keyboard::Keys::W))
    {
        Camera3D::cameraPosition += Camera3D::cameraTarget * velocity;     
    }
    if (keyboard->getKeyDown(Keyboard::Keys::S))
    {
        Camera3D::cameraPosition -= Camera3D::cameraTarget * velocity;     
    }
    if (keyboard->getKeyDown(Keyboard::Keys::A))
    {
        Camera3D::cameraPosition -= Camera3D::cameraRight * velocity;     
    }
    if (keyboard->getKeyDown(Keyboard::Keys::D))
    {
        Camera3D::cameraPosition += Camera3D::cameraRight * velocity;     
    }

    Mouse::Position mousePosition = mouse->getPosition();

    if (Camera3D::firstIteration)
    {
        Camera3D::oldMousePosition = mousePosition;
        Camera3D::firstIteration = false;
    }

    double xOffset = mousePosition.x - Camera3D::oldMousePosition.x;
    double yOffset = mousePosition.y - Camera3D::oldMousePosition.y;

    Camera3D::oldMousePosition = mousePosition;
    
    xOffset *= 0.6f;
    yOffset *= 0.6f;

    Camera3D::yaw += xOffset;
    Camera3D::pitch -= yOffset;

    if (Camera3D::pitch > 89.0f)
    {
        Camera3D::pitch = 89.0f;
    }
    if (Camera3D::pitch < -89.0f)
    {
        Camera3D::pitch = -89.0f;
    }

    if (keyboard->getKeyDown(Keyboard::Keys::Equal))
    {
        Camera3D::fov -= 0.25 * win->getFrameTime();
    }

    if (keyboard->getKeyDown(Keyboard::Keys::Minus))
    {
        Camera3D::fov += 0.25 * win->getFrameTime();
    }

    if (Camera3D::fov < 1.0f)
    {
        Camera3D::fov = 1.0f;
    }
        
    if (Camera3D::fov > 45.0f)
    {
        Camera3D::fov = 45.0f;
    } 

    if (Camera3D::oldFov != Camera3D::fov)
    {
        Camera3D::projection = glm::perspective(glm::radians(Camera3D::fov),
            (float)Camera3D::width/(float)Camera3D::height, 0.1f, 100.0f);
        Camera3D::oldFov = Camera3D::fov;
    }

    Camera3D::cameraTarget.x = cos(glm::radians(Camera3D::yaw)) * cos(glm::radians(Camera3D::pitch));
    Camera3D::cameraTarget.y = sin(glm::radians(Camera3D::pitch));
    Camera3D::cameraTarget.z = sin(glm::radians(Camera3D::yaw)) * cos(glm::radians(Camera3D::pitch));
    Camera3D::cameraTarget = glm::normalize(Camera3D::cameraTarget);
    
    Camera3D::cameraRight = glm::normalize(glm::cross(Camera3D::cameraTarget, Camera3D::generalUp));
    Camera3D::cameraUp = glm::normalize(glm::cross(Camera3D::cameraRight, Camera3D::cameraTarget));
}