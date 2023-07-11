#pragma once

#include <iostream>
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

class Camera {
public:
    enum Movement {
        FORWARD,
        BACKWARD,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    float speed = 4.5f;

    const float FOV = 75.0f;
    const float NEAR_PLANE = 0.1f;
    const float FAR_PLANE = 100.0f;

public:
    Camera();

    Camera(glm::vec3 position, glm::vec3 target, float viewportWidth = 1280, float viewportHeight = 720);

    void OneAxisMove(Movement movement, float delta);

    void SetViewportSize(float width, float height);

    [[nodiscard]] glm::vec3 GetPosition() const;
    [[nodiscard]] glm::mat4 GetViewProjection() const;

private:
    void UpdateProjection(); //for when the camera's viewport changes (mainly)
    void UpdateView(); //for when the camera's rotation changes

private:
    glm::vec3 cam_position;
    glm::vec3 cam_target;

    glm::vec3 cam_up;
    glm::vec3 cam_right;
    glm::vec3 cam_forward;

    float viewport_height;
    float viewport_width;

    glm::mat4 view_matrix = glm::mat4(1.0f);
    glm::mat4 projection_matrix = glm::mat4(1.0f);
};
