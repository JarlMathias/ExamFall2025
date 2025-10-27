#pragma once
#include "src/Vector2d/Vector2d.h"
#include <raylib.h>

class Player
{
public:
	Vector2d position{ 0.f, 0.f };
	float speed = 200.f;
	float size = 25.f;
	Color color = GREEN;
	Color aimColor = WHITE;
	bool shieldActive = false;

	void Move();

	void Draw(Vector2d aimDirection);

	Vector2d AimDirection();
};

