#include "obstacles.h"
#include <raylib.h>
#include <cstdlib>

namespace game
{
    Obstacle obstacles[MAX_OBSTACLES];

    void InitObstacles() 
    {      
        for (int i = 0; i < MAX_OBSTACLES; i++) 
        {
            obstacles[i].rect = { static_cast<float>(rand() % (1280 - 30)), -30.0f, 30.0f, 30.0f };
            obstacles[i].speedY = static_cast<float>(150 + rand() % 150);
            obstacles[i].active = true;
        }
    }

    void UpdateObstacles(float deltaTime)
    {        
        for (int i = 0; i < MAX_OBSTACLES; i++) 
        {
            if (obstacles[i].active)
            {
                obstacles[i].rect.y += obstacles[i].speedY * deltaTime;
                
                if (obstacles[i].rect.y > 720)
                {
                    obstacles[i].rect.y = -30.0f;
                    obstacles[i].rect.x = static_cast<float>(rand() % (1280 - 30));
                }
            }
        }
    }

    void DrawObstacles()
    {
        
        for (int i = 0; i < MAX_OBSTACLES; i++)
        {
            if (obstacles[i].active)
            {
                DrawRectangleRec(obstacles[i].rect, RED);
            }
        }
    }

    void ResetObstacle(int index)
    {
        obstacles[index].rect.y = -30.0f;
        obstacles[index].rect.x = static_cast<float>(rand() % (screenWidth - static_cast<int>(obstacles[index].rect.width)));
    }
} 
