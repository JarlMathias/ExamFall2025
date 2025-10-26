#pragma once
#include "src/Vector2d/Vector2d.h"
#include <raylib.h>

class Bullet
{
public:
	Vector2d position;
	Vector2d velocity;
	float radius = 5.f;
	bool isAlive{ false };

	void Shoot(Vector2d inStartPos, Vector2d inDirection, float speed);

	void Update();

	void Draw();
};

