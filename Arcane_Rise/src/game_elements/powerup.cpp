#include "game_manager/game.h"  
#include "powerup.h"
#include <cstdlib>

namespace game 
{
    void InitPowerUp(PowerUp& powerUp, int screenWidth)
    {
        powerUp.rect.x = static_cast<float>(rand() % (screenWidth - 20));
        powerUp.rect.y = -20.0f;
        powerUp.rect.width = 20.0f;
        powerUp.rect.height = 20.0f;
        powerUp.speedY = static_cast<float>(100 + (rand() % 50));
        powerUp.active = true;
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
            Color color = (powerUp.type == PowerUpType::SHIELD) ? GREEN : YELLOW;
            DrawRectangleRec(powerUp.rect, color);
        }
    }

    void ResetPowerUp(PowerUp& powerUp, int screenWidth)
    {
        powerUp.rect.y = -20.0f;
        powerUp.rect.x = static_cast<float>(rand() % (screenWidth - static_cast<int>(powerUp.rect.width)));
        powerUp.active = true;
        powerUp.type = (rand() % 2 == 0) ? PowerUpType::SHIELD : PowerUpType::SPEED;
    }
} 