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
#include "Level/Level.h"

// Set global variables Gamestate
enum Gamestate {
    PLAYING,
    DEATHSCREEN,
    VICTORY,
    PAUSED
};

std::vector<Level> levels;

// Sound variables
Sound shootSound;
Sound enemyDeathSound;
Sound explosionSound;
Music music;

// The level data
void InitLevels()
{
    int n = 10; // number of levels

    for (int i = 0; i < n; ++i) {
        levels.emplace_back();
    }
    
    // ================= LEVEL 0  =================
    {
        std::vector<int> level0Waves{ 3, 3 };
        std::vector<ColorDimension> level0Enemies
        {
            BLUE_COLOR, BLUE_COLOR, BLUE_COLOR,      // 3
            YELLOW_COLOR, RED_COLOR, YELLOW_COLOR       // 3
        };
        levels[0].AddEnemies(level0Enemies);
        levels[0].AddWaves(level0Waves);
    }

    // ================= LEVEL 1 =================
    {
        std::vector<int> level1Waves{ 4, 4, 2 };
        std::vector<ColorDimension> level1Enemies
        {
            BLUE_COLOR, YELLOW_COLOR, BLUE_COLOR, YELLOW_COLOR,     // 4
            YELLOW_COLOR, BLUE_COLOR, YELLOW_COLOR, BLUE_COLOR,     // 4
            BLUE_COLOR, YELLOW_COLOR                                // 2
        };
        levels[1].AddEnemies(level1Enemies);
        levels[1].AddWaves(level1Waves);
    }

    // ================= LEVEL 2 =================
    {
        std::vector<int> level2Waves{ 5, 3 };
        std::vector<ColorDimension> level2Enemies
        {
            RED_COLOR, RED_COLOR, RED_COLOR, BLUE_COLOR, RED_COLOR,   // 5
            RED_COLOR, RED_COLOR, BLUE_COLOR                          // 3
        };
        levels[2].AddEnemies(level2Enemies);
        levels[2].AddWaves(level2Waves);
    }

    // ================= LEVEL 3 =================
    {
        std::vector<int> level3Waves{ 4, 6, 4 };
        std::vector<ColorDimension> level3Enemies
        {
            RED_COLOR, YELLOW_COLOR, RED_COLOR, YELLOW_COLOR,         // 4
            YELLOW_COLOR, RED_COLOR, RED_COLOR, YELLOW_COLOR, YELLOW_COLOR, RED_COLOR, // 6
            RED_COLOR, YELLOW_COLOR, RED_COLOR, YELLOW_COLOR          // 4
        };
        levels[3].AddEnemies(level3Enemies);
        levels[3].AddWaves(level3Waves);
    }

    // ================= LEVEL 4 =================
    {
        std::vector<int> level4Waves{ 6, 5 };
        std::vector<ColorDimension> level4Enemies
        {
            BLUE_COLOR, RED_COLOR, BLUE_COLOR, BLUE_COLOR, RED_COLOR, RED_COLOR, // 6
            RED_COLOR, BLUE_COLOR, RED_COLOR, BLUE_COLOR, RED_COLOR              // 5
        };
        levels[4].AddEnemies(level4Enemies);
        levels[4].AddWaves(level4Waves);
    }

    // ================= LEVEL 5 =================
    {
        std::vector<int> level5Waves{ 4, 7 };
        std::vector<ColorDimension> level5Enemies
        {
            BLUE_COLOR, BLUE_COLOR, YELLOW_COLOR, RED_COLOR,                     // 4
            RED_COLOR, BLUE_COLOR, RED_COLOR, YELLOW_COLOR, RED_COLOR, BLUE_COLOR, YELLOW_COLOR // 7
        };
        levels[5].AddEnemies(level5Enemies);
        levels[5].AddWaves(level5Waves);
    }

    // ================= LEVEL 6 =================
    {
        std::vector<int> level6Waves{ 6, 6, 4 };
        std::vector<ColorDimension> level6Enemies
        {
            YELLOW_COLOR, YELLOW_COLOR, YELLOW_COLOR, YELLOW_COLOR, YELLOW_COLOR, YELLOW_COLOR,
            YELLOW_COLOR, YELLOW_COLOR, YELLOW_COLOR, YELLOW_COLOR, YELLOW_COLOR, YELLOW_COLOR,
            YELLOW_COLOR, YELLOW_COLOR, YELLOW_COLOR, YELLOW_COLOR
        };
        levels[6].AddEnemies(level6Enemies);
        levels[6].AddWaves(level6Waves);
    }

    // ================= LEVEL 7 =================
    {
        std::vector<int> level7Waves{ 7, 5, 7 };
        std::vector<ColorDimension> level7Enemies
        {
            BLUE_COLOR, YELLOW_COLOR, BLUE_COLOR, BLUE_COLOR, YELLOW_COLOR, YELLOW_COLOR, BLUE_COLOR,   // 7
            YELLOW_COLOR, BLUE_COLOR, YELLOW_COLOR, BLUE_COLOR, YELLOW_COLOR,                           // 5
            BLUE_COLOR, YELLOW_COLOR, BLUE_COLOR, YELLOW_COLOR, BLUE_COLOR, YELLOW_COLOR, BLUE_COLOR    // 7
        };
        levels[7].AddEnemies(level7Enemies);
        levels[7].AddWaves(level7Waves);
    }

    // ================= LEVEL 8 =================
    {
        std::vector<int> level8Waves{ 8, 6 };
        std::vector<ColorDimension> level8Enemies
        {
            RED_COLOR, RED_COLOR, BLUE_COLOR, RED_COLOR, YELLOW_COLOR, RED_COLOR, RED_COLOR, BLUE_COLOR, // 8
            RED_COLOR, RED_COLOR, RED_COLOR, YELLOW_COLOR, RED_COLOR, RED_COLOR                           // 6
        };
        levels[8].AddEnemies(level8Enemies);
        levels[8].AddWaves(level8Waves);
    }

    // ================= LEVEL 9 =================
    {
        std::vector<int> level9Waves{ 10, 8, 10 };
        std::vector<ColorDimension> level9Enemies
        {
            RED_COLOR, RED_COLOR, RED_COLOR, BLUE_COLOR, YELLOW_COLOR,
            RED_COLOR, RED_COLOR, BLUE_COLOR, RED_COLOR, YELLOW_COLOR,

            BLUE_COLOR, BLUE_COLOR, RED_COLOR, YELLOW_COLOR,
            BLUE_COLOR, YELLOW_COLOR, BLUE_COLOR, RED_COLOR,

            YELLOW_COLOR, RED_COLOR, BLUE_COLOR, RED_COLOR, YELLOW_COLOR,
            RED_COLOR, YELLOW_COLOR, BLUE_COLOR, RED_COLOR, BLUE_COLOR
        };
        levels[9].AddEnemies(level9Enemies);
        levels[9].AddWaves(level9Waves);
    }
}

