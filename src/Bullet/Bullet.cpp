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

void Bullet::Draw(ColorDimension colorDimension)
{
    if (isAlive)
    {
        Color drawColor = WHITE;
        
        switch (color)
        {
        case BLUE_COLOR:
            drawColor = BLUE;
            break;
        case RED_COLOR:
            drawColor = RED;
            break;
        case YELLOW_COLOR:
            drawColor = YELLOW;
            break;
        }

        if (color == colorDimension)
        {
            DrawCircle(position.x, position.y, radius, {255, 255, 255, 255});
            drawColor.a = 255;
        }
        else
        {
            DrawCircle(position.x, position.y, radius, {255, 255, 255, 100});
            drawColor.a = 50;
        }

        DrawCircle(position.x, position.y, radius - 1.f, drawColor);
    }
}
