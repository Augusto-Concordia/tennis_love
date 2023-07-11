#include <iostream>
#include <functional>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Components/Renderer.h"

int main() {
    std::cout << "Starting..." << std::endl;

    const uint16_t INITIAL_WIDTH = 1024;
    const uint16_t INITIAL_HEIGHT = 768;

    //initialize GL context
    if (!glfwInit()) {
        fprintf(stderr, "ERROR -> Could not start GLFW\n");
        return 1;
    }

    //initialize OS window with GLFW
    GLFWwindow* window = glfwCreateWindow(INITIAL_WIDTH, INITIAL_HEIGHT, "Tennis Love", nullptr, nullptr);
    if (window == nullptr) {
        fprintf(stderr, "ERROR -> Could not open widow through GLFW\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    //initialize GLAD
    gladLoadGL();

    //get current renderer and supported OpenGL version
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    printf("INFO -> Renderer: %s\n", renderer);
    printf("INFO -> Supported OpenGL version: %s\n", version);

    //enable depth testing and the desired testing function (the closest fragment is drawn)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //enable blending and the desired blending function
    //from: https://learnopengl.com/Advanced-OpenGL/Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::shared_ptr<Renderer> main_renderer = Renderer::CreateRenderer(INITIAL_WIDTH, INITIAL_HEIGHT, window);

    glfwSetKeyCallback(window, Renderer::KeyCallback);

    while (!glfwWindowShouldClose(window)) {
        //watch for input events
        glfwPollEvents();

        //get current display window size
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        main_renderer->Render();

        //swap buffers and prepare for next frame
        glfwSwapBuffers(window);

        //clears the canvas to black
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    std::cout << "Closing..." << std::endl;

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}