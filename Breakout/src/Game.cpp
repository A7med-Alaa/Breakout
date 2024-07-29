#include "Game.h"

#include "ResourceManager.h"
#include "GLFW/glfw3.h"

SpriteRenderer* renderer;

Game::Game(float width, float height)
    : WIDTH(width), HEIGHT(height), state(GAME_ACTIVE), Keys()
{
}

Game::~Game()
{
    delete renderer;
}


void Game::Init()
{
    state = GAME_ACTIVE;
    glm::mat4 ortho = glm::ortho(0.0f, WIDTH, HEIGHT, 0.0f, -1.0f, 1.0f);
    
    ResourceManager::LoadShader("src/vertex.vert", "src/fragment.frag", nullptr, "sprite");
    Shader shader = ResourceManager::GetShader("sprite");
    shader.Use();
    
    shader.setMat4("proj", ortho);
    shader.setInt("image", 0);
    
    renderer = new SpriteRenderer(shader);

    ResourceManager::LoadTexture("src/assets/textures/background.jpg", false, "background");
    ResourceManager::LoadTexture("src/assets/textures/block_solid.png", false, "solid_block");
    ResourceManager::LoadTexture("src/assets/textures/block.png", false, "block");
    ResourceManager::LoadTexture("src/assets/textures/player.png", true, "player");
    
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

    currentLevel = 0;
}

void Game::processInput(float dt)
{
    const float speed = PLAYER_VELOCITY * dt;
    if (Keys[GLFW_KEY_A] && player->m_Position.x >= 0.0f) {
        player->m_Position.x -= speed;
    }
    
    if (Keys[GLFW_KEY_D] && player->m_Position.x <= WIDTH - PLAYER_SIZE.x) {
        player->m_Position.x += speed;
    }
}

void Game::Update(float dt)
{
}

void Game::Render()
{
    if (state == GAME_ACTIVE) {
        renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f), 0,
            glm::vec2(WIDTH, HEIGHT), glm::vec3(1.0f));

        Levels[currentLevel].DrawLevel(*renderer);

        player->Draw(*renderer);

    }
}
