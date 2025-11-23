#include "Level.h"

void Level::AddEnemies(std::vector<ColorDimension> colors)
{
	for (int i = 0; i < colors.size(); i++)
	{
		enemyList.push_back(colors[i]);
	}
}

void Level::AddWaves(std::vector<int> waves)
{
	for (int i = 0; i < waves.size(); i++)
	{
		enemyWaves.push_back(waves[i]);
	}
}