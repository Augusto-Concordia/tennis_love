#pragma once

#include <memory>
#include <vector>
#include "glm/vec3.hpp"
#include "Components/Shader.h"

class VisualObject {
public:
    glm::vec3 position, rotation, scale;

    Shader::Descriptor shader_descriptor;

protected:
    std::shared_ptr<Shader> shader;

    std::vector<float> vertices;
    std::vector<int> indices;

    GLuint vertex_array_o;
    GLuint vertex_buffer_o;
    GLuint element_buffer_o;

public:
    //todo: create various constructors that have different parameters (for higher flexibility)
    explicit VisualObject(glm::vec3 _position = glm::vec3(0.0f), glm::vec3 _rotation = glm::vec3(0.0f), glm::vec3 _scale = glm::vec3(1.0f), Shader::Descriptor _descriptor = Shader::Descriptor());

    //todo: add a way of drawing the object directly with a matrix
    virtual void Draw(const glm::mat4& _viewProjection, const glm::vec3 &_cameraPosition) = 0;

protected:
    virtual void SetupGlBuffersVerticesOnly();
    virtual void SetupGlBuffersVerticesAndNormalsOnlyNoIndices();
};
