#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"

namespace game 
{
    struct Player 
    {
        float x, y;
        float radius;
    };

    void UpdatePlayer(Player& player, float deltaTime);
    void DrawPlayer(const Player& player);
} 
#endif