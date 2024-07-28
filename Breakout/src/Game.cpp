#include "Game.h"

#include <iostream>
#include <stb/stb_image.h>

#include "ResourceManager.h"

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
    ResourceManager::LoadShader("src/vertex.vert", "src/fragment.frag", nullptr, "sprite");
    Shader shader = ResourceManager::GetShader("sprite");
    glm::mat4 ortho = glm::ortho(0.0f, WIDTH, HEIGHT, 0.0f, -1.0f, 1.0f);
    shader.Use();
    shader.setMat4("proj", ortho);
    shader.setInt("image", 0);
    
    renderer = new SpriteRenderer(shader);
    ResourceManager::LoadTexture("src/hello.png", true, "face");
}

void Game::processInput()
{
}

void Game::Update(float dt)
{
}

void Game::Render()
{
    renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(0, 0), 0, glm::vec2(WIDTH, HEIGHT), glm::vec3(1.0f, 1.0f, 1.0f));
}
