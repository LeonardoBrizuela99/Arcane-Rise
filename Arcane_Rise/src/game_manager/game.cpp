﻿#include "game.h"
#include "raylib.h"

namespace game
{
    static float GetSpawnInterval(int score)
    {

        const int SCORE_THRESHOLD_1 = 500;
        const int SCORE_THRESHOLD_2 = 1000;
        const int SCORE_THRESHOLD_3 = 1500;
        const float SPAWN_INTERVAL_1 = 1.0f;
        const float SPAWN_INTERVAL_2 = 0.75f;
        const float SPAWN_INTERVAL_3 = 0.5f;
        const float SPAWN_INTERVAL_4 = 0.25f;

        if (score < SCORE_THRESHOLD_1) return SPAWN_INTERVAL_1;
        else if (score < SCORE_THRESHOLD_2) return SPAWN_INTERVAL_2;
        else if (score < SCORE_THRESHOLD_3) return SPAWN_INTERVAL_3;
        else return SPAWN_INTERVAL_4;
    }

    static void InitObstaclesModule(GameState& state)
    {
        InitObstacles(state.obstacles, MAX_OBSTACLES, GAME_SCREEN_WIDTH);
    }
    static void InitEnemiesModule(GameState& state)
    {
        InitEnemies(state.enemies, MAX_ENEMIES, GAME_SCREEN_WIDTH);
    }
    static void InitPowerUpModule(GameState& state)
    {
        InitPowerUp(state.powerUp, GAME_SCREEN_WIDTH);
    }

    void InitGame(GameState& state)
    {
        state.gameOver = false;
        state.paused = false;
        state.localGameScore = 0;
        state.spawnTimer = 0.0f;

        InitPlayer(state.player, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);

        state.shieldDistance = SHIELD_DISTANCE;
        state.shieldRadius = SHIELD_INIT_RADIUS;
        state.shieldX = 0.0f;
        state.shieldY = 0.0f;

        state.basePlayerSpeed = BASE_PLAYER_SPEED;
        state.currentPlayerSpeed = BASE_PLAYER_SPEED;
        state.shieldPowerTimer = 0.0f;
        state.speedPowerTimer = 0.0f;

        InitObstaclesModule(state);
        InitEnemiesModule(state);
        InitPowerUpModule(state);
    }

    void UpdateGame(GameState& state, float deltaTime)
    {
        UpdatePlayer(state.player, deltaTime, state.currentPlayerSpeed);
        UpdateShieldPosition(state.player, state.shieldDistance, state.shieldX, state.shieldY);

        UpdateObstacles(state.obstacles, MAX_OBSTACLES, deltaTime);
        UpdateEnemies(state.enemies, MAX_ENEMIES, deltaTime);
        UpdatePowerUp(state.powerUp, deltaTime);

        state.spawnTimer += deltaTime;
        if (state.spawnTimer >= GetSpawnInterval(state.localGameScore))
            state.spawnTimer = 0.0f;

        if (state.shieldPowerTimer > 0.0f)
        {
            state.shieldPowerTimer -= deltaTime;
            if (state.shieldPowerTimer > 0.0f)
                state.shieldRadius = SHIELD_POWERUP_RADIUS;
            else
                state.shieldRadius = SHIELD_NO_POWERUP_RADIUS;
        }

        if (state.speedPowerTimer > 0.0f)
        {
            state.speedPowerTimer -= deltaTime;
            if (state.speedPowerTimer > 0.0f)
                state.currentPlayerSpeed = state.basePlayerSpeed * SPEED_POWER_MULTIPLIER;
            else
                state.currentPlayerSpeed = state.basePlayerSpeed;
        }
    }

