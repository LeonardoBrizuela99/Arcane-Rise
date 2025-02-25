#include "game_manager/game.h"  
#include "enemies.h"
#include "raylib.h"
#include <cstdlib>
#include <cmath>

namespace game
{
    void InitEnemies(Enemies enemies[], int count, int screenWidth)
    {
        for (int i = 0; i < count; i++)
        {
            enemies[i].rect.x = static_cast<float>(rand() % (screenWidth - 20));
            enemies[i].rect.y = -20.0f;
            enemies[i].rect.width = 20.0f;
            enemies[i].rect.height = 20.0f;
            enemies[i].speedY = static_cast<float>(180 + (rand() % 120));
            enemies[i].speedX = static_cast<float>(70 + (rand() % 50));
            enemies[i].time = 0.0f;
            enemies[i].active = true;
        }
    }

    void UpdateEnemies(Enemies enemies[], int count, float deltaTime)
    {
        for (int i = 0; i < count; i++)
        {
            if (enemies[i].active)
            {
                enemies[i].time += deltaTime * 3.0f;
                enemies[i].rect.y += enemies[i].speedY * deltaTime;
                enemies[i].rect.x += enemies[i].speedX * sinf(enemies[i].time) * deltaTime;
                if (enemies[i].rect.y > GAME_SCREEN_HEIGHT)
                {
                    enemies[i].rect.y = -20.0f;
                    enemies[i].rect.x = static_cast<float>(rand() % (GAME_SCREEN_WIDTH - 20));
                    enemies[i].time = 0.0f;
                }
            }
        }
    }

    void DrawEnemies(const Enemies enemies[], int count)
    {
        for (int i = 0; i < count; i++)
        {
            if (enemies[i].active)
            {
                DrawRectangleRec(enemies[i].rect, PURPLE);
            }
        }
    }

    void ResetEnemies(Enemies& enemy, int screenWidth)
    {
        enemy.rect.y = -20.0f;
        enemy.rect.x = static_cast<float>(rand() % (screenWidth - static_cast<int>(enemy.rect.width)));
        enemy.time = 0.0f;
    }
} 