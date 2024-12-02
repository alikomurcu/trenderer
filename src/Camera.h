#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 300.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UPWARD,
    DOWNWARD
};

class Camera
{
public:
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, int width, int height);
    ~Camera();

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    int width, height;
    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    glm::mat4& getViewMatrix();
    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);
    void processMouseScroll(float yOffset);

private:
    void updateCameraVectors();
};