#pragma once
#include "src/ColorDimension.h"
#include "src/Enemy/Enemy.h"
#include "src/Player/Player.h"
#include "src/Bullet/Bullet.h"
#include <vector>
#include <iostream>
#include <algorithm>

class Ability
{
public:
	float cooldown;
	float lastUsedTime;
	bool isReady = true;
	std::vector <ColorDimension> holdingColors;

	void InsertColor(ColorDimension color);

	bool IsHoldingColor(ColorDimension color);

	int Use(Player player, std::vector<Bullet> bullets, std::vector<Enemy> enemies);
};