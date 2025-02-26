﻿//#ifndef GAME_H
#define GAME_H

#include "game_elements/player.h"
#include "game_elements/powerup.h"
#include "game_elements/obstacles.h"
#include "game_elements/enemies.h"

namespace game
{

    const int GAME_SCREEN_WIDTH = 800;
    const int GAME_SCREEN_HEIGHT = 600;


    const float EFFECT_DURATION = 5.0f;


    const float SHIELD_INIT_RADIUS = 20.0f;
    const float SHIELD_NO_POWERUP_RADIUS = 30.0f;
    const float SHIELD_POWERUP_RADIUS = 40.0f;
    const float SHIELD_DISTANCE = 60.0f;


    const float BASE_PLAYER_SPEED = 300.0f;

    const float SPEED_POWER_MULTIPLIER = 1.25f;


    const int MAX_OBSTACLES = 10;
    const int MAX_ENEMIES = 5;


    const int SCORE_INCREMENT_OBSTACLE = 20;
    const int SCORE_INCREMENT_ENEMY = 50;
    const int SCORE_INCREMENT_POWERUP = 100;


    const int TARGET_FPS = 60;

    struct GameState
    {
        Player player;

        float shieldX;
        float shieldY;
        float shieldRadius;
        float shieldDistance;

        int localGameScore;
        float spawnTimer;
        bool gameOver;

        float basePlayerSpeed;
        float currentPlayerSpeed;
        float shieldPowerTimer;
        float speedPowerTimer;

        PowerUp powerUp;

        Obstacle obstacles[MAX_OBSTACLES];
        Enemies enemies[MAX_ENEMIES];
    };

    void InitGame(GameState& state);
    void UpdateGame(GameState& state, float deltaTime);
    void ProcessCollisions(GameState& state);
    void RenderFrame(const GameState& state);
    void RunGame();
}