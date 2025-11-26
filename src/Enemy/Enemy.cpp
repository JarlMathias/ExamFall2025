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
void Enemy::Draw(ColorDimension worldColor, Vector2d playerPos)
{
    if (isAlive)
    {
        switch (color)
        {
        case BLUE_COLOR:
            if (worldColor == color)
            {
                float triangleScale = 2.0f;

                float halfWidth = (size * triangleScale) * 0.5f;
                float height = (size * triangleScale) * sqrtf(3) / 2.0f;

                Vector2d tip = { 0, -height / 2.0f };
                Vector2d left = { -halfWidth, height / 2.0f };
                Vector2d right = { halfWidth, height / 2.0f };

                Vector2d dir = playerPos.VectorTowardsTarget(position).NormalizeVector();
                float angle = atan2f(dir.y, dir.x) + (PI / 2.0f) + PI;

                Vector2d rotatedTip = tip.Rotate(angle).SetVectorOffset(position);
                Vector2d rotatedLeft = left.Rotate(angle).SetVectorOffset(position);
                Vector2d rotatedRight = right.Rotate(angle).SetVectorOffset(position);

                DrawTriangle
                (
                    { rotatedTip.x, rotatedTip.y },
                    { rotatedLeft.x, rotatedLeft.y },
                    { rotatedRight.x, rotatedRight.y },
                    BLUE
                );
            }
            else
            {
                float triangleScale = 2.0f;

                float halfWidth = (size * triangleScale) * 0.5f;
                float height = (size * triangleScale) * sqrtf(3) / 2.0f;

                Vector2d tip = { 0, -height / 2.0f };
                Vector2d left = { -halfWidth, height / 2.0f };
                Vector2d right = { halfWidth, height / 2.0f };

                Vector2d dir = playerPos.VectorTowardsTarget(position).NormalizeVector();
                float angle = atan2f(dir.y, dir.x) + (PI / 2.0f) + PI;

                Vector2d rotatedTip = tip.Rotate(angle).SetVectorOffset(position);
                Vector2d rotatedLeft = left.Rotate(angle).SetVectorOffset(position);
                Vector2d rotatedRight = right.Rotate(angle).SetVectorOffset(position);

                DrawTriangle
                (
                    { rotatedTip.x, rotatedTip.y },
                    { rotatedLeft.x, rotatedLeft.y },
                    { rotatedRight.x, rotatedRight.y },
                    { BLUE.r, BLUE.g, BLUE.b, 50 }
                );
            }
            break;
        case RED_COLOR:
            if (worldColor == color)
            {
                Vector2d direction = playerPos.VectorTowardsTarget(position);
                float angle = atan2f(direction.y, direction.x) * (180.0f / PI);

                Rectangle rect;
                rect.x = position.x;
                rect.y = position.y;
                rect.width = size * 2;
                rect.height = size * 2;

                Vector2 origin = { size, size };

                DrawRectanglePro(rect, origin, angle, RED);
            }
            else
            {
                Vector2d direction = playerPos.VectorTowardsTarget(position);
                float angle = atan2f(direction.y, direction.x) * (180.0f / PI);

                Rectangle rect;
                rect.x = position.x;
                rect.y = position.y;
                rect.width = size * 2;
                rect.height = size * 2;

                Vector2 origin = { size, size };

                DrawRectanglePro(rect, origin, angle, { RED.r, RED.g, RED.b, 50 });
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