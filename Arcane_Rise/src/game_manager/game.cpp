#include "game.h"
#include "raylib.h"

namespace game
{  
    static float GetSpawnInterval(int score)
    {
        if (score < 500) return 1.0f;
        else if (score < 1000) return 0.75f;
        else if (score < 1500) return 0.5f;
        else return 0.25f;
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
        state.localGameScore = 0;
        state.spawnTimer = 0.0f;
        
        InitPlayer(state.player, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
        
        state.shieldDistance = 60.0f;
        state.shieldRadius = shieldInitRadius;
        state.shieldX = 0.0f;
        state.shieldY = 0.0f;
       
        state.basePlayerSpeed = basePlayerSpeedConst;
        state.currentPlayerSpeed = basePlayerSpeedConst;
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
                state.shieldRadius = shieldPowerupRadius;
            else
                state.shieldRadius = shieldNoPowerupRadius;
        }
       
        if (state.speedPowerTimer > 0.0f)
        {
            state.speedPowerTimer -= deltaTime;
            if (state.speedPowerTimer > 0.0f)
                state.currentPlayerSpeed = state.basePlayerSpeed * 1.25f;
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
                    state.localGameScore += 20;
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
                    state.localGameScore += 50;
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
                state.localGameScore += 100;
            }
        }
    }

    void RenderFrame(const GameState& state)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!state.gameOver)
        {
            DrawPlayer(state.player);
            DrawShield(state.shieldX, state.shieldY, state.shieldRadius);
            DrawObstacles(state.obstacles, MAX_OBSTACLES);
            DrawEnemies(state.enemies, MAX_ENEMIES);
            DrawPowerUp(state.powerUp);
            DrawText(TextFormat("Score: %d", state.localGameScore), 10, 10, 20, BLACK);
        }
        else
        {
            DrawText("GAME OVER", GAME_SCREEN_WIDTH / 2 - 50, GAME_SCREEN_HEIGHT / 2, 30, RED);
            DrawText("Press R to Restart", GAME_SCREEN_WIDTH / 2 - 70, GAME_SCREEN_HEIGHT / 2 + 40, 20, DARKGRAY);
        }
        EndDrawing();
    }

    void RunGame()
    {
        GameState state;
        InitWindow(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, "Arcane Rise");
        SetTargetFPS(60);
        InitGame(state);

        while (!WindowShouldClose())
        {
            float deltaTime = GetFrameTime();

            if (!state.gameOver)
            {
                UpdateGame(state, deltaTime);
                ProcessCollisions(state);
            }
            else if (IsKeyPressed(KEY_R))
            {
                InitGame(state);
            }
            RenderFrame(state);
        }
        CloseWindow();
    }
} 