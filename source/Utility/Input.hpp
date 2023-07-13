#include "GLFW/glfw3.h"

struct Input {
    inline static double cursor_x = 0.0, cursor_y = 0.0, cursor_delta_x = 0.0, cursor_delta_y = 0.0;
    inline static std::unordered_map<int, int> key_state;

    static void KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods) {
        key_state[_key] = _action;
    }

    static void PreEventsPoll(GLFWwindow* _window) {
        for (auto key : key_state) {
            if (key.second == GLFW_RELEASE) key_state.erase(key.first);
        }
    }

    static void PostEventsPoll(GLFWwindow* _window) {
        double now_cursor_x, now_cursor_y;

        //get the current cursor position, regardless if it has moved or not
        glfwGetCursorPos(_window, &now_cursor_x, &now_cursor_y);

        cursor_delta_x = cursor_x - now_cursor_x;
        cursor_delta_y = cursor_y - now_cursor_y;

        cursor_x = now_cursor_x;
        cursor_y = now_cursor_y;
    }

    static bool IsKeyPressed(GLFWwindow* _window, const int _desiredKey) {
        return key_state.contains(_desiredKey) && key_state[_desiredKey] == GLFW_PRESS || key_state[_desiredKey] == GLFW_REPEAT;
    }

    static bool IsKeyReleased(GLFWwindow* _window, const int _desiredKey) {
        return key_state.contains(_desiredKey) && key_state[_desiredKey] == GLFW_RELEASE;
    }

    static bool IsMouseButtonPressed(GLFWwindow* _window, const int _desiredButton) {
        return glfwGetMouseButton(_window, _desiredButton) == GLFW_PRESS;
    }
};