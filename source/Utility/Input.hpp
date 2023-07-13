#include "GLFW/glfw3.h"

struct Input {
    inline static double cursor_x = 0.0, cursor_y = 0.0, cursor_delta_x = 0.0, cursor_delta_y = 0.0;

    static void InputPoll(GLFWwindow* _window) {
        double now_cursor_x, now_cursor_y;

        //get the current cursor position, regardless if it has moved or not
        glfwGetCursorPos(_window, &now_cursor_x, &now_cursor_y);

        cursor_delta_x = cursor_x - now_cursor_x;
        cursor_delta_y = cursor_y - now_cursor_y;

        cursor_x = now_cursor_x;
        cursor_y = now_cursor_y;
    }

    static bool IsKeyPressed(GLFWwindow* _window, const int _desiredKey) {
        return glfwGetKey(_window, _desiredKey) == GLFW_PRESS;
    }

    static bool IsMouseButtonPressed(GLFWwindow* _window, const int _desiredButton) {
        return glfwGetMouseButton(_window, _desiredButton) == GLFW_PRESS;
    }
};