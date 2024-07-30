#pragma once
#include "Shaders/Shader.h"
#include "Textures/Texture.h"
#include <glm/glm.hpp>

class SpriteRenderer
{
public:
    SpriteRenderer(Shader& shader);
    ~SpriteRenderer();

    void DrawSprite(const Texture& texture, const glm::vec2& position, float rotation, const glm::vec2& scale, const glm::vec3& color);
private:
    Shader m_shader;
    unsigned int m_VAO;
};
