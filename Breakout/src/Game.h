#pragma once
#include "SpriteRenderer.h"
#include "GameLevel.h"

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

    const glm::vec2 PLAYER_SIZE = {100.0f, 20.0f};
    const float PLAYER_VELOCITY = 500.0f;

    GameObject* player;

	std::vector<GameLevel> Levels;
	unsigned int currentLevel;

public:
    GameState state;
    bool Keys[1024];
    
    Game(float width, float height);
    ~Game();

    void Init();
    
    void processInput(float dt);
    void Update(float dt);
    void Render();
};
