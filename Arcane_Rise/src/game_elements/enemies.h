#ifndef ENEMIES_H
#define ENEMIES_H

namespace game
{

    struct Enemies
    {
        Rectangle rect;
        float speedY;
        float speedX;
        float time;
        bool active;
    };

    void InitEnemies(Enemies enemies[], int count, int screenWidth);
    void UpdateEnemies(Enemies enemies[], int count, float deltaTime);
    void DrawEnemies(const Enemies enemies[], int count);
    void ResetEnemies(Enemies& enemy, int screenWidth);
} 
#endif