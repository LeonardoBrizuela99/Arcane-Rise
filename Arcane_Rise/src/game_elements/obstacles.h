#ifndef OBSTACLES_H
#define OBSTACLES_H

namespace game
{
    struct Obstacle
    {
        Rectangle rect;
        float speedY;
        bool active;
    };

    void InitObstacles(Obstacle obstacles[], int count, int screenWidth);
    void UpdateObstacles(Obstacle obstacles[], int count, float deltaTime);
    void DrawObstacles(const Obstacle obstacles[], int count);
    void ResetObstacle(Obstacle& obstacle, int screenWidth);
} 
#endif