    void ProcessCollisions(GameState& state)
    {
        for (int i = 0; i < MAX_OBSTACLES; i++)
        {
            if (state.obstacles[i].active)
            {
                if (CheckCollisionCircleRec(Vector2{ state.shieldX, state.shieldY },
                    state.shieldRadius, state.obstacles[i].rect))
                {
                    ResetObstacle(state.obstacles[i], GAME_SCREEN_WIDTH);
                    state.localGameScore += SCORE_INCREMENT_OBSTACLE;
                }
                else if (CheckCollisionCircleRec(Vector2{ state.player.x, state.player.y },
                    state.player.radius, state.obstacles[i].rect))
                {
                    state.gameOver = true;
                    return;
                }
            }
        }

        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            if (state.enemies[i].active)
            {
                if (CheckCollisionCircleRec(Vector2{ state.shieldX, state.shieldY },
                    state.shieldRadius, state.enemies[i].rect))
                {
                    ResetEnemies(state.enemies[i], GAME_SCREEN_WIDTH);
                    state.localGameScore += SCORE_INCREMENT_ENEMY;
                }
                else if (CheckCollisionCircleRec(Vector2{ state.player.x, state.player.y },
                    state.player.radius, state.enemies[i].rect))
                {
                    state.gameOver = true;
                    return;
                }
            }
        }

        if (state.powerUp.active)
        {
            if (CheckCollisionCircleRec(Vector2{ state.player.x, state.player.y },
                state.player.radius, state.powerUp.rect) ||
                CheckCollisionCircleRec(Vector2{ state.shieldX, state.shieldY },
                    state.shieldRadius, state.powerUp.rect))
            {
                switch (state.powerUp.type)
                {
                case PowerUpType::SHIELD:
                    state.shieldPowerTimer = EFFECT_DURATION;
                    break;
                case PowerUpType::SPEED:
                    state.speedPowerTimer = EFFECT_DURATION;
                    break;
                default:
                    break;
                }
                ResetPowerUp(state.powerUp, GAME_SCREEN_WIDTH);
                state.localGameScore += SCORE_INCREMENT_POWERUP;
            }
        }
    }

    void RenderFrame(const GameState& state)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        const int SCORE_TEXT_POS_X = 10;
        const int SCORE_TEXT_POS_Y = 10;
        const int SCORE_TEXT_FONT_SIZE = 20;
        const int GAME_OVER_FONT_SIZE = 30;
        const int GAME_OVER_OFFSET_X = 50;
        const int RESTART_OFFSET_X = 70;
        const int RESTART_OFFSET_Y = 40;

        if (!state.gameOver)
        {
            DrawPlayer(state.player);
            DrawShield(state.shieldX, state.shieldY, state.shieldRadius);
            DrawObstacles(state.obstacles, MAX_OBSTACLES);
            DrawEnemies(state.enemies, MAX_ENEMIES);
            DrawPowerUp(state.powerUp);
            DrawText(TextFormat("Score: %d", state.localGameScore),
                SCORE_TEXT_POS_X, SCORE_TEXT_POS_Y, SCORE_TEXT_FONT_SIZE, BLACK);
            if (state.paused)
            {
                DrawText("PAUSED", GAME_SCREEN_WIDTH / 2 - 50, GAME_SCREEN_HEIGHT / 2,
                    GAME_OVER_FONT_SIZE, DARKGRAY);
            }
        }
        else
        {
            DrawText("GAME OVER", GAME_SCREEN_WIDTH / 2 - GAME_OVER_OFFSET_X,
                GAME_SCREEN_HEIGHT / 2, GAME_OVER_FONT_SIZE, RED);
            DrawText("Press R to Restart", GAME_SCREEN_WIDTH / 2 - RESTART_OFFSET_X,
                GAME_SCREEN_HEIGHT / 2 + RESTART_OFFSET_Y, SCORE_TEXT_FONT_SIZE, DARKGRAY);
        }
        EndDrawing();
    }

    void RunGame()
    {
        GameState state;
        InitWindow(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, "Arcane Rise");
        SetExitKey(0);
        SetTargetFPS(TARGET_FPS);
        InitGame(state);

        while (!WindowShouldClose())
        {
            float deltaTime = GetFrameTime();

          
            if (IsKeyPressed(KEY_P)||IsKeyPressed(KEY_ESCAPE))
            {
                state.paused = !state.paused;
            }

            if (!state.gameOver && !state.paused)
            {
                UpdateGame(state, deltaTime);
                ProcessCollisions(state);
            }
            else if (state.gameOver && IsKeyPressed(KEY_R))
            {
                InitGame(state);
            }
            RenderFrame(state);
        }
        CloseWindow();
    }
}