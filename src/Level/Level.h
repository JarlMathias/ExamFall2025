#pragma once
#include "src/Vector2d/Vector2d.h"
#include <iostream>
#include <vector>
#include <raylib.h>
#include "src/ColorDimension.h"

class Level
{
public:
	std::vector<ColorDimension> enemyList;
	std::vector<int> enemyWaves;

	void AddEnemies(std::vector<ColorDimension> colors);
	void AddWaves(std::vector<int> waves);
};

