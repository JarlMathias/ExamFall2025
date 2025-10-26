#include "Enemy.h"

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

void Enemy::Update(Vector2d inTargetPosition)
{   
    if (isAlive)
    {
        Vector2d direction = position.VectorTowardsTarget(inTargetPosition).NormalizeVector();
        position = position.SetVectorOffset(direction.ScaleVector(speed * GetFrameTime()));

        if (position.DistanceToTarget(inTargetPosition) < 45.f)
        {
            std::cout << "game over";
        }
    }
}

void Enemy::Draw(WorldColor worldColor)
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
                DrawCircle(position.x, position.y, size, { 0, 121, 241, 50 });
            }
            break;
        case RED_COLOR:
            if (worldColor == color)
            {
                DrawCircle(position.x, position.y, size, RED);
            }
            else
            {
                DrawCircle(position.x, position.y, size, { 230, 41, 55, 50 });
            }
            break;
        case YELLOW_COLOR:
            if (worldColor == color)
            {
                DrawCircle(position.x, position.y, size, YELLOW);
            }
            else
            {
                DrawCircle(position.x, position.y, size, { 253, 249, 0, 50 });
            }
            break;
        }
    }
}