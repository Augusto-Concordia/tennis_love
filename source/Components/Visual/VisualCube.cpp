#include "VisualCube.h"
#include "Utility/Transform.hpp"

VisualCube::VisualCube(glm::vec3 _position, glm::vec3 _rotation, float _lineThickness, glm::vec3 _color, float _alpha) : VisualObject("shaders/cube/cube.vert", "shaders/cube/cube.frag", _position, _rotation, _lineThickness, _color, _alpha) {
    //vertices with their normals
    vertices = {
            //top face, top triangle
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

            //top face, bottom triangle
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

            //right side, top triangle
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

            //right side, bottom triangle
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

            //front side, top triangle
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,

            //front side, bottom triangle
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,

            //left side, top triangle
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,

            //left side, bottom triangle
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,

            //back side, top triangle
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

            //back side, bottom triangle
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

            //bottom face, top triangle
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

            //bottom face, bottom triangle
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    };

    VisualObject::SetupGlBuffersVerticesAndNormalsOnlyNoIndices();
}

void VisualCube::Draw(const glm::mat4& _viewProjection, const glm::vec3 &_cameraPosition) {
    //bind the vertex array to draw
    glBindVertexArray(vertex_array_o);

    glm::mat4 model_matrix = glm::mat4(1.0f);
    model_matrix = Transforms::RotateDegrees(model_matrix, rotation);

    shader->Use();
    shader->SetModelMatrix(model_matrix);
    shader->SetViewProjectionMatrix(_viewProjection);

    shader->SetVec3("u_light_pos", 7.5f, -3.2f, 9.0f);
    shader->SetVec3("u_light_color", 0.76f, 0.23f, 0.36f);
    shader->SetVec3("u_cam_pos", _cameraPosition.x, _cameraPosition.y, _cameraPosition.z);
    shader->SetVec3("u_color", color.r, color.g, color.b);
    shader->SetFloat("u_alpha", alpha);

    //draw vertices according to their indices
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
