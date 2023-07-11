#include "VisualGrid.h"
#include "Utility/Math.hpp"
#include "Utility/Transform.hpp"

VisualGrid::VisualGrid(int width, int height, float cellSize, float thickness, glm::vec3 position, glm::vec3 rotation) {
    cell_size = cellSize;
    this->thickness = thickness;

    this->width = width;
    this->height = height;

    this->position = position;
    this->rotation = rotation;

    shader = Shader::Library::CreateShader("shaders/grid/grid.vert", "shaders/grid/grid.frag");
    shader->SetVec3("u_color", 1.0f, 1.0f, 1.0f);
    shader->SetFloat("u_alpha", 0.4f);

    vertices = std::vector<float>();
    indices = std::vector<int>();

    //generates vertices for the far side of the grid
    for (int i = 0; i <= this->width; ++i) {
        vertices.push_back(Math::Map((float)i, 0, (float)this->width, -1.0f, 1.0f));
        vertices.push_back(-1.0f);
        vertices.push_back(0.0f);
    }

    //generates vertices for the right side of the grid
    for (int i = 1; i <= this->height; ++i) {
        vertices.push_back(1.0f);
        vertices.push_back(Math::Map((float)i, 0, (float)this->height, -1.0f, 1.0f));
        vertices.push_back(0.0f);
    }

    //generates vertices for the near side of the grid
    for (int i = this->width - 1; i >= 0; --i) {
        vertices.push_back(Math::Map((float)i, 0, (float)this->width, -1.0f, 1.0f));
        vertices.push_back(1.0f);
        vertices.push_back(0.0f);
    }

    //generates vertices for the left side of the grid
    for (int i = this->height - 1; i > 0; --i) {
        vertices.push_back(-1.0f);
        vertices.push_back(Math::Map((float)i, 0, (float)this->height, -1.0f, 1.0f));
        vertices.push_back(0.0f);
    }

    const int total_vertices = 2 * this->width + 2 * this->height; //number of vertices on the perimeter of the grid
    const int three_quarter_loop = total_vertices - this->height; //number of vertices to do a quarter turn of the perimeter

    //generates indices for the vertical lines of the grid
    for (int i = 0; i <= this->width; ++i) {
        const int top_side_index = i;
        const int bottom_side_index = three_quarter_loop - i;

        indices.push_back(top_side_index);
        indices.push_back(bottom_side_index);
    }

    //generates indices for the horizontal lines of the grid
    for (int i = this->height; i >= 0; --i) {
        const int left_side_index = (total_vertices - i) % (total_vertices);
        const int right_side_index = this->width + i;

        indices.push_back(left_side_index);
        indices.push_back(right_side_index);
    }

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

void VisualGrid::Draw(const glm::mat4& viewProjection) {
    //bind the vertex array to draw
    glBindVertexArray(vertex_array_o);

    glm::mat4 model_matrix = glm::mat4(1.0f);

    //since we want to respect the traditional order (scale, rotate, translate), the scaling is done on the z-axis instead of the y
    model_matrix = glm::scale(model_matrix, glm::vec3(cell_size / 2, cell_size / 2, 0.0f));

    //rotated -90deg, because the grid should facing up
    model_matrix = glm::translate(model_matrix, position);

    shader->Use();
    shader->SetModelMatrix(model_matrix);
    shader->SetViewProjectionMatrix(viewProjection);

    //sets grid's lines thickness
    glLineWidth(thickness);

    //draw vertices according to their indices
    glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, nullptr);
}
