#include "powerup.h"
#include "game_manager/game.h"  
#include <cstdlib>

namespace game 
{
    PowerUp powerUp;

    void InitPowerUp() 
    {
        powerUp.rect = { static_cast<float>(rand() % (screenWidth - 20)), -20.0f, 20.0f, 20.0f };
        powerUp.speedY = static_cast<float>(100 + rand() % 50);
        powerUp.active = true;
        powerUp.type = (rand() % 2 == 0) ? PowerUpType::SHIELD : PowerUpType::SPEED;
    }

    void UpdatePowerUp(float deltaTime)
    {
        if (powerUp.active)
        {
            powerUp.rect.y += 200 * deltaTime;
            if (powerUp.rect.y > screenHeight)
            {
                InitPowerUp();               
            }
        }
    }

    void DrawPowerUp()
    {
        if (powerUp.active) 
        {
            Color color = (powerUp.type == PowerUpType::SHIELD) ? GREEN : YELLOW;
            DrawRectangleRec(powerUp.rect, color);
        }
    }

    void ResetPowerUp()
    {
        powerUp.rect.y = -20.0f;
        powerUp.rect.x = static_cast<float>(rand() % (screenWidth - static_cast<int>(powerUp.rect.width)));       
        powerUp.active = true;
        powerUp.type = (rand() % 2 == 0) ? PowerUpType::SHIELD : PowerUpType::SPEED;
    }
}