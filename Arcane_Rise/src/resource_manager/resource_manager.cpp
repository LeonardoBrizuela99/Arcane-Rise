#include "resource_manager.h"
#include "raylib.h"

namespace resource {

    Texture2D backgroundTexture = { 0 };
    Texture2D instruction = {0};
    Texture2D credits = {0};
    Texture2D pause = {0};
    Texture2D options = {0};
    Texture2D gameOver = {0};

    Texture2D playerTexture1 = { 0 };
    Texture2D playerTexture2 = { 0 };
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
    Sound powerUp= { 0 };
    Sound pop= { 0 };
    Sound select= { 0 };

    Music menuSong = { 0 };
    Music gameSong = { 0 };
    Music pauseSong = { 0 };
    Music gameOverSong = { 0 };

    void LoadResources()
    {

        playerTexture1 = LoadTexture("../../res/textures/player1.png");
        playerTexture2 = LoadTexture("../../res/textures/player2.png");
        obstacleTexture = LoadTexture("../../res/textures/bola_de_fuego.png");
        sideEnemyTexture1 = LoadTexture("../../res/textures/skeleton_1.png");
        sideEnemyTexture2 = LoadTexture("../../res/textures/skeleton_2.png");
        enemyTexture = LoadTexture("../../res/textures/enemy.png");
        powerUpShieldTexture = LoadTexture("../../res/textures/escudo_power.png");
        powerUpSpeedTexture = LoadTexture("../../res/textures/speed.png");

        backgroundTexture = LoadTexture("../../res/textures/main_menu.png");
        shieldTexture = LoadTexture("../../res/textures/escudo.png");
        gameBackgroundTexture = LoadTexture("../../res/textures/game_background.png");
        instruction = LoadTexture("../../res/textures/instructions.png");
        credits = LoadTexture("../../res/textures/credits.png");
        gameOver = LoadTexture("../../res/textures/gameOver.png");
        options = LoadTexture("../../res/textures/options.png");
        

        pause = LoadTexture("../../res/textures/pause_text.png");


        InitAudioDevice();


        shieldSound = LoadSound("resources/shield.wav");
        powerUp = LoadSound("../../res/sounds/power_up.wav");

        select = LoadSound("../../res/sounds/select.wav");
        pop = LoadSound("../../res/sounds/pop.wav");

        menuSong = LoadMusicStream("../../res/sounds/menuSong.wav");
        gameSong = LoadMusicStream("../../res/sounds/gameSong.wav");
        pauseSong = LoadMusicStream("../../res/sounds/pauseSong.wav");
        gameOverSong = LoadMusicStream("../../res/sounds/gameOverSong.wav");
   


    }

    void UnloadResources()
    {

        UnloadTexture(playerTexture1);
        UnloadTexture(playerTexture2);
        UnloadTexture(obstacleTexture);
        UnloadTexture(enemyTexture);        
        UnloadTexture(sideEnemyTexture1);
        UnloadTexture(sideEnemyTexture2);       
        UnloadTexture(backgroundTexture);
        UnloadTexture(shieldTexture);
        UnloadTexture(gameBackgroundTexture);
        UnloadTexture(powerUpSpeedTexture);
        UnloadTexture(powerUpShieldTexture);
        UnloadTexture(pause);
        UnloadTexture(instruction);
        UnloadTexture(credits);
        UnloadTexture(pause);
        UnloadTexture(gameOver);
        UnloadTexture(options);

        UnloadSound(pop);
        UnloadSound(powerUp);       
        UnloadSound(select);

        UnloadMusicStream(menuSong);
        UnloadMusicStream(gameSong);
        UnloadMusicStream(pauseSong);
        UnloadMusicStream(gameOverSong);

        CloseAudioDevice();
    }
}