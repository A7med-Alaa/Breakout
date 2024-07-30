#pragma once
#include "SpriteRenderer.h"
#include "GameLevel.h"
#include "BallObject.h"
#include "GLFW/glfw3.h"

enum GameState
{
    GAME_ACTIVE,
    GAME_PAUSED,
    GAME_WIN
};

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

class Game
{
private:
    const float WIDTH;
    const float HEIGHT;

    const glm::vec2 PLAYER_SIZE = {100.0f, 20.0f};
    const float PLAYER_VELOCITY = 500.0f;

    const float BALL_RADIUS = 12.5f;
    const glm::vec2 BALL_VELOCITY = glm::vec2(150.0f, -550.0f);

    unsigned int currentDestroyedBricks = 0;


	std::vector<GameLevel> Levels;
	unsigned int currentLevel;

    std::tuple<bool, Direction, glm::vec2> CheckCollision(BallObject& one, GameObject& two);
    Direction VectorDirection(glm::vec2 target);
    void LevelCollisions();

    void ResetGame();
    void checkForWin();

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
