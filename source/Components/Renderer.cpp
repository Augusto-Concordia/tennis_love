#include "Renderer.h"
#include "Utility/Input.hpp"
#include "Utility/Transform.hpp"

Renderer::Renderer(int _initialWidth, int _initialHeight) {
    main_camera = std::make_unique<Camera>(glm::vec3(10.0f, 10.0f, 13.0f), glm::vec3(0.0f), _initialWidth, _initialHeight);

    default_shader = Shader::Library::CreateShader("shaders/default.vert", "shaders/default.frag");

    //grid
    main_grid = std::make_unique<VisualGrid>(100, 100, 100.0f);

    //axis
    main_x_line = std::make_unique<VisualLine>(glm::vec3(0.0f), glm::vec3(5.0f, 0.0f, 0.0f), 3.0f, glm::vec3(1.0f, 0.0f, 0.0f), 1.0f);
    main_y_line = std::make_unique<VisualLine>(glm::vec3(0.0f), glm::vec3(0.0f, 5.0f, 0.0f), 3.0f, glm::vec3(0.0f, 1.0f, 0.0f), 1.0f);
    main_z_line = std::make_unique<VisualLine>(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 5.0f), 3.0f, glm::vec3(0.0f, 0.0f, 1.0f), 1.0f);

    //racket and its components
    auto current_position = glm::vec3(0.0f), current_rotation = glm::vec3(0.0f), current_scale = glm::vec3(1.0f), transform_offset = glm::vec3(0.0f, 0.0f, 0.5f);

    racket_cubes = std::vector<VisualCube>(10);
    racket_cubes[0] = VisualCube(current_position, current_rotation, current_scale, transform_offset); //forearm
    racket_cubes[1] = VisualCube(current_position, current_rotation, current_scale, transform_offset); //arm
    racket_cubes[2] = VisualCube(current_position, current_rotation, current_scale, transform_offset); //racket handle
    racket_cubes[3] = VisualCube(current_position, current_rotation, current_scale, transform_offset); //racket angled bottom left
    racket_cubes[4] = VisualCube(current_position, current_rotation, current_scale, transform_offset); //racket vertical left
    racket_cubes[5] = VisualCube(current_position, current_rotation, current_scale, transform_offset); //racket angled top left
    racket_cubes[6] = VisualCube(current_position, current_rotation, current_scale, transform_offset); //racket horizontal top
    racket_cubes[7] = VisualCube(current_position, current_rotation, current_scale, transform_offset); //racket angled top right
    racket_cubes[8] = VisualCube(current_position, current_rotation, current_scale, transform_offset); //racket vertical right
    racket_cubes[9] = VisualCube(current_position, current_rotation, current_scale, transform_offset); //racket angled bottom right
}

void Renderer::Render(GLFWwindow* _window, const double _deltaTime) {
    //clears the canvas to black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //processes keyboard input
    InputCallback(_window, _deltaTime);

    //activates the default shader
    default_shader->Use();

    //draws the main grid
    main_grid->Draw(main_camera->GetViewProjection(), main_camera->GetPosition());

    //clears the depth buffer to allow the axis to always be drawn on top of the grid
    glClear(GL_DEPTH_BUFFER_BIT);

    //draws the coordinate axis
    main_x_line->Draw(main_camera->GetViewProjection(), main_camera->GetPosition());
    main_y_line->Draw(main_camera->GetViewProjection(), main_camera->GetPosition());
    main_z_line->Draw(main_camera->GetViewProjection(), main_camera->GetPosition());

    //draws the objects
    /*for (auto& cube : racket_cubes) {
        cube.Draw(main_camera->GetViewProjection(), main_camera->GetPosition());
    }*/

    glm::mat4 world_transform_matrix = glm::mat4(1.0f);

    //todo: figure out how on God's green earth will this work
    //forearm
    world_transform_matrix = glm::translate(world_transform_matrix, glm::vec3(0.0f));
    world_transform_matrix = Transforms::RotateDegrees(world_transform_matrix, glm::vec3(45.0f, 0.0f, 0.0f));
    world_transform_matrix = glm::scale(world_transform_matrix, glm::vec3(1.0f, 1.0f, 5.0f));
    racket_cubes[0].DrawFromMatrix(main_camera->GetViewProjection(), main_camera->GetPosition(), world_transform_matrix);
    world_transform_matrix = glm::scale(world_transform_matrix, glm::vec3(1.0f, 1.0f, 0.2f));

    //arm
    world_transform_matrix = glm::translate(world_transform_matrix, glm::vec3(0.0f, 0.0f, 0.0f));
    world_transform_matrix = Transforms::RotateDegrees(world_transform_matrix, glm::vec3(-45.0f, 0.0f, 0.0f));
    world_transform_matrix = glm::scale(world_transform_matrix, glm::vec3(1.0f, 1.0f, 1.0f));
    racket_cubes[1].DrawFromMatrix(main_camera->GetViewProjection(), main_camera->GetPosition(), world_transform_matrix);
}

