#include "resource_manager.h"
#include "raylib.h"

namespace resource {

    Texture2D backgroundTexture = { 0 };

    Texture2D playerTexture = { 0 };
    Texture2D obstacleTexture = { 0 };
    Texture2D enemyTexture = { 0 };
  
    Texture2D sideEnemyTexture1 = { 0 };
    Texture2D sideEnemyTexture2 = { 0 };
    
    Texture2D shieldTexture = { 0 };
    Texture2D gameBackgroundTexture={0};
    Texture2D powerUpShieldTexture = { 0 };
    Texture2D powerUpSpeedTexture = { 0 };
    


    Sound shieldSound = { 0 };
    Sound explosionSound = { 0 };
    Sound powerUpSound = { 0 };

    void LoadResources() {

        playerTexture = LoadTexture("../../res/textures/player.png");
        obstacleTexture = LoadTexture("../../res/textures/bola_de_fuego.png");
        sideEnemyTexture1 = LoadTexture("../../res/textures/skeleton_1.png");        
        sideEnemyTexture2 = LoadTexture("../../res/textures/skeleton_2.png");        
        enemyTexture = LoadTexture("resources/enemy.png");
        powerUpShieldTexture = LoadTexture("../../res/textures/escudo_power.png");
        powerUpSpeedTexture = LoadTexture("../../res/textures/speed.png");
       
        backgroundTexture = LoadTexture("../../res/textures/main_menu.png");
        shieldTexture = LoadTexture("../../res/textures/escudo.png");
        gameBackgroundTexture = LoadTexture("../../res/textures/game_background.png");


        InitAudioDevice();


        shieldSound = LoadSound("resources/shield.wav");
        explosionSound = LoadSound("resources/explosion.wav");
        powerUpSound = LoadSound("resources/powerup.wav");
    }

    void UnloadResources()
    {

        UnloadTexture(playerTexture);
        UnloadTexture(obstacleTexture);
        UnloadTexture(enemyTexture);
        
        UnloadTexture(sideEnemyTexture1);
        UnloadTexture(sideEnemyTexture2);
       
        UnloadTexture(backgroundTexture);
        UnloadTexture(shieldTexture);
        UnloadTexture(gameBackgroundTexture);
        UnloadTexture(powerUpSpeedTexture);
        UnloadTexture(powerUpShieldTexture);


        UnloadSound(shieldSound);
        UnloadSound(explosionSound);
        UnloadSound(powerUpSound);

        CloseAudioDevice();
    }
}