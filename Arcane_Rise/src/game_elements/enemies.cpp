#include "enemies.h"
#include "game_manager/game.h"  
#include <cstdlib>
#include <cmath>

namespace game 
{
    Enemies enemies[MAX_ENEMIES];

    void InitEnemies() 
    {
        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            enemies[i].rect = { static_cast<float>(rand() % (screenWidth - 20)), -20.0f, 20.0f, 20.0f };
            enemies[i].speedY = static_cast<float>(180 + rand() % 120);
            enemies[i].speedX = static_cast<float>(70 + rand() % 50);
            enemies[i].time = 0.0f;
            enemies[i].active = true;
        }
    }

    void UpdateEnemies(float deltaTime)
    {
        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            if (enemies[i].active) 
            {
                enemies[i].time += deltaTime * 3.0f;
                enemies[i].rect.y += enemies[i].speedY * deltaTime;
                enemies[i].rect.x += enemies[i].speedX * sinf(enemies[i].time) * deltaTime;

                if (enemies[i].rect.y > screenHeight)
                {
                    enemies[i].rect.y = -20.0f;
                    enemies[i].rect.x = static_cast<float>(rand() % (screenWidth - 20));
                    enemies[i].time = 0.0f;
                }
            }
        }
    }

    void DrawEnemies()
    {
        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            if (enemies[i].active)
            {
                DrawRectangleRec(enemies[i].rect, PURPLE);
            }
        }
    }
}