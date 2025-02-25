#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

namespace game
{

    struct Player
    {
        float x;
        float y;
        float radius;
    };

    void InitPlayer(Player& player, int screenWidth, int screenHeight);
    void UpdatePlayer(Player& player, float deltaTime, float currentPlayerSpeed);
    void DrawPlayer(const Player& player);
    void UpdateShieldPosition(const Player& player, float distance, float& shieldX, float& shieldY);
    void DrawShield(float shieldX, float shieldY, float shieldRadius);
} 
#endif