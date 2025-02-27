#include "game.h"
#include "raylib.h"
#include "screen_manager/menu.h"

namespace game
{
    static float GetSpawnInterval(int score)
    {
        const int SCORE_THRESHOLD_1 = 1500;
        const int SCORE_THRESHOLD_2 = 2000;
        const int SCORE_THRESHOLD_3 = 4500;
        const float SPAWN_INTERVAL_1 = 1.0f;
        const float SPAWN_INTERVAL_2 = 0.75f;
        const float SPAWN_INTERVAL_3 = 0.5f;
        const float SPAWN_INTERVAL_4 = 0.25f;

        if (score < SCORE_THRESHOLD_1)
            return SPAWN_INTERVAL_1;
        else if (score < SCORE_THRESHOLD_2)
            return SPAWN_INTERVAL_2;
        else if (score < SCORE_THRESHOLD_3)
            return SPAWN_INTERVAL_3;
        else
            return SPAWN_INTERVAL_4;
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

    static void InitSideEnemiesModule(GameState& state)
    {
        InitSideEnemies(state.sideEnemies, MAX_SIDE_ENEMIES, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, state.player);
    }

    void InitGame(GameState& state)
    {
        state.gameOver = false;
        state.currentScreen = ScreenState::MAIN_MENU;
        state.previousScreen = ScreenState::MAIN_MENU;
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
        InitSideEnemiesModule(state);

        state.activeObstacles = 3;
        state.activeEnemies = 0;
        state.activeSideEnemies = 0;

        state.lastObstacleScoreThreshold = 0;
        state.lastEnemyScoreThreshold = 500;
        state.lastPowerUpScoreThreshold = 0;
        state.lastSideEnemyScoreThreshold = 1000;


        for (int i = 0; i < MAX_SIDE_ENEMIES; i++)
        {
            state.sideEnemyRespawnTimers[i] = 0.0f;
        }


        for (int i = 0; i < MAX_OBSTACLES; i++)
        {
            state.obstacles[i].active = (i < state.activeObstacles);
        }

        for (int i = 0; i < MAX_ENEMIES; i++) {
            state.enemies[i].active = false;
        }
        state.powerUp.active = false;

        for (int i = 0; i < MAX_SIDE_ENEMIES; i++) {
            state.sideEnemies[i].active = false;
        }
    }

    void UpdateGame(GameState& state, float deltaTime)
    {
        UpdatePlayer(state.player, deltaTime, state.currentPlayerSpeed);
        UpdateShieldPosition(state.player, state.shieldDistance, state.shieldX, state.shieldY);

        UpdateObstacles(state.obstacles, MAX_OBSTACLES, deltaTime);
        UpdateEnemies(state.enemies, MAX_ENEMIES, deltaTime);
        UpdatePowerUp(state.powerUp, deltaTime);
        UpdateSideEnemies(state.sideEnemies, MAX_SIDE_ENEMIES, deltaTime);

        state.spawnTimer += deltaTime;
        if (state.spawnTimer >= GetSpawnInterval(state.localGameScore))
        {
            state.spawnTimer = 0.0f;

            if (state.localGameScore >= state.lastObstacleScoreThreshold + 100 && state.activeObstacles < MAX_OBSTACLES) {
                state.activeObstacles++;
                state.obstacles[state.activeObstacles - 1].active = true;
                float maxSpeed = 0.0f;
                for (int i = 0; i < state.activeObstacles; i++) {
                    if (state.obstacles[i].speedY > maxSpeed)
                        maxSpeed = state.obstacles[i].speedY;
                }
                float newSpeed = maxSpeed * 1.02f;
                for (int i = 0; i < state.activeObstacles; i++) {
                    state.obstacles[i].speedY = newSpeed;
                }
                state.lastObstacleScoreThreshold += 300;
            }

            if (state.activeEnemies == 0 && state.localGameScore >= 500)
            {
                state.activeEnemies = 1;
                state.enemies[0].active = true;
            }
            else if (state.localGameScore >= state.lastEnemyScoreThreshold + 100 && state.activeEnemies < MAX_ENEMIES) {
                state.activeEnemies++;
                state.enemies[state.activeEnemies - 1].active = true;
                float maxSpeed = 0.0f;
                for (int i = 0; i < state.activeEnemies; i++) {
                    if (state.enemies[i].speedY > maxSpeed)
                        maxSpeed = state.enemies[i].speedY;
                }
                float newSpeed = maxSpeed * 1.02f;
                for (int i = 0; i < state.activeEnemies; i++) {
                    state.enemies[i].speedY = newSpeed;
                }
                state.lastEnemyScoreThreshold += 500;
            }

            if (state.localGameScore >= state.lastPowerUpScoreThreshold + 300 && !state.powerUp.active) {
                state.powerUp.active = true;
                state.powerUp.speedY *= 1.02f;
                state.lastPowerUpScoreThreshold += 300;
            }
        }

        if (state.activeSideEnemies == 0 && state.localGameScore >= state.lastSideEnemyScoreThreshold) {
            state.activeSideEnemies = 1;

            if (state.sideEnemyRespawnTimers[0] <= 0.0f)
                state.sideEnemyRespawnTimers[0] = static_cast<float>(GetRandomValue(5, 10));
        }
        else if (state.localGameScore >= state.lastSideEnemyScoreThreshold + 200 && state.activeSideEnemies < MAX_SIDE_ENEMIES) {
            state.activeSideEnemies++;
            state.lastSideEnemyScoreThreshold += 500;
            state.sideEnemyRespawnTimers[state.activeSideEnemies - 1] = static_cast<float>(GetRandomValue(5, 10));
        }

        for (int i = 0; i < state.activeSideEnemies; i++) {
            if (!state.sideEnemies[i].active) {
                state.sideEnemyRespawnTimers[i] -= deltaTime;
                if (state.sideEnemyRespawnTimers[i] <= 0.0f) {
                    ResetSideEnemy(state.sideEnemies[i], GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, state.player);
                    state.sideEnemyRespawnTimers[i] = 0.0f;
                }
            }
        }

        if (state.shieldPowerTimer > 0.0f)
        {
            state.shieldPowerTimer -= deltaTime;
            if (state.shieldPowerTimer > 0.0f)
                state.shieldRadius = SHIELD_POWERUP_RADIUS;
            else
                state.shieldRadius = SHIELD_INIT_RADIUS;
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

        for (int i = 0; i < MAX_SIDE_ENEMIES; i++)
        {
            if (state.sideEnemies[i].active)
            {
                if (CheckCollisionCircleRec(Vector2{ state.shieldX, state.shieldY },
                    state.shieldRadius, state.sideEnemies[i].rect))
                {
                    state.sideEnemies[i].active = false;
                    state.sideEnemyRespawnTimers[i] = static_cast<float>(GetRandomValue(5, 10));
                    state.localGameScore += SCORE_INCREMENT_ENEMY;
                }
                else if (CheckCollisionCircleRec(Vector2{ state.player.x, state.player.y },
                    state.player.radius, state.sideEnemies[i].rect))
                {
                    state.gameOver = true;
                    return;
                }
            }
        }
    }

    void RenderFrame(const GameState& state)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawPlayer(state.player);
        DrawShield(state.shieldX, state.shieldY, state.shieldRadius);
        DrawObstacles(state.obstacles, MAX_OBSTACLES);
        DrawEnemies(state.enemies, MAX_ENEMIES);
        DrawPowerUp(state.powerUp);
        DrawSideEnemies(state.sideEnemies, MAX_SIDE_ENEMIES);
        DrawText(TextFormat("Score: %d", state.localGameScore), 10, 10, 20, BLACK);

        if (state.gameOver)
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
        SetExitKey(0);
        SetTargetFPS(TARGET_FPS);
        InitGame(state);

        while (!WindowShouldClose())
        {
            float deltaTime = GetFrameTime();

            if (state.currentScreen == ScreenState::EXIT)
                break;

            switch (state.currentScreen)
            {
            case ScreenState::MAIN_MENU:
                menu::UpdateMainMenu(state);
                menu::RenderMainMenu(state);
                break;

            case ScreenState::GAMEPLAY:

                if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_ESCAPE))
                {
                    state.previousScreen = ScreenState::GAMEPLAY;
                    state.currentScreen = ScreenState::PAUSE_MENU;
                }

                if (!state.gameOver)
                {
                    UpdateGame(state, deltaTime);
                    ProcessCollisions(state);
                }
                else if (IsKeyPressed(KEY_R))
                {
                    InitGame(state);
                    state.currentScreen = ScreenState::GAMEPLAY;
                }
                RenderFrame(state);
                break;

            case ScreenState::PAUSE_MENU:
                menu::UpdatePauseMenu(state);
                menu::RenderPauseMenu(state);
                break;

            case ScreenState::OPTIONS:
                menu::UpdateSubMenu(state);
                menu::RenderSubMenu(state, "OPTIONS", "null.");
                break;

            case ScreenState::INSTRUCTIONS:
                menu::UpdateSubMenu(state);
                menu::RenderSubMenu(state, "INSTRUCTIONS", "Use the arrows and A/S to move,\nuse the mouse to select and use ESC to go back.\nP: Pause/Resume");
                break;

            case ScreenState::CREDITS:
                menu::UpdateSubMenu(state);
                menu::RenderSubMenu(state, "CREDITS", "Developed by: Leonardo Brizuela. \n Game version: v0.2");
                break;

            default:
                break;
            }
        }
        CloseWindow();
    }
}