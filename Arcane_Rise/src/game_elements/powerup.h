#ifndef POWERUP_H
#define POWERUP_H

#include "raylib.h"

namespace game
{ 
    struct PowerUp
    {
        Rectangle rect;
        float speedY;
        bool active;
    };

    extern PowerUp powerUp;
    
    void InitPowerUp();
    void UpdatePowerUp(float deltaTime);
    void DrawPowerUp();
}
#endif 