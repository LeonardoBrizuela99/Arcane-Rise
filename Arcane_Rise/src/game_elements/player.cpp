#include "resource_manager/resource_manager.h"
#include "game_manager/game.h" 
#include "player.h"
#include <math.h>

namespace game
{
    void InitPlayer(Player& player, int screenWidth, int screenHeight)
    {
        const float PLAYER_RADIUS = 20.0f;
        const float PLAYER_Y_OFFSET = 50.0f;
        player.x = static_cast<float>(screenWidth) / 2.0f;
        player.y = static_cast<float>(screenHeight) - PLAYER_Y_OFFSET;
        player.radius = PLAYER_RADIUS;
    }

    void UpdatePlayer(Player& player, float deltaTime, float currentPlayerSpeed)
    {
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
            player.x += currentPlayerSpeed * deltaTime;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
            player.x -= currentPlayerSpeed * deltaTime;

        if (player.x - player.radius < 0)
            player.x = player.radius;
        if (player.x + player.radius > GAME_SCREEN_WIDTH)
            player.x = GAME_SCREEN_WIDTH - player.radius;
    }


    void DrawPlayer(const Player& player)
    {    
        bool movingLeft = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
        bool movingRight = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
        Texture2D tex;
       
        if (movingLeft || movingRight)
        {
            float t = static_cast<float>(GetTime());
            int frame = ((int)(t * 4)) % 2;  // Alterna cada 0.25 seg
            tex = (frame == 0) ? resource::playerTexture1 : resource::playerTexture2;
        }
        else
        {           
            tex = resource::playerTexture1;
        }
       
        bool flip = movingRight; 
        Rectangle source = { 0, 0, static_cast<float>(tex.width), static_cast<float>(tex.height) };

        if (flip)
        {
            source.width = -source.width;  
        }    
        float scale = 1.7f;  
        Rectangle dest = { player.x, player.y, static_cast<float>(tex.width) * scale, static_cast<float>(tex.height) * scale };      
        Vector2 origin = { static_cast<float>(tex.width) * scale / 2.0f, static_cast<float>(tex.height) * scale / 2.0f };     
        DrawTexturePro(tex, source, dest, origin, 0.0f, WHITE);
    }

     void UpdateShieldPosition(const Player& player, float distance, float& shieldX, float& shieldY)
     {
        const float MIN_SHIELD_ANGLE = -PI;
        const float MAX_SHIELD_ANGLE = 0.0f;
        float mouseX = static_cast<float>(GetMouseX());
        float mouseY = static_cast<float>(GetMouseY());
        float angle = static_cast<float>(atan2(mouseY - player.y, mouseX - player.x));

        if (mouseX < player.x)
        {
            if (angle > 0)
                angle -= 2 * PI;
        }

        if (angle < MIN_SHIELD_ANGLE)
            angle = MIN_SHIELD_ANGLE;
        if (angle > MAX_SHIELD_ANGLE)
            angle = MAX_SHIELD_ANGLE;

        shieldX = player.x + distance * static_cast<float>(cos(angle));
        shieldY = player.y + distance * static_cast<float>(sin(angle));
     }


    void DrawShield(float shieldX, float shieldY, float shieldRadius)
    {
        Rectangle source = { 0, 0, static_cast<float>(resource::shieldTexture.width), static_cast<float>(resource::shieldTexture.height) };
        Rectangle dest = { shieldX - shieldRadius, shieldY - shieldRadius, shieldRadius * 2, shieldRadius * 2 };
        
        DrawTexturePro(resource::shieldTexture, source, dest, { 0, 0 }, 0.0f, WHITE);
        //DrawCircle(static_cast<int>(shieldX), static_cast<int>(shieldY), shieldRadius, DARKBLUE);
    }
}