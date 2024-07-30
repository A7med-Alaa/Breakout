#include <GL/glew.h>
#include "Game.h"
#include "ResourceManager.h"
#include <iostream>

//CONSTANTS
const int WIDTH = 1280;
const int HEIGHT = 720;

//CALLBACKS
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

//GAME
Game Breakout((float)WIDTH, (float)HEIGHT);

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
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    if(glewInit() != GLEW_OK)
    {
        std::cout << "glew Couldnt load.";
        glfwTerminate();
        return -1;
    }
    
    glViewport(0, 0, WIDTH, HEIGHT);

    Breakout.Init();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //DELTA TIME
    float lastFrame = 0.0f;
    
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = (float)glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        Breakout.Update(deltaTime);

        Breakout.processInput(deltaTime);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Breakout.Render();

        glfwSwapBuffers(window);
    }

    ResourceManager::Clean();
    glfwTerminate();
    return 0;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if(key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS) 
        {
            Breakout.Keys[key] = true;
        }
        else if(action == GLFW_RELEASE)
        {
            Breakout.Keys[key] = false;
        }
    }
}
