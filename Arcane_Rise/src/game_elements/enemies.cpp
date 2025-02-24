#include "enemies.h"
#include <cstdlib>

Enemies enemies[MAX_ENEMIES];

void InitEnemies() 
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        enemies[i].rect = { static_cast<float>(rand() % 1280), -30.0f, 30.0f, 30.0f };
        enemies[i].speed = 200.0f;
        enemies[i].active = true;
    }
}

void UpdateEnemies(float deltaTime)
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (enemies[i].active)
        {
            enemies[i].rect.y += enemies[i].speed * deltaTime;

            if (enemies[i].rect.y > 720)
            {            
                enemies[i].rect.y = -30.0f;
                enemies[i].rect.x = static_cast<float>(rand() % 1280);
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