// Function to spawn enemies at random location and add them to the vector
std::vector<Enemy> spawnEnemies(int screenWidth, int screenHeight, Vector2d inTargetPosition, std::vector<Enemy> enemies, ColorDimension color)
{
    Enemy e;
    e.Spawn(screenWidth, screenHeight, inTargetPosition);

    e.color = static_cast<ColorDimension>(color);

    enemies.push_back(e);
    return enemies;
}

// Function to draw several HUD elements
void DrawHud(ColorDimension worldColor, std::vector<ColorDimension> holdingColors, int halfScreenWidth, int halfScreenHeight, int levelProgress, int currentLevel, int currentWave, float gameTime)
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

    // Creates three points in a circle to act as placement for the three color circles
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
    
    // Draws arrows pointing between the HUD elements
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

    // Displays the time
    DrawText(TextFormat("Time: %.1f", gameTime), 1100, 50, 30, WHITE);

    // Displays the currently held "colors" for the ability
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
    
    // Displays a progressbar for the progress in the current level
    DrawRectangle(halfScreenWidth / 2, 40, halfScreenWidth, 30, WHITE);
    DrawRectangle((halfScreenWidth / 2) + 5, 45, (int)levelProgress, 20, GREEN);

    // Displays which level and wave the player is on
    DrawText(TextFormat("Level %i", currentLevel), (halfScreenWidth / 2) + 5, 10, 20, WHITE);
    DrawText(TextFormat("Wave %i", currentWave), ((halfScreenWidth / 2) + halfScreenWidth) - 70, 10, 20, WHITE);

    DrawText("Press P to pause", 50, 950, 30, WHITE);
}

// Draws the Cooldown circle
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

