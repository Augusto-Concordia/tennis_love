#pragma once

#include "glm/vec3.hpp"

struct Transforms {
    constexpr static glm::vec3 FORWARD = glm::vec3 (1.0f, 0.0f, 0.0f);
    constexpr static glm::vec3 RIGHT = glm::vec3 (0.0f, 1.0f, 0.0f);
    constexpr static glm::vec3 UP = glm::vec3 (0.0f, 0.0f, 1.0f);
};