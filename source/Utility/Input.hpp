#include "GLFW/glfw3.h"

struct Input {
    static bool IsKeyDown(int desiredKey, int key, int action) {
        return key == desiredKey && action == GLFW_PRESS;
    }

    static bool IsKeyPressed(GLFWwindow* window, int desiredKey) {
        return glfwGetKey(window, desiredKey) == GLFW_PRESS;
    }

    static bool IsKeyPressed(int desiredKey, int key, int action) {
        return key == desiredKey && action == GLFW_REPEAT;
    }

    static bool IsKeyUp(int desiredKey, int key, int action) {
        return key == desiredKey && action == GLFW_RELEASE;
    }
};