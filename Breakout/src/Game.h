#pragma once
#include "SpriteRenderer.h"

enum GameState
{
    GAME_ACTIVE,
    GAME_PAUSED,
    GAME_WIN
};

class Game
{
private:
    const float WIDTH;
    const float HEIGHT;

public:
    GameState state;
    bool Keys[1024];
    
    Game(float width, float height);
    ~Game();

    void Init();
    
    void processInput();
    void Update(float dt);
    void Render();
};
