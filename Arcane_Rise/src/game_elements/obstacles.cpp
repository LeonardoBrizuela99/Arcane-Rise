#include "game_manager/game.h" 
#include "obstacles.h"
#include "raylib.h"
#include <cstdlib>

namespace game
{
    const int OBSTACLE_SIZE = 30;

    void InitObstacles(Obstacle obstacles[], int count, int screenWidth)
    {
        for (int i = 0; i < count; i++)
        {
            obstacles[i].rect.x = static_cast<float>(rand() % (screenWidth - OBSTACLE_SIZE));
            obstacles[i].rect.y = -OBSTACLE_SIZE;
            obstacles[i].rect.width = OBSTACLE_SIZE;
            obstacles[i].rect.height = OBSTACLE_SIZE;
            obstacles[i].speedY = static_cast<float>(150 + (rand() % 150));
            obstacles[i].active = (i == 0) ? true : false;
        }
    }

    void UpdateObstacles(Obstacle obstacles[], int count, float deltaTime)
    {
        for (int i = 0; i < count; i++)
        {
            if (obstacles[i].active)
            {
                obstacles[i].rect.y += obstacles[i].speedY * deltaTime;
                if (obstacles[i].rect.y > 720)
                {
                    obstacles[i].rect.y = -OBSTACLE_SIZE;
                    obstacles[i].rect.x = static_cast<float>(rand() % (GAME_SCREEN_WIDTH - OBSTACLE_SIZE));
                }
            }
        }
    }

    void DrawObstacles(const Obstacle obstacles[], int count)
    {
        for (int i = 0; i < count; i++)
        {
            if (obstacles[i].active)
            {
                DrawRectangleRec(obstacles[i].rect, RED);
            }
        }
    }

    void ResetObstacle(Obstacle& obstacle, int screenWidth)
    {
        obstacle.rect.y = -30.0f;
        obstacle.rect.x = static_cast<float>(rand() % (screenWidth - static_cast<int>(obstacle.rect.width)));
    }
}