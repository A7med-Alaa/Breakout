#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum GameState
{
    GAME_ACTIVE,
    GAME_PAUSED,
    GAME_WIN
};

class Game
{
private:
    unsigned int WIDTH;
    unsigned int HEIGHT;

public:
    GameState state;
    bool Keys[1024];
    
    Game(unsigned int width, unsigned int height);
    ~Game();

    void Init();
    
    void processInput();
    void Update(float dt);
    void Render();
};
