#include "Camera.h"
#include "Utility/Transform.hpp"

Camera::Camera() : Camera::Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f)) {}

Camera::Camera(glm::vec3 _position, glm::vec3 _target, float _viewportWidth, float _viewportHeight) {
    cam_position = _position;
    cam_target = _target;

    cam_forward = glm::normalize(cam_position - cam_target);
    cam_right = glm::normalize(glm::cross(cam_forward, Transforms::UP));
    cam_up = glm::normalize(glm::cross(cam_right, cam_forward));

    viewport_width = _viewportWidth;
    viewport_height = _viewportHeight;

    UpdateView();
    UpdateProjection();
}

void Camera::OneAxisMove(Camera::Movement _movement, float _amount) {
    glm::vec3 delta;

    switch (_movement) {
        case UP:
            delta = _amount * speed * cam_up;
            break;
        case DOWN:
            delta = -_amount * speed * cam_up;
            break;
        case LEFT:
            delta = _amount * speed * cam_right;
            break;
        case RIGHT:
            delta = -_amount * speed * cam_right;
            break;
        case FORWARD:
            delta = -_amount * speed * cam_forward;
            break;
        case BACKWARD:
            delta = _amount * speed * cam_forward;
            break;
    }

    cam_target += delta;
    cam_position += delta;

    UpdateView();
}

void Camera::SetViewportSize(float _width, float _height) {
    viewport_width = _width;
    viewport_height = _height;

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