// Main
int main()
{
    // Setup variables
    int screenWidth = 1280;
    int screenHeight = 1024;

    float halfScreenWidth = (float)(screenWidth / 2);
    float halfScreenHeight = (float)(screenHeight / 2);

    InitLevels();
    int currentLevel = 0;
    int currentWave = 0;
    int totalWaves = 0;
    float waveProgressSize = 0;
    float enemyProgressSize = 0;
    float levelProgress = 0;
    float gameTime = 0.0;
    float lastFrame = 0.0;

    ColorDimension worldColor = BLUE_COLOR;
    int colorSwapCD = 0;
    int maxSwapCD = 30;
    enum Gamestate gamestate = PAUSED;

    Player player;
    player.position = { halfScreenWidth, halfScreenHeight };

    Vector2d aimDirection;

    std::vector<Bullet> bullets;
    float bulletSpeed = 500.0f;
    bool spreadEnabled{ false };
    int spreadCount = 5;
    float spreadAngle = 15 * DEG2RAD;
    bool autoShoot = false;
    int shootCD = 0;
    int maxShootCD = 25;
    bool machineGun = false;
    int machineGunCD = 0;
    int maxMachineGunCD = 5;

    std::vector<Enemy> enemies;

    Ability ability;
    int abilityEffect;
    bool drawExplosion = false;
    int explosionDuration = 0;
    float explosionRadius = 300.0f;

    // Setup
    InitWindow(screenWidth, screenHeight, "ExamFall2025");
    InitAudioDevice();
    SetTargetFPS(60);

    // Sound setup
    shootSound = LoadSound("resources/shoot.wav");
    enemyDeathSound = LoadSound("resources/enemyDeathSound.wav");
    explosionSound = LoadSound("resources/explosion.wav");
    music = LoadMusicStream("resources/music.mp3");

    SetSoundVolume(shootSound, 0.1f);
    SetSoundVolume(enemyDeathSound, 0.02f);
    SetSoundVolume(explosionSound, 1.0f);
    SetMusicVolume(music, 0.1f);

    PlayMusicStream(music);

    // Spawns the initial enemies for the first level and wave
    for (int i = 0; i < levels[currentLevel].enemyWaves[currentWave]; i++)
    {
        if (currentWave == 0)
        {
            enemies = spawnEnemies(screenWidth, screenHeight, player.position, enemies, levels[currentLevel].enemyList[i]);
        }
        else
        {
            int spawnedEnemies = 0;
            for (int j = 0; j < currentWave; j++)
            {
                spawnedEnemies += levels[currentLevel].enemyWaves[j];
            }
            enemies = spawnEnemies(screenWidth, screenHeight, player.position, enemies, levels[currentLevel].enemyList[spawnedEnemies + i]);
        }
    }

    for (int num : levels[currentLevel].enemyWaves)
    {
        totalWaves += 1;
    }

    // Main Game Loop
    while (!WindowShouldClose())
    {
        float now = GetTime();
        float delta = now - lastFrame;
        lastFrame = now;

        UpdateMusicStream(music);

        switch (gamestate)
        {
        case PLAYING:
            // Input and Player control
            aimDirection = player.AimDirection();
            player.Move();

            gameTime += delta;

            // Function for shooting
            if ((IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && shootCD == 0) || (autoShoot && shootCD == 0) ||(machineGun && machineGunCD == 0))
            {
                Vector2d mousePos = { (float)GetMouseX(), (float)GetMouseY() };
                Vector2d dir = player.position.VectorTowardsTarget(mousePos).NormalizeVector();

                // Shoots in a spread pattern if respective ability is active
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

                shootCD = maxShootCD;
                machineGunCD = maxMachineGunCD;

                PlaySound(shootSound);
            }

            if (shootCD != 0)
            {
                shootCD -= 1;
            }

            if (machineGunCD != 0)
            {
                machineGunCD -= 1;
            }

            if (IsKeyPressed(KEY_C))
            {
                autoShoot = !autoShoot;
            }

            // Changes the current Color Dimension / shootable enemies
            if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && colorSwapCD == 0)
            {
                worldColor = static_cast<ColorDimension>((worldColor + 1) % WORLD_COLOR_COUNT);
                colorSwapCD = maxSwapCD;
            }

            // Use Ability
            if (IsKeyPressed(KEY_E))
            {
                if (ability.holdingColors.size() == 3 && ability.isReady)
                {
                    abilityEffect = ability.Use();

                    switch(abilityEffect)
                    {
                    case 0:
                        break;
                    case 1:
                        machineGun = true;
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
                        PlaySound(explosionSound);
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

            // Update/Reset Ability
            if (!ability.isReady && GetTime() - ability.lastUsedTime >= ability.cooldown)
            {
                std::cout << abilityEffect << std::endl;
                
                switch (abilityEffect)
                {
                case 0:
                    break;
                case 1:
                    machineGun = false;
                    break;
                case 2:
                    bulletSpeed /= 2;
                    std::cout << bulletSpeed << std::endl;
                    break;
                case 3:
                    for (auto& e : enemies)
                        e.speed == 150.0f;
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

            enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& e) { return !e.isAlive; }), enemies.end());

            // Updates level and wave progression
            if (enemies.size() == 0)
            {
                if (currentWave + 1 == levels[currentLevel].enemyWaves.size())
                {
                    if (levels.size() > currentLevel + 1)
                    {
                        currentLevel += 1;
                        currentWave = 0;
                        std::cout << "level increased" << std::endl;

                        totalWaves = 0;
                        for (int num : levels[currentLevel].enemyWaves)
                        {
                            totalWaves += 1;
                        }
                    }
                    else
                    {
                        gamestate = VICTORY;
                    }
                }
                else
                {
                    std::cout << currentWave << std::endl;

                    currentWave += 1;
                    std::cout << "wave increased" << std::endl;
                }

                for (int i = 0; i < levels[currentLevel].enemyWaves[currentWave]; i++)
                {
                    if (currentWave == 0)
                    {
                        enemies = spawnEnemies(screenWidth, screenHeight, player.position, enemies, levels[currentLevel].enemyList[i]);
                    }
                    else
                    {
                        int spawnedEnemies = 0;
                        for (int j = 0; j < currentWave; j++)
                        {
                            spawnedEnemies += levels[currentLevel].enemyWaves[j];
                        }
                        enemies = spawnEnemies(screenWidth, screenHeight, player.position, enemies, levels[currentLevel].enemyList[spawnedEnemies + i]);
                    }
                }
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

                        PlaySound(enemyDeathSound);
                    }
                }
            }

            // Pauses the game
            if (IsKeyPressed(KEY_P))
            {
                gamestate = PAUSED;
            }

            // Draw
            BeginDrawing();
            ClearBackground({ 10, 10, 10, 255 });

            player.Draw(aimDirection);

            for (auto& b : bullets)
                b.Draw(worldColor);

            for (auto& e : enemies)
                e.Draw(worldColor, player.position);

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

            if (colorSwapCD != 0)
            {
                colorSwapCD -= 1;
                DrawRectangle(player.position.x - player.size, player.position.y - (player.size + 20), ((float)colorSwapCD / (float)maxSwapCD) * (float)player.size * 2.0f, 10, LIME);
            }

            // Math for progress bar
            waveProgressSize = (float)(halfScreenWidth - 10) / (float)totalWaves;
            enemyProgressSize = waveProgressSize / (float)levels[currentLevel].enemyWaves[currentWave];
            levelProgress = (enemyProgressSize * (float)(levels[currentLevel].enemyWaves[currentWave] - enemies.size())) + (waveProgressSize * currentWave);

            DrawHud(worldColor, ability.holdingColors, halfScreenWidth, halfScreenHeight, levelProgress, currentLevel, currentWave, gameTime);

            DrawCooldown(ability);

            // Displays what ability the player can use
            if (ability.holdingColors.size() == 3)
            {
                switch (ability.CanUse())
                {
                case 0:
                    break;
                case 1:
                    DrawText("Machine Gun", 950, 940, 30, WHITE);
                    break;
                case 2:
                    DrawText("Bullet speed", 950, 940, 30, WHITE);
                    break;
                case 3:
                    DrawText("Enemy slow", 1000, 940, 30, WHITE);
                    break;
                case 4:
                    DrawText("Explosion", 1000, 940, 30, WHITE);
                    break;
                case 5:
                    DrawText("Shield", 1050, 940, 30, WHITE);
                    break;
                case 6:
                    DrawText("Bullet spread", 950, 940, 30, WHITE);
                    break;
                case 7:
                    DrawText("Speed", 1050, 940, 30, WHITE);
                    break;
                default:
                    break;
                }
            }

            EndDrawing();

            break;

        // Deathscreen when getting hit
        case DEATHSCREEN:
        {
            BeginDrawing();
            ClearBackground({ 10, 10, 10, 255 });

            int panelWidth = 600;
            int panelHeight = 450;
            int panelX = (1280 - panelWidth) / 2;
            int panelY = (1024 - panelHeight) / 2;
            int centerX = 1280 / 2;

            DrawRectangle(panelX, panelY, panelWidth, panelHeight, Fade(BLACK, 0.5f));
            DrawRectangleLines(panelX, panelY, panelWidth, panelHeight, WHITE);

            int titleFont = 100;
            int infoFont = 60;

            DrawText("You Lost!",
                centerX - MeasureText("You Lost!", titleFont) / 2,
                panelY + 40,
                titleFont,
                WHITE);

            DrawText(TextFormat("Level: %i", currentLevel),
                centerX - MeasureText(TextFormat("Level: %i", currentLevel), infoFont) / 2,
                panelY + 200,
                infoFont,
                WHITE);

            DrawText(TextFormat("Wave: %i", currentWave),
                centerX - MeasureText(TextFormat("Wave: %i", currentWave), infoFont) / 2,
                panelY + 290,
                infoFont,
                WHITE);

            EndDrawing();
        }
        break;

        // Screen that displays after winning the game (clearing level 10)
        case VICTORY:
        {
            BeginDrawing();
            ClearBackground({ 10, 10, 10, 255 });

            int panelWidth = 600;
            int panelHeight = 400;
            int panelX = (1280 - panelWidth) / 2;
            int panelY = (1024 - panelHeight) / 2;
            int centerX = 1280 / 2;

            DrawRectangle(panelX, panelY, panelWidth, panelHeight, Fade(BLACK, 0.5f));
            DrawRectangleLines(panelX, panelY, panelWidth, panelHeight, WHITE);

            int titleFont = 100;
            int infoFont = 60;

            DrawText("You Won!",
                centerX - MeasureText("You Won!", titleFont) / 2,
                panelY + 40,
                titleFont,
                WHITE);

            DrawText(TextFormat("Time: %.2f", gameTime),
                centerX - MeasureText(TextFormat("Time: %.2f", gameTime), infoFont) / 2,
                panelY + 200,
                infoFont,
                WHITE);

            EndDrawing();
        }
        break;

        // Pause screen when starting the screen or pressing P
        case PAUSED:
            if (IsKeyPressed(KEY_P))
            {
                gamestate = PLAYING;
            }
            
            BeginDrawing();
            ClearBackground({ 10, 10, 10, 255 });

            // Menu background panel
            int panelWidth = 800;
            int panelHeight = 600;
            int panelX = (1280 - panelWidth) / 2;
            int panelY = (1024 - panelHeight) / 2;

            DrawRectangle(panelX, panelY, panelWidth, panelHeight, Fade(BLACK, 0.5f));
            DrawRectangleLines(panelX, panelY, panelWidth, panelHeight, WHITE);

            // Text content
            const int titleFont = 80;
            const int optionFont = 40;

            int centerX = 1280 / 2;

            DrawText("Game Paused",
                centerX - MeasureText("Game Paused", titleFont) / 2,
                panelY + 40,
                titleFont,
                WHITE);

            DrawText("Press P to play",
                centerX - MeasureText("Press P to play", optionFont) / 2,
                panelY + 160,
                optionFont,
                WHITE);

            DrawText("Press C to auto fire",
                centerX - MeasureText("Press C to auto fire", optionFont) / 2,
                panelY + 220,
                optionFont,
                WHITE);

            DrawText("Shoot enemies to store colors.",
                centerX - MeasureText("Shoot enemies to store colors.", optionFont) / 2,
                panelY + 300,
                optionFont,
                WHITE);

            DrawText("Press E to consume colors.",
                centerX - MeasureText("Press E to consume colors.", optionFont) / 2,
                panelY + 360,
                optionFont,
                WHITE);

            DrawText("Effects depend on consumed colors.",
                centerX - MeasureText("Effects depend on consumed colors.", optionFont) / 2,
                panelY + 420,
                optionFont,
                WHITE);

            // Game time
            DrawText(TextFormat("Game Time: %.2f", gameTime),
                centerX - MeasureText(TextFormat("Game Time: %.2f", gameTime), optionFont) / 2,
                panelY + 500,
                optionFont,
                WHITE);

            EndDrawing();
        }
    }

    UnloadSound(shootSound);
    UnloadSound(enemyDeathSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
