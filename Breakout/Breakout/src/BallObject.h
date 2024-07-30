#pragma once

#include "GameObject.h"

struct BallObject : public GameObject
{
	float m_Radius;
	bool m_isStuck;

	BallObject();
	BallObject(Texture sprite, glm::vec2 pos, float radius, glm::vec2 velocity);

	glm::vec2 move(float dt, float window_width);
	void reset(glm::vec2 position, glm::vec2 velocity);
};

