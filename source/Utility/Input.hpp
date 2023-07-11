#include "GLFW/glfw3.h"

struct Input {
    static bool IsKeyPressed(GLFWwindow* _window, int _desiredKey) {
        return glfwGetKey(_window, _desiredKey) == GLFW_PRESS;
    }
};