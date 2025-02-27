#include "game_manager/game.h"  
#include "enemies.h"
#include "raylib.h"
#include <cstdlib>
#include <cmath>

namespace game
{
    void InitEnemies(Enemies enemies[], int count, int screenWidth)
    {
        const int ENEMY_SIZE = 20;
        const float ENEMY_INITIAL_Y = -20.0f;
        const int ENEMY_SPEED_Y_MIN = 180;
        const int ENEMY_SPEED_Y_RANGE = 120;
        const int ENEMY_SPEED_X_MIN = 70;
        const int ENEMY_SPEED_X_RANGE = 50;
        for (int i = 0; i < count; i++)
        {
            enemies[i].rect.x = static_cast<float>(rand() % (screenWidth - ENEMY_SIZE));
            enemies[i].rect.y = ENEMY_INITIAL_Y;
            enemies[i].rect.width = ENEMY_SIZE;
            enemies[i].rect.height = ENEMY_SIZE;
            enemies[i].speedY = static_cast<float>(ENEMY_SPEED_Y_MIN + (rand() % ENEMY_SPEED_Y_RANGE));
            enemies[i].speedX = static_cast<float>(ENEMY_SPEED_X_MIN + (rand() % ENEMY_SPEED_X_RANGE));
            enemies[i].time = 0.0f;
            enemies[i].active = (i == 0) ? true : false;
        }
    }

    void UpdateEnemies(Enemies enemies[], int count, float deltaTime)
    {
        const int ENEMY_SIZE = 20;
        const float ENEMY_INITIAL_Y = -20.0f;
        const float ENEMY_TIME_MULTIPLIER = 3.0f;
        for (int i = 0; i < count; i++)
        {
            if (enemies[i].active)
            {
                enemies[i].time += deltaTime * ENEMY_TIME_MULTIPLIER;
                enemies[i].rect.y += enemies[i].speedY * deltaTime;
                enemies[i].rect.x += enemies[i].speedX * sinf(enemies[i].time) * deltaTime;
                if (enemies[i].rect.y > GAME_SCREEN_HEIGHT)
                {
                    enemies[i].rect.y = ENEMY_INITIAL_Y;
                    enemies[i].rect.x = static_cast<float>(rand() % (GAME_SCREEN_WIDTH - ENEMY_SIZE));
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
        const float ENEMY_INITIAL_Y = -20.0f;
        enemy.rect.y = ENEMY_INITIAL_Y;
        enemy.rect.x = static_cast<float>(rand() % (screenWidth - static_cast<int>(enemy.rect.width)));
        enemy.time = 0.0f;
    }
}
