#include "Level.h"

// Adds enemies to the level
void Level::AddEnemies(std::vector<ColorDimension> colors)
{
	for (int i = 0; i < colors.size(); i++)
	{
		enemyList.push_back(colors[i]);
	}
}

// Adds waves to the level
void Level::AddWaves(std::vector<int> waves)
{
	for (int i = 0; i < waves.size(); i++)
	{
		enemyWaves.push_back(waves[i]);
	}
}