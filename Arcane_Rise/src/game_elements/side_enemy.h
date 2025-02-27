#pragma once
#pragma once
#ifndef SIDE_ENEMY_H
#define SIDE_ENEMY_H

#include "raylib.h"
#include "player.h"

namespace game
{
    const int MAX_SIDE_ENEMIES = 1;

    struct SideEnemy
    {
        Rectangle rect;
        float speedX;
        bool active;
        int direction;
    };

    void InitSideEnemies(SideEnemy sideEnemies[], int count, int screenWidth, int screenHeight, const Player& player);
    void UpdateSideEnemies(SideEnemy sideEnemies[], int count, float deltaTime);
    void DrawSideEnemies(const SideEnemy sideEnemies[], int count);
    void ResetSideEnemy(SideEnemy& enemy, int screenWidth, int screenHeight, const Player& player);
}
#endif