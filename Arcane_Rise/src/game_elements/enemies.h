#ifndef ENEMIES_H
#define ENEMIES_H

#include "raylib.h"

namespace game 
{
    const int MAX_ENEMIES = 5; 

    struct Enemies 
    {
        Rectangle rect;
        float speedY;
        float speedX;
        float time;    
        bool active;
    };

    extern Enemies enemies[MAX_ENEMIES];

    void InitEnemies();
    void UpdateEnemies(float deltaTime);
    void DrawEnemies();
    void ResetEnemies(int index);
}
#endif 