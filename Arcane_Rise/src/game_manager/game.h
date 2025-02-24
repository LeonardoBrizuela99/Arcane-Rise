#ifndef GAME_H
#define GAME_H
#include "game_elements/player.h"
#include "game_elements/obstacles.h"
#include"game_elements/enemies.h"
#include"game_elements/powerup.h"

namespace game 
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    const float playerSpeed = 200.0f;
    void RunGame();
}
#endif 