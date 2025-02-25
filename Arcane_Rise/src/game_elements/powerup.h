#ifndef POWERUP_H
#define POWERUP_H

#include "raylib.h"

namespace game
{ 
    enum class PowerUpType
    {
        SHIELD,  
        SPEED    
    };

    struct PowerUp
    {
        Rectangle rect;
        float speedY;
        bool active;
        PowerUpType type;
    };

    extern PowerUp powerUp;
    
    void InitPowerUp();
    void UpdatePowerUp(float deltaTime);
    void DrawPowerUp();
    void ResetPowerUp();
}
#endif 