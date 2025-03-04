#include "game_manager/game.h"  
#include "resource_manager/resource_manager.h"
#include "powerup.h"
#include <cstdlib>

namespace game
{
    const int POWERUP_SIZE = 20;

    void InitPowerUp(PowerUp& powerUp, int screenWidth)
    {
        powerUp.rect.x = static_cast<float>(rand() % (screenWidth - POWERUP_SIZE));
        powerUp.rect.y = -POWERUP_SIZE;
        powerUp.rect.width = POWERUP_SIZE;
        powerUp.rect.height = POWERUP_SIZE;
        powerUp.speedY = static_cast<float>(100 + (rand() % 50));
        powerUp.active = false;
        powerUp.type = (rand() % 2 == 0) ? PowerUpType::SHIELD : PowerUpType::SPEED;
    }

    void UpdatePowerUp(PowerUp& powerUp, float deltaTime)
    {
        if (powerUp.active)
        {
            powerUp.rect.y += 200.0f * deltaTime;
            if (powerUp.rect.y > GAME_SCREEN_HEIGHT)
            {
                ResetPowerUp(powerUp, GAME_SCREEN_WIDTH);
            }
        }
    }
    void DrawPowerUp(const PowerUp& powerUp)
    {
        if (powerUp.active)
        {
          
            Texture2D tex;
            float scale = 1.0f;  

            if (powerUp.type == PowerUpType::SHIELD)
            {
                tex = resource::powerUpShieldTexture;
                scale = 2.0f; 
            }
            else
            {
                tex = resource::powerUpSpeedTexture;
                scale = 2.5f;  
            }

            Rectangle source = { 0, 0, static_cast<float>(tex.width), static_cast<float>(tex.height) };
            
            float newWidth = powerUp.rect.width * scale;
            float newHeight = powerUp.rect.height * scale;

            
            Rectangle dest = 
            {
                powerUp.rect.x + (powerUp.rect.width - newWidth) / 2,
                powerUp.rect.y + (powerUp.rect.height - newHeight) / 2,
                newWidth,
                newHeight
            };

            
            DrawTexturePro(tex, source, dest, { 0, 0 }, 0.0f, WHITE);

            
          /*  DrawRectangleLines(
                static_cast<int>(powerUp.rect.x),
                static_cast<int>(powerUp.rect.y),
                static_cast<int>(powerUp.rect.width),
                static_cast<int>(powerUp.rect.height),
                RED
            );*/
        }
    }

    void ResetPowerUp(PowerUp& powerUp, int screenWidth)
    {
        powerUp.rect.y = -20.0f;
        powerUp.rect.x = static_cast<float>(rand() % (screenWidth - static_cast<int>(powerUp.rect.width)));
        powerUp.active = false;
        powerUp.type = (rand() % 2 == 0) ? PowerUpType::SHIELD : PowerUpType::SPEED;
    }
}
