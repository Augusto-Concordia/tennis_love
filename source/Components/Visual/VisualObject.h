#pragma once

#include <memory>
#include <vector>
#include "glm/vec3.hpp"
#include "Components/Shader.h"

class VisualObject {
public:
    glm::vec3 position, rotation, scale;

    float line_thickness;

    glm::vec3 color;
    float alpha;

protected:
    std::shared_ptr<Shader> shader;

    std::vector<float> vertices;
    std::vector<int> indices;

    GLuint vertex_array_o;
    GLuint vertex_buffer_o;
    GLuint element_buffer_o;

public:
    //todo: create various constructors that have different parameters (for higher flexibility)
    explicit VisualObject(const char* _vertShaderSource = "shaders/default.vert", const char* _fragShaderSource = "shaders/default.frag", glm::vec3 _position = glm::vec3(0.0f), glm::vec3 _rotation = glm::vec3(0.0f), glm::vec3 _scale = glm::vec3(1.0f), float _lineThickness = 1.0f, glm::vec3 _color = glm::vec3(1.0f), float _alpha = 1.0f);

    //todo: add a way of drawing the object directly with a matrix
    virtual void Draw(const glm::mat4& _viewProjection, const glm::vec3 &_cameraPosition) = 0;

protected:
    virtual void SetupGlBuffersVerticesOnly();
    virtual void SetupGlBuffersVerticesAndNormalsOnlyNoIndices();
};
