#include <raylib.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Player/Player.h"
#include "Bullet/Bullet.h"
#include "Enemy/Enemy.h"

std::vector<Enemy> spawnEnemies(int screenWidth, int screenHeight, Vector2d inTargetPosition, std::vector<Enemy> enemies)
{
    Enemy e;
    e.Spawn(screenWidth, screenHeight, inTargetPosition);
    if (GetRandomValue(0, 1) == 0)
    {
        e.isBlue = true;
    }
    enemies.push_back(e);

    return enemies;
}

int main()
{
    int screenWidth = 1280;
    int screenHeight = 1024;

    float halfScreenWidth = (float)(screenWidth / 2);
    float halfScreenHeight = (float)(screenHeight / 2);

    bool worldIsBlue{ false };

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
            if (worldIsBlue)
            {
                worldIsBlue = false;
            }
            else
            {
                worldIsBlue = true;
            }
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
                if (e.isAlive && b.isAlive && e.position.DistanceToTarget(b.position) < e.size + b.radius && e.isBlue == worldIsBlue)
                {
                    e.isAlive = false;
                    b.isAlive = false;
                }
            }
        }

        // Draw
        BeginDrawing();
        if (worldIsBlue)
        {
            ClearBackground({ 115, 42, 42, 255});
        }
        else
        {
            ClearBackground({ 16, 16, 79, 255});
        }

        player.Draw(aimDirection);

        for (auto& b : bullets)
            b.Draw();

        for (auto& e : enemies)
            e.Draw(worldIsBlue);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
