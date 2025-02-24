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
    }

    void UpdatePowerUp(float deltaTime)
    {
        if (powerUp.active)
        {
            powerUp.rect.y += powerUp.speedY * deltaTime;
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
            DrawRectangleRec(powerUp.rect, GREEN);
        }
    }
}