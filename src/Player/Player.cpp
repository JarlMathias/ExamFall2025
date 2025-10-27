#include "Player.h"
#include <iostream>

// Function to move the player
void Player::Move()
{
	Vector2d offsetPosition{ 0.f, 0.f };
	if (IsKeyDown(KEY_W))
	{
		offsetPosition.y -= 1;
	}
	if (IsKeyDown(KEY_A))
	{
		offsetPosition.x -= 1;
	}
	if (IsKeyDown(KEY_S))
	{
		offsetPosition.y += 1;
	}
	if (IsKeyDown(KEY_D))
	{
		offsetPosition.x += 1;
	}

	offsetPosition = offsetPosition.NormalizeVector();

	position = position.SetVectorOffset(offsetPosition.ScaleVector(speed * GetFrameTime()));
}

// Function to draw the player
void Player::Draw(Vector2d aimDirection)
{
	DrawCircle(position.x, position.y, size, color);
	if (shieldActive)
	{
		DrawCircle(position.x, position.y, size * 1.25, { SKYBLUE.r, SKYBLUE.g, SKYBLUE.b, 150 });
	}
	DrawLine(
		position.x,
		position.y,
		position.x + aimDirection.x * 30.f,
		position.y + aimDirection.y * 30.f,
		aimColor
	);
}

// Function to get the aim direction
Vector2d Player::AimDirection()
{
	Vector2d mousePosition{ GetMouseX(), GetMouseY() };
	Vector2d towardsMousePosition = position.VectorTowardsTarget(mousePosition).NormalizeVector();
	
	return towardsMousePosition;
}