#pragma once

#include <vector>
#include "glm/vec3.hpp"
#include "glad/glad.h"
#include "Components/Shader.h"
#include "Components/Camera.h"
#include "VisualObject.h"

class VisualGrid : public VisualObject{
public:
    float cell_size;
    int width, height;

public:
    VisualGrid(int _width, int _height, float _cellSize = 1.0f, float _lineThickness = 1.0f, glm::vec3 _position = glm::vec3 (0.0f), glm::vec3 _rotation = glm::vec3(0.0f), glm::vec3 _color = glm::vec3(1.0f), float _alpha = 1.0f);

    void Draw(const glm::mat4& viewProjection) override;
};