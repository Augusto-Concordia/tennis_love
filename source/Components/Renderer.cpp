#include "Renderer.h"
#include "Utility/Input.hpp"

std::unordered_map<GLFWwindow*, std::shared_ptr<Renderer>> Renderer::instances;

std::shared_ptr<Renderer> Renderer::CreateRenderer(uint16_t initialWidth, uint16_t initialHeight, GLFWwindow* associatedWindow) {
    auto renderer = std::make_shared<Renderer>(initialWidth, initialHeight);

    Renderer::instances[associatedWindow] = renderer;

    return renderer;
}

void Renderer::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (!Renderer::instances.contains(window)) return;

    Renderer::instances[window]->KeyCallbackLocal(window, key, scancode, action, mods);
}

Renderer::Renderer(uint16_t initialWidth, uint16_t initialHeight, GLFWwindow* associatedWindow) {
    associated_window = associatedWindow;

    main_camera = std::make_unique<Camera>();
    main_camera->SetViewportSize(initialWidth, initialHeight);

    default_shader = Shader::Library::CreateShader("shaders/default.vert", "shaders/default.frag");

    main_grid = std::make_unique<VisualGrid>(100, 100, 1.0f, glm::vec3(0.0f, -1.0f, 0.0f));
}

Renderer::~Renderer() {
    Renderer::instances.erase(associated_window);
}

void Renderer::Render() {
    //activates the default shader
    default_shader->Use();

    //draws the main grid
    main_grid->Draw(main_camera->GetViewProjection());
}

void Renderer::KeyCallbackLocal(GLFWwindow *window, int key, int scancode, int action, int mods) {

    //moves camera (side to side and zoom)
    if (Input::IsKeyPressed(window, GLFW_KEY_Q))
        main_camera->OneAxisMove(Camera::Movement::UP, 0.1f);
    if (Input::IsKeyPressed(window, GLFW_KEY_E))
        main_camera->OneAxisMove(Camera::Movement::DOWN, 0.1f);
    if (Input::IsKeyPressed(GLFW_KEY_A, key, action))
        main_camera->OneAxisMove(Camera::Movement::LEFT, 0.1f);
    if (Input::IsKeyPressed(GLFW_KEY_D, key, action))
        main_camera->OneAxisMove(Camera::Movement::RIGHT, 0.1f);
    if (Input::IsKeyPressed(GLFW_KEY_S, key, action))
        main_camera->OneAxisMove(Camera::Movement::BACKWARD, 0.1f);
    if (Input::IsKeyPressed(GLFW_KEY_W, key, action))
        main_camera->OneAxisMove(Camera::Movement::FORWARD, 0.1f);
}
