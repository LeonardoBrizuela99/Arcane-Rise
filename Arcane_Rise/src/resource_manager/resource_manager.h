#pragma once
#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "raylib.h"

namespace resource
{


    extern Texture2D backgroundTexture;
    extern Texture2D playerTexture1;
    extern Texture2D playerTexture2;
    extern Texture2D obstacleTexture;
    extern Texture2D enemyTexture;
    extern Texture2D sideEnemyTexture1;
    extern Texture2D sideEnemyTexture2;   
    extern Texture2D shieldTexture;
    extern Texture2D gameBackgroundTexture;
    extern Texture2D powerUpSpeedTexture;
    extern Texture2D powerUpShieldTexture;

    extern Sound shieldSound;
    extern Sound explosionSound;
   
    extern Sound select;
    extern Sound pop;
    extern Sound powerUp;


    void LoadResources();
    void UnloadResources();
}

#endif
