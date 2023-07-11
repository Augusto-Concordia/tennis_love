#include "Renderer.h"
#include "Utility/Input.hpp"

std::unordered_map<GLFWwindow*, std::shared_ptr<Renderer>> Renderer::instances;

Renderer::Renderer(GLFWwindow* _associatedWindow, int _initialWidth, int _initialHeight) {
    associated_window = _associatedWindow;

    main_camera = std::make_unique<Camera>(glm::vec3(10.0f, 10.0f, 13.0f), glm::vec3(1.0f), _initialWidth, _initialHeight);

    default_shader = Shader::Library::CreateShader("shaders/default.vert", "shaders/default.frag");

    //grid
    main_grid = std::make_unique<VisualGrid>(100, 100, 100.0f);

    //axis
    main_x_line = std::make_unique<VisualLine>(glm::vec3(0.0f), glm::vec3(5.0f, 0.0f, 0.0f), 3.0f, glm::vec3(1.0f, 0.0f, 0.0f), 1.0f);
    main_y_line = std::make_unique<VisualLine>(glm::vec3(0.0f), glm::vec3(0.0f, 5.0f, 0.0f), 3.0f, glm::vec3(0.0f, 1.0f, 0.0f), 1.0f);
    main_z_line = std::make_unique<VisualLine>(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 5.0f), 3.0f, glm::vec3(0.0f, 0.0f, 1.0f), 1.0f);

    //objects
    test_cube = std::make_unique<VisualCube>(glm::vec3(0.0f, 0.0f, 1.0f));
}

Renderer::~Renderer() {
    Renderer::instances.erase(associated_window);
}

void Renderer::Render(GLFWwindow* _window, const double _deltaTime) {
    //clears the canvas to black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //processes keyboard input
    InputCallbackLocal(_window, _deltaTime);

    //activates the default shader
    default_shader->Use();

    //draws the main grid
    main_grid->Draw(main_camera->GetViewProjection());

    //clears the depth buffer to allow the axis to always be drawn on top of the grid
    glClear(GL_DEPTH_BUFFER_BIT);

    //draws the coordinate axis
    main_x_line->Draw(main_camera->GetViewProjection());
    main_y_line->Draw(main_camera->GetViewProjection());
    main_z_line->Draw(main_camera->GetViewProjection());

    //clears the depth buffer to allow the objects to be drawn on top of everything before
    glClear(GL_DEPTH_BUFFER_BIT);

    //draws the objects
    test_cube->Draw(main_camera->GetViewProjection());
}

void Renderer::ResizeCallback(GLFWwindow* _window, int _displayWidth, int _displayHeight) {
    main_camera->SetViewportSize((float)_displayWidth, (float)_displayHeight);
}

void Renderer::InputCallbackLocal(GLFWwindow* _window, const double _deltaTime) {
    //moves camera (side to side and zoom)
    if (Input::IsKeyPressed(_window, GLFW_KEY_Q))
        main_camera->OneAxisMove(Camera::Movement::UP, (float)_deltaTime);
    if (Input::IsKeyPressed(_window, GLFW_KEY_E))
        main_camera->OneAxisMove(Camera::Movement::DOWN, (float)_deltaTime);
    if (Input::IsKeyPressed(_window, GLFW_KEY_A))
        main_camera->OneAxisMove(Camera::Movement::LEFT, (float)_deltaTime);
    if (Input::IsKeyPressed(_window, GLFW_KEY_D))
        main_camera->OneAxisMove(Camera::Movement::RIGHT, (float)_deltaTime);
    if (Input::IsKeyPressed(_window, GLFW_KEY_S))
        main_camera->OneAxisMove(Camera::Movement::BACKWARD, (float)_deltaTime);
    if (Input::IsKeyPressed(_window, GLFW_KEY_W))
        main_camera->OneAxisMove(Camera::Movement::FORWARD, (float)_deltaTime);
}
