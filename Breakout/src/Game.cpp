#include "Game.h"

#include "ResourceManager.h"
#include <iostream>


SpriteRenderer* renderer;

GameObject* player;
BallObject* ball;

Game::Game(float width, float height)
    : WIDTH(width), HEIGHT(height), state(GAME_ACTIVE), Keys()
{
}

Game::~Game()
{
    delete renderer;
    delete player;
    delete ball;
}

void Game::Init()
{
    glm::mat4 ortho = glm::ortho(0.0f, WIDTH, HEIGHT, 0.0f, -1.0f, 1.0f);
    
    ResourceManager::LoadShader("src/assets/shaders/breakout.vert", "src/assets/shaders/breakout.frag", nullptr, "sprite");
    Shader shader = ResourceManager::GetShader("sprite");
    shader.Use();
    
    shader.setMat4("proj", ortho);
    shader.setInt("image", 0);
    
    renderer = new SpriteRenderer(shader);

    ResourceManager::LoadTexture("src/assets/textures/background.jpg", false, "background");
    ResourceManager::LoadTexture("src/assets/textures/block_solid.png", false, "solid_block");
    ResourceManager::LoadTexture("src/assets/textures/block.png", false, "block");
    ResourceManager::LoadTexture("src/assets/textures/player.png", true, "player");
    ResourceManager::LoadTexture("src/assets/textures/ball.png", true, "ball");
    
    GameLevel one; one.Load("src/assets/levels/1.lvl", WIDTH, HEIGHT / 2);
    GameLevel two; two.Load("src/assets/levels/2.lvl", WIDTH, HEIGHT / 2);
    GameLevel three; three.Load("src/assets/levels/3.lvl", WIDTH, HEIGHT / 2);
    GameLevel four; four.Load("src/assets/levels/4.lvl", WIDTH, HEIGHT / 2);
    
    Levels.push_back(one);
    Levels.push_back(two);
    Levels.push_back(three);
    Levels.push_back(four);

    player = new GameObject(ResourceManager::GetTexture("player"), glm::vec2((WIDTH - PLAYER_SIZE.x) / 2.0f, HEIGHT - PLAYER_SIZE.y),
        PLAYER_SIZE);

    ball = new BallObject(ResourceManager::GetTexture("ball"), 
        glm::vec2(player->m_Position.x + PLAYER_SIZE.x / 2 - BALL_RADIUS, player->m_Position.y - BALL_RADIUS * 2), BALL_RADIUS, BALL_VELOCITY);

    currentLevel = 0;
}

void Game::processInput(float dt)
{
    const float speed = PLAYER_VELOCITY * dt;
    if (Keys[GLFW_KEY_A] && player->m_Position.x >= 0.0f) {
        player->m_Position.x -= speed;
        if (ball->m_isStuck) {
            ball->m_Position.x -= speed;
        }
    }
    
    if (Keys[GLFW_KEY_D] && player->m_Position.x <= WIDTH - PLAYER_SIZE.x) {
        player->m_Position.x += speed;
        if (ball->m_isStuck) {
            ball->m_Position.x += speed;
        }
    }

    if (Keys[GLFW_KEY_SPACE]) {
        ball->m_isStuck = false;
    }
}

void Game::Update(float dt)
{
    LevelCollisions();
    ball->move(dt, WIDTH);

    checkForWin();

    if (ball->m_Position.y + BALL_RADIUS * 2 >= HEIGHT) {
        ResetGame();
        std::cout << "GameLose";
    }
}

void Game::Render()
{
    if (state == GAME_ACTIVE) {
        renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f), 0,
            glm::vec2(WIDTH, HEIGHT), glm::vec3(1.0f));

        Levels[currentLevel].DrawLevel(*renderer);

        player->Draw(*renderer);

        ball->Draw(*renderer);
    }
}

Direction Game::VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),	// up
		glm::vec2(1.0f, 0.0f),	// right
		glm::vec2(0.0f, -1.0f),	// down
		glm::vec2(-1.0f, 0.0f)	// left
	};
	float max = 0.0f;
	unsigned int best_match = -1;
	for (unsigned int i = 0; i < 4; i++)
	{
		float dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}

