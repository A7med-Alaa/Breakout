#include <iostream>

#include "Game.h"

//CONSTANTS
constexpr unsigned int WIDTH = 1280;
constexpr unsigned int HEIGHT = 720;

//CALLBACKS
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

//GAME
Game Breakout(WIDTH, HEIGHT);

int main(int argc, char* argv[])
{
    //WINDOW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Breakout", nullptr, nullptr);
    if(!window)
    {
        std::cout << "Couldn't Create a Window.";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    if(glewInit() != GLEW_OK)
    {
        std::cout << "Couldn't Initialize Glew.";
        glfwTerminate();
        return -1;
    }
    
    glViewport(0, 0, WIDTH, HEIGHT);

    Breakout.Init();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //DELTA TIME
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        Breakout.Update(deltaTime);

        Breakout.processInput();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Breakout.Render();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if(key > 0 && key < 1024 && action == GLFW_PRESS)
    {
        Breakout.Keys[key] = true;
    }
}
