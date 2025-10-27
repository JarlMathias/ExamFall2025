#include "Enemy.h"

// Function to initiate new enemies
void Enemy::Spawn(int inScreenWidth, int inScreenHeight, Vector2d inTargetPosition)
{
    Vector2d randPos = { (float)(rand() % inScreenWidth), (float)(rand() % inScreenHeight) };

    while (randPos.DistanceToTarget(inTargetPosition) < 400.f)
    {
        randPos = { (float)(rand() % inScreenWidth), (float)(rand() % inScreenHeight) };
    }

    position = randPos;
    isAlive = true;
}

// Function to update enemies
bool Enemy::Update(Vector2d inTargetPosition)
{   
    if (isAlive)
    {
        Vector2d direction = position.VectorTowardsTarget(inTargetPosition).NormalizeVector();
        position = position.SetVectorOffset(direction.ScaleVector(speed * GetFrameTime()));

        if (position.DistanceToTarget(inTargetPosition) < 45.f)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

// Function to draw enemies
void Enemy::Draw(ColorDimension worldColor)
{
    if (isAlive)
    {
        switch (color)
        {
        case BLUE_COLOR:
            if (worldColor == color)
            {
                DrawCircle(position.x, position.y, size, BLUE);
            }
            else
            {
                DrawCircle(position.x, position.y, size, { BLUE.r, BLUE.g, BLUE.b, 50 });
            }
            break;
        case RED_COLOR:
            if (worldColor == color)
            {
                DrawCircle(position.x, position.y, size, RED);
            }
            else
            {
                DrawCircle(position.x, position.y, size, { RED.r, RED.g, RED.b, 50 });
            }
            break;
        case YELLOW_COLOR:
            if (worldColor == color)
            {
                DrawCircle(position.x, position.y, size, YELLOW);
            }
            else
            {
                DrawCircle(position.x, position.y, size, { YELLOW.r, YELLOW.g, YELLOW.b, 50 });
            }
            break;
        }
    }
}