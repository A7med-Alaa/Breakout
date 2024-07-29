#pragma once
#include <glm/glm.hpp>
#include "Textures/Texture.h"
#include "SpriteRenderer.h"

struct GameObject
{
	glm::vec2 m_Position, m_Size, m_Velocity;
	glm::vec3 m_Color;
	float m_Rotation;
	bool m_isDestroyed;
	bool m_isSolid;
	Texture m_Sprite;

	GameObject();
	GameObject(const Texture& texture, const glm::vec2& pos, const glm::vec2& size, const glm::vec3 color = glm::vec3(1.0f),
		const glm::vec2& velocity = glm::vec2(0.0f, 0.0f));

	virtual void Draw(SpriteRenderer& renderer);
};