std::tuple<bool, Direction, glm::vec2> Game::CheckCollision(BallObject& one, GameObject& two) // AABB - Circle collision
{
	glm::vec2 center(one.m_Position + one.m_Radius);

    glm::vec2 aabb_half_extents(two.m_Size.x / 2.0f, two.m_Size.y / 2.0f);
	glm::vec2 aabb_center(
		two.m_Position.x + aabb_half_extents.x,
		two.m_Position.y + aabb_half_extents.y
	);

    glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    glm::vec2 closest = aabb_center + clamped;
	
	difference = closest - center;
    if (glm::length(difference) < one.m_Radius) {
        return std::make_tuple(true, VectorDirection(difference), difference);
    }
    else {
        return std::make_tuple(false, UP, glm::vec2(0.0f));
    }
}

void Game::LevelCollisions()
{
    for (GameObject& box : Levels[currentLevel].m_Bricks)
    {
        if (!box.m_isDestroyed)
        {
            std::tuple<bool, Direction, glm::vec2> collision = CheckCollision(*ball, box);
            if (std::get<0>(collision)) // if collision is true
            {
                if (!box.m_isSolid) {
                    box.m_isDestroyed = true;
                    currentDestroyedBricks++;
                }

                Direction dir = std::get<1>(collision);
                glm::vec2 diff_vector = std::get<2>(collision);
                if (dir == LEFT || dir == RIGHT)
                {
                    ball->m_Velocity.x = -ball->m_Velocity.x;

                    float penetration = ball->m_Radius - std::abs(diff_vector.x);
                    if (dir == LEFT)
                        ball->m_Position.x += penetration;
                    else
                        ball->m_Position.x -= penetration;
                }
                else
                {
                    ball->m_Velocity.y = -ball->m_Velocity.y;

                    float penetration = ball->m_Radius - std::abs(diff_vector.y);
                    if (dir == UP)
                        ball->m_Position.y -= penetration;
                    else
                        ball->m_Position.y += penetration;
                }
            }
        }
    }

    std::tuple<bool, Direction, glm::vec2> result = CheckCollision(*ball, *player);
    if (!ball->m_isStuck && std::get<0>(result))
    {

        float centerBoard = player->m_Position.x + player->m_Size.x / 2.0f;
        float distance = (ball->m_Position.x + ball->m_Radius) - centerBoard;
        float percentage = distance / (player->m_Size.x / 2.0f);

        float strength = 2.0f;
        glm::vec2 oldVelocity = ball->m_Velocity;
        ball->m_Velocity.x = BALL_VELOCITY.x * percentage * strength;

        ball->m_Velocity.y = -1.0f * abs(ball->m_Velocity.y);
        ball->m_Velocity = glm::normalize(ball->m_Velocity) * glm::length(oldVelocity);
    }
}

void Game::ResetGame()
{
    switch (currentLevel) 
    {
    case 0:
        Levels[currentLevel].Load("src/assets/levels/1.lvl", WIDTH, HEIGHT / 2);
        break;
    case 1:
        Levels[currentLevel].Load("src/assets/levels/2.lvl", WIDTH, HEIGHT / 2);
        break;
    case 2:
        Levels[currentLevel].Load("src/assets/levels/3.lvl", WIDTH, HEIGHT / 2);
        break;
    case 3:
        Levels[currentLevel].Load("src/assets/levels/4.lvl", WIDTH, HEIGHT / 2);
        break;
    default:
        Levels[currentLevel].Load("src/assets/levels/1.lvl", WIDTH, HEIGHT / 2);
        break;
    }

    player->m_Position = glm::vec2((WIDTH - PLAYER_SIZE.x) / 2.0f, HEIGHT - PLAYER_SIZE.y);
    ball->m_Position = glm::vec2(player->m_Position.x + PLAYER_SIZE.x / 2 - BALL_RADIUS, player->m_Position.y - BALL_RADIUS * 2);
    ball->m_isStuck = true;
    currentDestroyedBricks = 0;
}

void Game::checkForWin() 
{
    unsigned int breakableBricksSize = 1;
    for (auto& brick : Levels[currentLevel].m_Bricks) {
        if (!brick.m_isSolid) {
            breakableBricksSize++;
        }
    }

    if (currentDestroyedBricks >= breakableBricksSize - 1) {
        //Win
        if (currentLevel < Levels.size()) {
            currentLevel++;
        }
        else {
            currentLevel = 0;
        }

        ResetGame();
    }
}
