#pragma once

#include <memory>
#include <vector>
#include "glm/vec3.hpp"
#include "Components/Shader.h"
#include "VisualObject.h"

class VisualLine : public VisualObject {
public:
    glm::vec3 end;

public:
    explicit VisualLine(glm::vec3 _start = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _end = glm::vec3(1.0f, 1.0f, 1.0f), float _lineThickness = 1.0f, glm::vec3 _color = glm::vec3(1.0f), float _alpha = 1.0f);

    void Draw(const glm::mat4& _viewProjection) override;
};
