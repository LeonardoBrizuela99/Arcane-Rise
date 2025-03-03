#pragma once
#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "raylib.h"

namespace resource
{


    extern Texture2D backgroundTexture;
    extern Texture2D playerTexture;
    extern Texture2D obstacleTexture;
    extern Texture2D enemyTexture;
    extern Texture2D powerUpTexture;
    extern Texture2D sideEnemyTexture;
    extern Texture2D buttonTexture;

    extern Sound shieldSound;
    extern Sound explosionSound;
    extern Sound powerUpSound;


    void LoadResources();
    void UnloadResources();
}

#endif
