#include <raylib.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Player/Player.h"
#include "Bullet/Bullet.h"
#include "Enemy/Enemy.h"
#include "ColorDimension.h"

int score = 0;
enum Gamestate {
    PLAYING,
    DEATHSCREEN
};

std::vector<Enemy> spawnEnemies(int screenWidth, int screenHeight, Vector2d inTargetPosition, std::vector<Enemy> enemies)
{
    Enemy e;
    e.Spawn(screenWidth, screenHeight, inTargetPosition);

    int randValue = GetRandomValue(0, 2);
    e.color = static_cast<ColorDimension>(randValue);

    std::cout << e.color;

    enemies.push_back(e);
    return enemies;
}


void DrawHud(ColorDimension worldColor)
{
    Color blue = { 0, 121, 241, 50 };
    Color red = { 230, 41, 55, 50 };
    Color yellow = { 253, 249, 0, 50 };
    
    switch (worldColor)
    {
    case BLUE_COLOR:
        blue.a = 255;
        break;
    case RED_COLOR:
        red.a = 255;
        break;
    case YELLOW_COLOR:
        yellow.a = 255;
        break;
    }

    Vector2d center = { 100, 100 };
    float radius = 50.f;

    Vector2d p1;
    p1 = p1.CircularMotion(center, radius, 0.0f);
    Vector2d p2;
    p2 = p2.CircularMotion(center, radius, 2.0f * PI / 3.0f);
    Vector2d p3;
    p3 = p3.CircularMotion(center, radius, 4.0f * PI / 3.0f);

    DrawCircle(p1.x, p1.y, 15, blue);
    DrawCircle(p2.x, p2.y, 15, red);
    DrawCircle(p3.x, p3.y, 15, yellow);

    std::vector<Vector2d> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);

    Vector2d previousVector = p3;
    float lineOffset = 25.f;
    
    for (Vector2d p : points)
    {
        Vector2d dir = previousVector.VectorTowardsTarget(p);
        float distance = dir.CalculateMagnitude();
        if (distance == 0.0f) {
            previousVector = p;
            continue;
        }
        dir = dir.NormalizeVector();

        Vector2d shaftStart = previousVector.SetVectorOffset(dir.ScaleVector(lineOffset));
        Vector2d shaftEnd = p.SetVectorOffset(dir.ScaleVector(-lineOffset));

        DrawLine(shaftStart.x, shaftStart.y, shaftEnd.x, shaftEnd.y, WHITE);

        Vector2d tip = shaftEnd;

        float arrowSize = 12.0f;
        float arrowAngle = DEG2RAD * 25.0f;

        Vector2d wingRight = dir.Rotate(-arrowAngle).ScaleVector(-arrowSize);
        Vector2d wingLeft = dir.Rotate(arrowAngle).ScaleVector(-arrowSize);

        Vector2d rightPoint = tip.SetVectorOffset(wingRight);
        Vector2d leftPoint = tip.SetVectorOffset(wingLeft);

        DrawLine(tip.x, tip.y, rightPoint.x, rightPoint.y, WHITE);
        DrawLine(tip.x, tip.y, leftPoint.x, leftPoint.y, WHITE);

        previousVector = p;
    }

    DrawText(TextFormat("Score: %i", score), 1100, 50, 30, WHITE);
}

int main()
{
    int screenWidth = 1280;
    int screenHeight = 1024;

    float halfScreenWidth = (float)(screenWidth / 2);
    float halfScreenHeight = (float)(screenHeight / 2);

    ColorDimension worldColor = BLUE_COLOR;
    enum Gamestate gamestate = PLAYING;

    Player player;
    player.position = { halfScreenWidth, halfScreenHeight };

    Vector2d aimDirection;

    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;

    // Setup
    InitWindow(screenWidth, screenHeight, "ExamFall2025");
    SetTargetFPS(60);

    for (int i = 0; i < 3; i++)
    {
        enemies = spawnEnemies(screenWidth, screenHeight, player.position, enemies);
    }

    // Main Game Loop
    while (!WindowShouldClose())
    {
        switch (gamestate)
        {
        case PLAYING:
            // Input & Player
            aimDirection = player.AimDirection();
            player.Move();

            // Shooting
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2d mousePos = { (float)GetMouseX(), (float)GetMouseY() };
                Vector2d dir = player.position.VectorTowardsTarget(mousePos).NormalizeVector();

                Bullet b;
                b.color = worldColor;
                b.Shoot(player.position, dir, 500.0f);
                bullets.push_back(b);
            }

            if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
            {
                worldColor = static_cast<ColorDimension>((worldColor + 1) % WORLD_COLOR_COUNT);
            }

            // Update Bullets
            for (auto& b : bullets)
                b.Update();

            bullets.erase(
                std::remove_if(bullets.begin(), bullets.end(),
                    [](const Bullet& b) { return !b.isAlive; }),
                bullets.end());

            // Update Enemies
            for (auto& e : enemies)
                if (e.Update(player.position))
                {
                    gamestate = DEATHSCREEN;
                };

            enemies.erase(
                std::remove_if(enemies.begin(), enemies.end(),
                    [](const Enemy& e) { return !e.isAlive; }),
                enemies.end());

            // Randomly spawn new enemies over time
            if (GetRandomValue(0, 100) == 0 && enemies.size() < 15)
            {
                enemies = spawnEnemies(screenWidth, screenHeight, player.position, enemies);
            }

            // Make sures theres always one enemy on screen
            if (enemies.size() == 0)
            {
                enemies = spawnEnemies(screenWidth, screenHeight, player.position, enemies);
            }

            // Bullet–enemy collision
            for (auto& e : enemies)
            {
                for (auto& b : bullets)
                {
                    if (e.isAlive && b.isAlive && e.position.DistanceToTarget(b.position) < e.size + b.radius && e.color == b.color)
                    {
                        e.isAlive = false;
                        b.isAlive = false;
                        score += 1;
                    }
                }
            }

            // Draw
            BeginDrawing();
            ClearBackground({ 10, 10, 10, 255 });

            player.Draw(aimDirection);

            for (auto& b : bullets)
                b.Draw(worldColor);

            for (auto& e : enemies)
                e.Draw(worldColor);

            DrawHud(worldColor);

            EndDrawing();

            break;

        case DEATHSCREEN:
            BeginDrawing();
            ClearBackground({ 10, 10, 10, 255 });

            DrawText("You Lost!", 400, 400, 100, WHITE);
            DrawText(TextFormat("Score: %i", score), 400, 600, 100, WHITE);

            EndDrawing();
            break;
        }
    }

    CloseWindow();
    return 0;
}
