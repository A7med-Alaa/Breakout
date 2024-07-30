#include "GameLevel.h"
#include <fstream>
#include <sstream>
#include "ResourceManager.h"
#include <iostream>

void GameLevel::Load(const std::string& filePath, int levelWidth, int levelHeight)
{
	m_Bricks.clear();

	std::ifstream levelFile(filePath);
	std::string line;
	GameLevel level;
	unsigned int tileCode;

	std::vector<std::vector<unsigned int>> tileData;
	if (levelFile) {
		while (std::getline(levelFile, line))
		{
			std::istringstream sstream(line);
			std::vector<unsigned int> rows;
			while (sstream >> tileCode) {
				rows.push_back(tileCode);
			}
			tileData.push_back(rows);
		}
	}

	if (tileData.size() > 0)
		Init(tileData, levelWidth, levelHeight);
}

void GameLevel::DrawLevel(SpriteRenderer& renderer)
{
	for (GameObject& brick : m_Bricks)
	{
		if (brick.m_isDestroyed != true) {
			brick.Draw(renderer);
		}
	}

}

bool GameLevel::isCompleted()
{
	for (GameObject& brick : m_Bricks)
	{
		if (brick.m_isDestroyed && brick.m_isSolid) {
			return true;
		}
	}
	return false;
}

void GameLevel::Init(std::vector<std::vector<unsigned int>> tileData, int levelWidth, int levelHeight)
{
	unsigned int width = tileData[0].size();
	unsigned int height = tileData.size();

	float unitWidth = levelWidth / width;
	float unitHeight = levelHeight / height;

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			
			unsigned int currentTile = tileData[y][x];

			//Unbreakable tile
			if (currentTile == 1) {
				glm::vec2 pos(unitWidth * x, unitHeight * y);
				glm::vec2 size(unitWidth, unitHeight);
				GameObject obj(ResourceManager::GetTexture("solid_block"), pos, size, glm::vec3(0.8f, 0.8f, 0.7f));
				obj.m_isSolid = true;
				m_Bricks.push_back(obj);

			}
			else if(currentTile > 1) {
				glm::vec2 pos(unitWidth * x, unitHeight * y);
				glm::vec2 size(unitWidth, unitHeight);
				glm::vec3 color(1.0f, 1.0f, 1.0f);
				if (currentTile == 2)
					color = glm::vec3(0.2f, 0.6f, 1.0f);
				else if (currentTile == 3)
					color = glm::vec3(0.0f, 0.7f, 0.0f);
				else if (currentTile == 4)
					color = glm::vec3(0.8f, 0.8f, 0.4f);
				else if (currentTile == 5)
					color = glm::vec3(1.0f, 0.5f, 0.0f);

				GameObject obj(ResourceManager::GetTexture("block"), pos, size, color);
				m_Bricks.push_back(obj);
			}

		}
	}
}
