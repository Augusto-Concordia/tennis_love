#include "Camera.h"
#include "Utility/Constants.h"

Camera::Camera() : Camera::Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f)) {}

Camera::Camera(glm::vec3 position, glm::vec3 target) {
    cam_position = position;
    cam_target = target;

    cam_forward = glm::normalize(cam_position - cam_target);
    cam_right = glm::normalize(glm::cross(cam_forward, Constants::UP));
    cam_up = glm::normalize(glm::cross(cam_right, cam_forward));

    UpdateView();
    UpdateProjection();
}

void Camera::OneAxisMove(Camera::Movement movement, float amount) {
    glm::vec3 delta;

    switch (movement) {
        case UP:
            delta = amount * speed * cam_up; //up because we are in a 2D view of sorts
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

    cam_position.z = glm::clamp(cam_position.z, 0.0f, Camera::FAR_PLANE);
    cam_target.z = glm::clamp(cam_target.z, cam_position.z - 1.0f,
                              Camera::FAR_PLANE); //the target distance from the camera, does not matter in a 2D context

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
