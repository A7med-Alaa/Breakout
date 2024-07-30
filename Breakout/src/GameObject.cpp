#include "GameObject.h"

GameObject::GameObject()
	: m_Position(0.0f), m_Rotation(0.0f), m_Size(1.0f, 1.0f), m_Velocity(0.0f), m_Color(1.0f), m_isDestroyed(false), m_isSolid(false), m_Sprite()
{

}

GameObject::GameObject(const Texture& texture, const glm::vec2& pos, const glm::vec2& size, const glm::vec3 color, const glm::vec2& velocity)
	: m_Position(pos), m_Rotation(0.0f), m_Size(size), m_Velocity(velocity), m_Color(color), m_isDestroyed(false), m_isSolid(false), m_Sprite(texture)
{

}

void GameObject::Draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(m_Sprite, m_Position, m_Rotation, m_Size, m_Color);
}
