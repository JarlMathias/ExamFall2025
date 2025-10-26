#pragma once
#include "src/Vector2d/Vector2d.h"
#include <raylib.h>
#include "src/ColorDimension.h"

class Bullet
{
public:
	Vector2d position;
	Vector2d velocity;
	float radius = 7.5f;
	bool isAlive{ false };
	ColorDimension color;

	void Shoot(Vector2d inStartPos, Vector2d inDirection, float speed);

	void Update();

	void Draw(ColorDimension colorDimension);
};

