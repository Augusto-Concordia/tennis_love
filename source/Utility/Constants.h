#pragma once

#include "glm/glm.hpp"

struct Constants {
    constexpr static glm::vec3 UP = glm::vec3 (0.0f, 1.0f, 0.0f);
    constexpr static glm::vec3 RIGHT = glm::vec3 (1.0f, 0.0f, 0.0f);
    constexpr static glm::vec3 FORWARD = glm::vec3 (0.0f, 0.0f, 1.0f);

    constexpr static float PI = 3.1415f;
};
