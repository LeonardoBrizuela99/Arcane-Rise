#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"

namespace game 
{
    extern float currentPlayerSpeed;

    struct Player 
    {
        float x, y;
        float radius;
    };

    void UpdatePlayer(Player& player, float deltaTime);
    void DrawPlayer(const Player& player);
    void UpdateShieldPosition(const Player& player, float distance, float& shieldX, float& shieldY);
    void DrawShield(float shieldX, float shieldY, float shieldRadius);
} 
#endif