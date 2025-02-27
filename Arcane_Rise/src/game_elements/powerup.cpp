#include "game_manager/game.h"  
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
            Color color = (powerUp.type == PowerUpType::SHIELD) ? GREEN : YELLOW;
            DrawRectangleRec(powerUp.rect, color);
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
