#include "Bullet.h"

void Bullet::Shoot(Vector2d inStartPos, Vector2d inDirection, float speed)
{
    position = inStartPos;
    velocity = inDirection.ScaleVector(speed);
    isAlive = true;
}

void Bullet::Update()
{
    if (isAlive)
    {
        position = position.SetVectorOffset(velocity.ScaleVector(GetFrameTime()));

        if (position.x < 0 || position.x > GetScreenWidth() ||
            position.y < 0 || position.y > GetScreenHeight())
        {
            isAlive = false;
        }
    }
}

void Bullet::Draw()
{
    if (isAlive)
    {
        DrawCircle(position.x, position.y, radius, YELLOW);
    }
}
