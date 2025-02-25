#include "player.h"
#include "game_manager/game.h" 
#include "math.h"

namespace game 
{
    void UpdatePlayer(Player& player, float deltaTime)
    {
       
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
            player.x += currentPlayerSpeed * deltaTime;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
            player.x -= currentPlayerSpeed * deltaTime;

        if (player.x - player.radius < 0) player.x = player.radius; 
        if (player.x + player.radius > screenWidth) player.x = screenWidth - player.radius;
    }

    void DrawPlayer(const Player& player)
    {
        DrawCircle(static_cast<int>(player.x), static_cast<int>(player.y), player.radius, BLUE);
    } 

    void UpdateShieldPosition(const Player& player, float distance, float& shieldX, float& shieldY) 
    {
        float mouseX = static_cast<float>(GetMouseX());
        float mouseY = static_cast<float>(GetMouseY());
        float angle = static_cast<float>(atan2(mouseY - player.y, mouseX - player.x));

        if (angle < -PI) angle = -PI;
        if (angle > 0) angle = 0;

        shieldX = player.x + distance * static_cast<float>(cos(angle));
        shieldY = player.y + distance * static_cast<float>(sin(angle));
    }

    void DrawShield(float shieldX, float shieldY, float shieldRadius) 
    {
        DrawCircle(static_cast<int>(shieldX), static_cast<int>(shieldY), shieldRadius, DARKBLUE);
    }
} 