#include "VisualLine.h"
#include "Utility/Transform.hpp"
#include "Utility/Math.hpp"

VisualLine::VisualLine(glm::vec3 start, glm::vec3 end, float thickness, glm::vec3 color, float alpha) {
    this->start = start;
    this->end = end;

    this->thickness = thickness;
    this->color = color;
    this->alpha = alpha;

    shader = Shader::Library::CreateShader("shaders/grid/grid.vert", "shaders/grid/grid.frag");

    vertices = {
            this->start.x,
            this->start.y,
            this->start.z,
            this->end.x,
            this->end.y,
            this->end.z
    };

    indices = {
            0, 1
    };

    //generate and bind the circles' vertex array (VAO)
    glGenVertexArrays(1, &vertex_array_o);
    glBindVertexArray(vertex_array_o);

    //generate and bind the grid's VBO
    glGenBuffers(1, &vertex_buffer_o);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_o);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 &vertices.front(), GL_STATIC_DRAW);

    //generate and bind the circles' EBO
    glGenBuffers(1, &element_buffer_o);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_o);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int),
                 &indices.front(), GL_STATIC_DRAW);

    //set vertex attributes pointers (position)
    //strides are 3 * float-size long, because we are including position coord data in the VAO (Vertex Attribute Object)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid *) nullptr);
    glEnableVertexAttribArray(0);

    //the following is in this specific order to avoid a dangling EBO
    //more info: https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/2.2.hello_triangle_indexed/hello_triangle_indexed.cpp

    //cleanup buffers
    glBindVertexArray(0);
    glDeleteBuffers(1, &vertex_buffer_o);
    glDeleteBuffers(1, &element_buffer_o);
}

void VisualLine::Draw(const glm::mat4& viewProjection) {
    //bind the vertex array to draw
    glBindVertexArray(vertex_array_o);

    glm::mat4 model_matrix = glm::mat4(1.0f);

    shader->Use();
    shader->SetModelMatrix(model_matrix);
    shader->SetViewProjectionMatrix(viewProjection);

    shader->SetVec3("u_color", color.r, color.g, color.b);
    shader->SetFloat("u_alpha", alpha);

    //sets line thickness
    glLineWidth(thickness);

    //draw vertices according to their indices
    glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, nullptr);
}