void Renderer::ResizeCallback(GLFWwindow* _window, int _displayWidth, int _displayHeight) {
    main_camera->SetViewportSize((float)_displayWidth, (float)_displayHeight);
}

void Renderer::InputCallback(GLFWwindow* _window, const double _deltaTime) {
    //keyboard triggers
    //camera translates (side to side and zoom forwards & back)
    if (Input::IsKeyPressed(_window, GLFW_KEY_KP_7) || Input::IsKeyPressed(_window, GLFW_KEY_Y))
        main_camera->OneAxisMove(Camera::Translation::UP, (float)_deltaTime);
    if (Input::IsKeyPressed(_window, GLFW_KEY_KP_9) || Input::IsKeyPressed(_window, GLFW_KEY_I))
        main_camera->OneAxisMove(Camera::Translation::DOWN, (float)_deltaTime);
    if (Input::IsKeyPressed(_window, GLFW_KEY_KP_4) || Input::IsKeyPressed(_window, GLFW_KEY_H))
        main_camera->OneAxisMove(Camera::Translation::LEFT, (float)_deltaTime);
    if (Input::IsKeyPressed(_window, GLFW_KEY_KP_6) || Input::IsKeyPressed(_window, GLFW_KEY_K))
        main_camera->OneAxisMove(Camera::Translation::RIGHT, (float)_deltaTime);
    if (Input::IsKeyPressed(_window, GLFW_KEY_KP_8) || Input::IsKeyPressed(_window, GLFW_KEY_U))
        main_camera->OneAxisMove(Camera::Translation::FORWARD, (float)_deltaTime);
    if (Input::IsKeyPressed(_window, GLFW_KEY_KP_2) || Input::IsKeyPressed(_window, GLFW_KEY_J))
        main_camera->OneAxisMove(Camera::Translation::BACKWARD, (float)_deltaTime);

    //mouse triggers
    //forwards & back in camera local coordinates
    if (Input::IsMouseButtonPressed(_window, GLFW_MOUSE_BUTTON_LEFT))
        main_camera->OneAxisMove(Camera::Translation::CAMERA_FORWARD, (float)(_deltaTime * Input::cursor_delta_y));

    //tilt control
    if (Input::IsMouseButtonPressed(_window, GLFW_MOUSE_BUTTON_MIDDLE))
        main_camera->OneAxisRotate(Camera::Rotation::POSITIVE_PITCH, (float)(_deltaTime * Input::cursor_delta_y));

    //pan control
    if (Input::IsMouseButtonPressed(_window, GLFW_MOUSE_BUTTON_RIGHT))
        main_camera->OneAxisRotate(Camera::Rotation::POSITIVE_YAW, (float) (_deltaTime * Input::cursor_delta_x));

    //camera rotation reset
    if (Input::IsKeyPressed(_window, GLFW_KEY_HOME) || Input::IsKeyPressed(_window, GLFW_KEY_KP_5))
        main_camera->SetDefaultPositionAndTarget();

    //keyboard triggers
    //camera orbit
    if (Input::IsKeyPressed(_window, GLFW_KEY_UP))
        main_camera->OneAxisOrbit(Camera::Orbitation::ORBIT_UP, (float)_deltaTime);
    if (Input::IsKeyPressed(_window, GLFW_KEY_DOWN))
        main_camera->OneAxisOrbit(Camera::Orbitation::ORBIT_DOWN, (float)_deltaTime);
    if (Input::IsKeyPressed(_window, GLFW_KEY_RIGHT))
        main_camera->OneAxisOrbit(Camera::Orbitation::ORBIT_RIGHT, (float)_deltaTime);
    if (Input::IsKeyPressed(_window, GLFW_KEY_LEFT))
        main_camera->OneAxisOrbit(Camera::Orbitation::ORBIT_LEFT, (float)_deltaTime);
}
