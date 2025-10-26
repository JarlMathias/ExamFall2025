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

void Enemy::Draw(bool worldIsBlue)
{
    if (isAlive && isBlue && worldIsBlue)
    {
        DrawCircle(position.x, position.y, size, BLUE);
    }
    else if (isAlive && !isBlue && !worldIsBlue)
    {
        DrawCircle(position.x, position.y, size, RED);
    }
}