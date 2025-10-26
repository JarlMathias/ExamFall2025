#include <raylib.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Player/Player.h"
#include "Bullet/Bullet.h"
#include "Enemy/Enemy.h"
#include "WorldColor.h"

std::vector<Enemy> spawnEnemies(int screenWidth, int screenHeight, Vector2d inTargetPosition, std::vector<Enemy> enemies)
{
    Enemy e;
    e.Spawn(screenWidth, screenHeight, inTargetPosition);

    int randValue = GetRandomValue(0, 2);
    e.color = static_cast<WorldColor>(randValue);

    std::cout << e.color;

    enemies.push_back(e);
    return enemies;
}


void DrawHud(WorldColor worldColor)
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

    DrawCircle(50, 50, 15, blue);
    DrawCircle(100, 50, 15, red);
    DrawCircle(150, 50, 15, yellow);
}

int main()
{
    int screenWidth = 1280;
    int screenHeight = 1024;

    float halfScreenWidth = (float)(screenWidth / 2);
    float halfScreenHeight = (float)(screenHeight / 2);

    WorldColor worldColor = BLUE_COLOR;

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
        // Input & Player
        aimDirection = player.AimDirection();
        player.Move();

        // Shooting
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2d mousePos = { (float)GetMouseX(), (float)GetMouseY() };
            Vector2d dir = player.position.VectorTowardsTarget(mousePos).NormalizeVector();

            Bullet b;
            b.Shoot(player.position, dir, 300.0f);
            bullets.push_back(b);
        }

        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            worldColor = static_cast<WorldColor>((worldColor + 1) % WORLD_COLOR_COUNT);
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
            e.Update(player.position);

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
                if (e.isAlive && b.isAlive && e.position.DistanceToTarget(b.position) < e.size + b.radius && e.color == worldColor)
                {
                    e.isAlive = false;
                    b.isAlive = false;
                }
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground({10, 10, 10, 255});

        player.Draw(aimDirection);

        for (auto& b : bullets)
            b.Draw();

        for (auto& e : enemies)
            e.Draw(worldColor);

        DrawHud(worldColor);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
