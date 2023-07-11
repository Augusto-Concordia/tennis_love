#pragma once

#include <map>
#include "Camera.h"
#include "Shader.h"
#include "Visual/VisualGrid.h"
#include "GLFW/glfw3.h"
#include "Components/Visual/VisualLine.h"

class Renderer {
private:
    static std::unordered_map<GLFWwindow*, std::shared_ptr<Renderer>> instances;

    GLFWwindow* associated_window;

    std::shared_ptr<Camera> main_camera;
    std::shared_ptr<Shader> default_shader;

    std::unique_ptr<VisualGrid> main_grid;

    std::unique_ptr<VisualLine> main_x_line;
    std::unique_ptr<VisualLine> main_y_line;
    std::unique_ptr<VisualLine> main_z_line;

public:
    Renderer(GLFWwindow* associatedWindow, uint16_t initialWidth, uint16_t initialHeight);
    ~Renderer();

    static std::shared_ptr<Renderer> CreateRenderer(GLFWwindow* associatedWindow, uint16_t initialWidth, uint16_t initialHeight);
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    void Render(GLFWwindow* window, double deltaTime);
    void ResizeCallback(GLFWwindow* window, int displayWidth, int displayHeight);

private:
    void InputCallbackLocal(GLFWwindow* window, double deltaTime);
};

