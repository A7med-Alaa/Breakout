#pragma once
#include <vector>
#include "GameObject.h"

struct GameLevel
{
	std::vector<GameObject> m_Bricks;

	GameLevel() {}
	
	void Load(const std::string& filePath, int levelWidth, int levelHeight);
	
	void DrawLevel(SpriteRenderer& renderer);

	bool isCompleted();

private:
	void Init(std::vector<std::vector<unsigned int>> tileData, int levelWidth, int levelHeight);
};

