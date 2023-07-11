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
    Renderer(GLFWwindow* _associatedWindow, int _initialWidth, int _initialHeight);
    ~Renderer();

    void Render(GLFWwindow* _window, double _deltaTime);
    void ResizeCallback(GLFWwindow* _window, int _displayWidth, int _displayHeight);

private:
    void InputCallbackLocal(GLFWwindow* _window, double _deltaTime);
};

