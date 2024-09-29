#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : position(position), front(glm::vec3(0.0f, 0.0f, -1.0f)), up(up), worldUp(up), yaw(yaw), pitch(pitch), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
{
    updateCameraVectors();
}

Camera::~Camera()
{
}

glm::mat4& Camera::getViewMatrix()
{
    auto x = glm::lookAt(position, position + front, up);
    return x;
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    if (direction == FORWARD)
        position += front * velocity;
    if (direction == BACKWARD)
        position -= front * velocity;
    if (direction == LEFT)
        position -= right * velocity;
    if (direction == RIGHT)
        position += right * velocity;
    if (direction == UPWARD)
        position += up * velocity;
    if (direction == DOWNWARD)
        position -= up * velocity;
}

void Camera::processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch)
{
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::processMouseScroll(float yOffset)
{
    if (zoom >= 1.0f && zoom <= 45.0f)
        zoom -= yOffset;
    if (zoom <= 1.0f)
        zoom = 1.0f;
    if (zoom >= 45.0f)
        zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);
    right = glm::normalize(glm::cross(this->front, worldUp));
    up = glm::normalize(glm::cross(right, this->front));
}
