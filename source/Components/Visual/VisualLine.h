#pragma once

#include <memory>
#include <vector>
#include "glm/vec3.hpp"
#include "Components/Shader.h"

class VisualLine {
public:
    glm::vec3 start, end;

    float thickness;
    glm::vec3 color;
    float alpha;

private:
    std::shared_ptr<Shader> shader;

    std::vector<float> vertices;
    std::vector<int> indices;

    GLuint vertex_array_o;
    GLuint vertex_buffer_o;
    GLuint element_buffer_o;

public:
    explicit VisualLine(glm::vec3 start = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 end = glm::vec3(1.0f, 1.0f, 1.0f), float thickness = 1.0f, glm::vec3 color = glm::vec3(1.0f), float alpha = 1.0f);

    void Draw(const glm::mat4& viewProjection);
};
