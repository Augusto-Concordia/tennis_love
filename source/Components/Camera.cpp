#include "Camera.h"
#include "Utility/Transform.hpp"

Camera::Camera() : Camera::Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f)) {}

Camera::Camera(glm::vec3 position, glm::vec3 target, float viewportWidth, float viewportHeight) {
    cam_position = position;
    cam_target = target;

    cam_forward = glm::normalize(cam_position - cam_target);
    cam_right = glm::normalize(glm::cross(cam_forward, Transforms::UP));
    cam_up = glm::normalize(glm::cross(cam_right, cam_forward));

    viewport_width = viewportWidth;
    viewport_height = viewportHeight;

    UpdateView();
    UpdateProjection();
}

void Camera::OneAxisMove(Camera::Movement movement, float amount) {
    glm::vec3 delta;

    switch (movement) {
        case UP:
            delta = amount * speed * cam_up;
            break;
        case DOWN:
            delta = -amount * speed * cam_up;
            break;
        case LEFT:
            delta = amount * speed * cam_right;
            break;
        case RIGHT:
            delta = -amount * speed * cam_right;
            break;
        case FORWARD:
            delta = -amount * speed * cam_forward;
            break;
        case BACKWARD:
            delta = amount * speed * cam_forward;
            break;
    }

    cam_target += delta;
    cam_position += delta;

    UpdateView();
}

void Camera::SetViewportSize(float width, float height) {
    viewport_width = width;
    viewport_height = height;

    UpdateProjection();
}

glm::vec3 Camera::GetPosition() const {
    return cam_position;
}

glm::mat4 Camera::GetViewProjection() const {
    return projection_matrix * view_matrix;
}

void Camera::UpdateView() {
    view_matrix = glm::lookAt(cam_position, cam_target, cam_up);
}

void Camera::UpdateProjection() {
    projection_matrix = glm::perspective(glm::radians(Camera::FOV), viewport_width / viewport_height, NEAR_PLANE, FAR_PLANE);
}
