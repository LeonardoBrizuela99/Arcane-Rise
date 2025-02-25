#ifndef POWERUP_H
#define POWERUP_H

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

    void InitPowerUp(PowerUp& powerUp, int screenWidth);
    void UpdatePowerUp(PowerUp& powerUp, float deltaTime);
    void DrawPowerUp(const PowerUp& powerUp);
    void ResetPowerUp(PowerUp& powerUp, int screenWidth);
} 
#endif