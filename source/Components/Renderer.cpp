#include "Renderer.h"
#include "Utility/Input.hpp"

std::unordered_map<GLFWwindow*, std::shared_ptr<Renderer>> Renderer::instances;

std::shared_ptr<Renderer> Renderer::CreateRenderer(GLFWwindow* associatedWindow, uint16_t initialWidth, uint16_t initialHeight) {
    auto renderer = std::make_shared<Renderer>(associatedWindow, initialWidth, initialHeight);

    Renderer::instances[associatedWindow] = renderer;

    return renderer;
}

void Renderer::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (!Renderer::instances.contains(window)) return;

    //Renderer::instances[window]->InputCallbackLocal(window, key, scancode, action, mods);
}

Renderer::Renderer(GLFWwindow* associatedWindow, uint16_t initialWidth, uint16_t initialHeight) {
    associated_window = associatedWindow;

    main_camera = std::make_unique<Camera>(glm::vec3(3.0f), glm::vec3(1.0f), initialWidth, initialHeight);

    default_shader = Shader::Library::CreateShader("shaders/default.vert", "shaders/default.frag");

    main_grid = std::make_unique<VisualGrid>(100, 100, 1.0f, glm::vec3(0.0f, -1.0f, 0.0f));
}

Renderer::~Renderer() {
    Renderer::instances.erase(associated_window);
}

void Renderer::Render(GLFWwindow* window, const double deltaTime) {
    //processes keyboard input
    InputCallbackLocal(window, deltaTime);

    //activates the default shader
    default_shader->Use();

    //draws the main grid
    main_grid->Draw(main_camera->GetViewProjection());
}

void Renderer::ResizeCallback(GLFWwindow* window, int displayWidth, int displayHeight) {
    main_camera->SetViewportSize((float)displayWidth, (float)displayHeight);
}

void Renderer::InputCallbackLocal(GLFWwindow *window, const double deltaTime) {
    //moves camera (side to side and zoom)
    if (Input::IsKeyPressed(window, GLFW_KEY_Q))
        main_camera->OneAxisMove(Camera::Movement::UP, (float)deltaTime);
    if (Input::IsKeyPressed(window, GLFW_KEY_E))
        main_camera->OneAxisMove(Camera::Movement::DOWN, (float)deltaTime);
    if (Input::IsKeyPressed(window, GLFW_KEY_A))
        main_camera->OneAxisMove(Camera::Movement::LEFT, (float)deltaTime);
    if (Input::IsKeyPressed(window, GLFW_KEY_D))
        main_camera->OneAxisMove(Camera::Movement::RIGHT, (float)deltaTime);
    if (Input::IsKeyPressed(window, GLFW_KEY_S))
        main_camera->OneAxisMove(Camera::Movement::BACKWARD, (float)deltaTime);
    if (Input::IsKeyPressed(window, GLFW_KEY_W))
        main_camera->OneAxisMove(Camera::Movement::FORWARD, (float)deltaTime);
}
