#include "player.h"
#include "game_manager/game.h" 

namespace game 
{
    void UpdatePlayer(Player& player, float deltaTime)
    {
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) player.x += playerSpeed * deltaTime;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) player.x -= playerSpeed * deltaTime;
        if (player.x - player.radius < 0) player.x = player.radius; 
        if (player.x + player.radius > screenWidth) player.x = screenWidth - player.radius;
    }

    void DrawPlayer(const Player& player)
    {
        DrawCircle(static_cast<int>(player.x), static_cast<int>(player.y), player.radius, BLUE);
    } 
} 