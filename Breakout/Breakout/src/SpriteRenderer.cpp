#include "SpriteRenderer.h"
#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

SpriteRenderer::SpriteRenderer(Shader& shader)
    : m_shader(shader)
{
    unsigned int VBO;
    float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    std::cout << "\nSpriteRenderer Initiated.\n";
}

SpriteRenderer::~SpriteRenderer()
{
    std::cout << "\nSpriteRenderer Deleted.";
    glDeleteVertexArrays(1, &m_VAO);
}

void SpriteRenderer::DrawSprite(const Texture& texture, const glm::vec2& position, float rotation, const glm::vec2& scale,
    const glm::vec3& color)
{
    m_shader.Use();
    
    glm::mat4 model = glm::identity<glm::mat4>();
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5 * scale.x, 0.5 * scale.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5 * scale.x, -0.5 * scale.y, 0.0f));
    model = glm::scale(model, glm::vec3(scale, 1.0f));

    m_shader.setMat4("model", model);
    m_shader.setVec3("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    // std::cout << "\nDraw: " << texture.internal_format;
    texture.Bind();
    
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
