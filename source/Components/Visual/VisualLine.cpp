#include "VisualLine.h"
#include "Utility/Transform.hpp"

VisualLine::VisualLine(glm::vec3 _start, glm::vec3 _end, float _lineThickness, glm::vec3 _color, float _alpha) : VisualObject("shaders/grid/grid.vert", "shaders/grid/grid.frag", _start, glm::vec3(0.0f), _lineThickness, _color, _alpha) {
    position = _start;
    end = _end;

    vertices = {
            position.x,
            position.y,
            position.z,
            end.x,
            end.y,
            end.z
    };

    indices = {
            0, 1
    };

    VisualObject::SetupGlBuffersVerticesOnly();
}

void VisualLine::Draw(const glm::mat4& _viewProjection) {
    //bind the vertex array to draw
    glBindVertexArray(vertex_array_o);

    glm::mat4 model_matrix = glm::mat4(1.0f);
    model_matrix = Transforms::RotateDegrees(model_matrix, rotation);

    shader->Use();
    shader->SetModelMatrix(model_matrix);
    shader->SetViewProjectionMatrix(_viewProjection);

    shader->SetVec3("u_color", color.r, color.g, color.b);
    shader->SetFloat("u_alpha", alpha);

    //sets line thickness
    glLineWidth(line_thickness);

    //draw vertices according to their indices
    glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, nullptr);
}
