#pragma once

#include <vector>
#include "glm/vec3.hpp"
#include "glad/glad.h"
#include "Components/Shader.h"
#include "Components/Camera.h"

class VisualGrid {
public:
    float cell_size, thickness;
    int width, height;
    glm::vec3 position, rotation;

private:
    std::shared_ptr<Shader> shader;

    std::vector<float> vertices;
    std::vector<int> indices;

    GLuint vertex_array_o;
    GLuint vertex_buffer_o;
    GLuint element_buffer_o;

public:
    VisualGrid(int width, int height, float cellSize = 1.0f, float thickness = 1.0f, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rotation = glm::vec3(1.0f, 1.0f, 1.0f));

    void Draw(const glm::mat4& viewProjection);
};