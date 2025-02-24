#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <raylib.h>
#include <cstdlib>

namespace game {

    const int MAX_OBSTACLES = 10;

    struct Obstacle {
        Rectangle rect;
        float speedY;
        bool active;
    };

    extern Obstacle obstacles[MAX_OBSTACLES];

    void InitObstacles();
    void UpdateObstacles(float deltaTime);
    void DrawObstacles();

} // namespace game

#endif // OBSTACLES_H
