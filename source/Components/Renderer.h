#pragma once

#include <map>
#include "Camera.h"
#include "Shader.h"
#include "Visual/VisualGrid.h"
#include "GLFW/glfw3.h"

class Renderer {
private:
    static std::unordered_map<GLFWwindow*, std::shared_ptr<Renderer>> instances;

    GLFWwindow* associated_window;

    std::shared_ptr<Camera> main_camera;
    std::shared_ptr<Shader> default_shader;

    std::unique_ptr<VisualGrid> main_grid;

public:
    Renderer(uint16_t initialWidth, uint16_t initialHeight, GLFWwindow* associatedWindow = nullptr);
    ~Renderer();

    static std::shared_ptr<Renderer> CreateRenderer(uint16_t initialWidth, uint16_t initialHeight, GLFWwindow* associatedWindow);
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    void Render();
    void KeyCallbackLocal(GLFWwindow* window, int key, int scancode, int action, int mods);
};

