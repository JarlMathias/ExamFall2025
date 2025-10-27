#include <raylib.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Player/Player.h"
#include "Bullet/Bullet.h"
#include "Enemy/Enemy.h"
#include "ColorDimension.h"
#include "Ability/Ability.h"

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

    enemies.push_back(e);
    return enemies;
}


void DrawHud(ColorDimension worldColor, std::vector<ColorDimension> holdingColors)
{
    Color blue = { BLUE.r, BLUE.g, BLUE.b, 50 };
    Color red = { RED.r, RED.g, RED.b, 50 };
    Color yellow = { YELLOW.r, YELLOW.g, YELLOW.b, 50 };
    
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

    DrawCircle(p1.x, p1.y, 15.f, blue);
    DrawCircle(p2.x, p2.y, 15.f, red);
    DrawCircle(p3.x, p3.y, 15.f, yellow);

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

    for (int i = 0; i < 3; i++)
    {
        DrawCircle(1200, 950 - (i * 75), 25.f, WHITE);

        DrawCircle(1200, 950 - (i * 75), 20.f, GRAY);
    }

    for (int i = 0; i < holdingColors.size(); i++)
    {
        Color color;

        switch (holdingColors[i])
        {
        case BLUE_COLOR:
            color = BLUE;
            break;
        case RED_COLOR:
            color = RED;
            break;
        case YELLOW_COLOR:
            color = YELLOW;
            break;
        default:
            color = GRAY;
            break;
        }

        DrawCircle(1200, 950 - (i * 75), 20.f, color);
    }
}

void DrawCooldown(Ability ability)
{
    if (!ability.isReady)
    {
        float currentTime = GetTime();
        float elapsed = currentTime - ability.lastUsedTime;
        float progress = elapsed / ability.cooldown;
        if (progress > 1.0f) progress = 1.0f;

        float radius = 40.0f;
        Vector2 center = { 1200, 700 };

        DrawCircleV(center, radius, LIGHTGRAY);

        float angle = 360.0f * progress;
        DrawCircleSector(center, radius, -90, -90 + (360 - angle), 64, Fade(BLACK, 0.7f));

        DrawCircleLines(center.x, center.y, radius, DARKGRAY);
        DrawText(TextFormat("%.1f", ability.cooldown - elapsed), center.x - 15, center.y - 10, 20, WHITE);
    }
    else
    {
        DrawCircle(1200, 700, 40, GREEN);
    }
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
    float bulletSpeed = 500.0f;
    bool spreadEnabled{ false };
    int spreadCount = 5;
    float spreadAngle = 15 * DEG2RAD;

    std::vector<Enemy> enemies;

    Ability ability;
    int abilityEffect;
    bool drawExplosion = false;
    int explosionDuration = 0;
    float explosionRadius = 300.0f;

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

                if (spreadEnabled)
                {
                    for (int i = 0; i < spreadCount; i++)
                    {
                        float angleOffset = ((float)i / (spreadCount - 1) - 0.5f) * spreadAngle;

                        Vector2d spreadDir = dir.Rotate(angleOffset);

                        Bullet b;
                        b.color = worldColor;
                        b.Shoot(player.position, spreadDir, bulletSpeed);
                        bullets.push_back(b);
                    }
                }
                else
                {
                    Bullet b;
                    b.color = worldColor;
                    b.Shoot(player.position, dir, bulletSpeed);
                    bullets.push_back(b);
                }
            }


            if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
            {
                worldColor = static_cast<ColorDimension>((worldColor + 1) % WORLD_COLOR_COUNT);
            }

            // Use Ability
            if (IsKeyPressed(KEY_E))
            {
                if (ability.holdingColors.size() == 3 && ability.isReady)
                {
                    abilityEffect = ability.Use(player, bullets, enemies);

                    switch(abilityEffect)
                    {
                    case 0:
                        break;
                    case 1:
                        enemies.clear();
                        break;
                    case 2:
                        bulletSpeed *= 2;
                        std::cout << bulletSpeed << std::endl;
                        break;
                    case 3:
                        for (auto& e : enemies)
                            e.speed /= 2;
                        break;
                    case 4:
                        drawExplosion = true;
                        enemies.erase(
                            std::remove_if(enemies.begin(), enemies.end(),
                                [&](const Enemy& e) {
                                    return player.position.DistanceToTarget(e.position) < explosionRadius;
                                }),
                            enemies.end());

                        break;
                    case 5:
                        player.shieldActive = true;
                        break;
                    case 6:
                        spreadEnabled = true;
                        break;
                    case 7:
                        player.speed *= 2;
                        break;
                    default:
                        break;
                    }
                }
            }

            // Update Ability
            if (!ability.isReady && GetTime() - ability.lastUsedTime >= ability.cooldown)
            {
                std::cout << abilityEffect << std::endl;
                
                switch (abilityEffect)
                {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    bulletSpeed /= 2;
                    std::cout << bulletSpeed << std::endl;
                    break;
                case 3:
                    for (auto& e : enemies)
                        e.speed *= 2;
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    spreadEnabled = false;
                    break;
                case 7:
                    player.speed /= 2;
                    break;
                default:
                    break;
                }

                ability.isReady = true;
            }

            // Update Bullets
            for (auto& b : bullets)
                b.Update();

            bullets.erase(
                std::remove_if(bullets.begin(), bullets.end(),
                    [](const Bullet& b) { return !b.isAlive; }),
                bullets.end());

            // Update Enemies
            for (int i = 0; i < enemies.size(); i++)
            {
                if (enemies[i].Update(player.position))
                {
                    if (!player.shieldActive)
                    {
                        gamestate = DEATHSCREEN;
                    }
                    else
                    {
                        enemies.erase(enemies.begin() + i);
                        i--;
                        player.shieldActive = false;
                    }
                }
            }

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
                        ability.InsertColor(e.color);
                        
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

            if (drawExplosion && explosionDuration < 15)
            {
                DrawCircle(player.position.x, player.position.y, explosionRadius, { ORANGE.r, ORANGE.g, ORANGE.b, 100 });
                explosionDuration += 1;
            }
            else
            {
                drawExplosion = false;
                explosionDuration = 0;
            }

            DrawHud(worldColor, ability.holdingColors);

            DrawCooldown(ability);

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
