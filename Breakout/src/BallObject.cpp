#include "BallObject.h"

BallObject::BallObject()
	: GameObject(), m_Radius(12.5f), m_isStuck(true)
{
}

BallObject::BallObject(Texture sprite, glm::vec2 pos, float radius, glm::vec2 velocity)
	: GameObject(sprite, pos, glm::vec2(radius * 2, radius * 2), glm::vec3(1.0f), velocity), m_isStuck(true), m_Radius(radius)
{
}

glm::vec2 BallObject::move(float dt, float window_width)
{
	if (!m_isStuck)
	{
		m_Position += m_Velocity * dt;
		if (m_Position.x <= 0.0f)
		{
			m_Velocity.x = -m_Velocity.x;
			m_Position.x = 0.0f;
		} else if (m_Position.x + m_Size.x >= window_width)
		{
			m_Velocity.x = -m_Velocity.x;
			m_Position.x = window_width - m_Size.x;
		} else if (m_Position.y <= 0.0f)
		{
			m_Velocity.y = -m_Velocity.y;
			m_Position.y = 0.0f;
		}
	}
	return m_Position;
}

void BallObject::reset(glm::vec2 position, glm::vec2 velocity)
{
	m_Position = position;
	m_Velocity = velocity;
	m_isStuck = true;
}
