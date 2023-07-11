#include "VisualCube.h"
#include "Utility/Transform.hpp"

VisualCube::VisualCube(glm::vec3 _position, glm::vec3 _rotation, float _lineThickness, glm::vec3 _color, float _alpha) : VisualObject("shaders/cube/cube.vert", "shaders/cube/cube.frag", _position, _rotation, _lineThickness, _color, _alpha) {
    vertices = {
            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f,
    };

    indices = {
            0, 1, 2,
            0, 2, 3,
            3, 2, 6,
            3, 6, 7,
            0, 3, 7,
            0, 7, 4,
            0, 1, 5,
            0, 5, 4,
            5, 4, 7,
            5, 7, 6,
            1, 5, 6,
            1, 6, 2,
    };

    VisualObject::SetupGlBuffersVerticesOnly();
}

void VisualCube::Draw(const glm::mat4& _viewProjection) {
    //bind the vertex array to draw
    glBindVertexArray(vertex_array_o);

    glm::mat4 model_matrix = glm::mat4(1.0f);
    model_matrix = Transforms::RotateDegrees(model_matrix, rotation);

    shader->Use();
    shader->SetModelMatrix(model_matrix);
    shader->SetViewProjectionMatrix(_viewProjection);

    shader->SetVec3("u_color", color.r, color.g, color.b);
    shader->SetFloat("u_alpha", alpha);

    //draw vertices according to their indices
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}
