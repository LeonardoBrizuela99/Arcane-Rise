#include "game.h"
#include "raylib.h"

namespace
{
    int mainMenuSelection = 0;
    const int MAIN_MENU_COUNT = 5;

    int pauseMenuSelection = 0;
    const int PAUSE_MENU_COUNT = 5;

    bool IsMouseOverRect(Rectangle rec)
    {
        Vector2 mousePos = GetMousePosition();
        return CheckCollisionPointRec(mousePos, rec);
    }


    void UpdateMainMenu(game::GameState& state)
    {
        if (IsKeyPressed(KEY_DOWN))
            mainMenuSelection = (mainMenuSelection + 1) % MAIN_MENU_COUNT;
        if (IsKeyPressed(KEY_UP))
            mainMenuSelection = (mainMenuSelection - 1 + MAIN_MENU_COUNT) % MAIN_MENU_COUNT;

        const int baseY = 200;
        const int spacing = 40;
        const int fontSize = 30;
        for (int i = 0; i < MAIN_MENU_COUNT; i++)
        {
            Rectangle itemRec = { (float)(game::GAME_SCREEN_WIDTH / 2 - 50), (float)(baseY + i * spacing), 200, (float)fontSize };
            if (IsMouseOverRect(itemRec))
            {
                mainMenuSelection = i;

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    break;
            }
        }

        if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            switch (mainMenuSelection)
            {
            case 0:
                state.currentScreen = game::ScreenState::GAMEPLAY;
                game::InitGame(state);
                state.currentScreen = game::ScreenState::GAMEPLAY;
                break;
            case 1:
                state.previousScreen = game::ScreenState::MAIN_MENU;
                state.currentScreen = game::ScreenState::OPTIONS;
                break;
            case 2:
                state.previousScreen = game::ScreenState::MAIN_MENU;
                state.currentScreen = game::ScreenState::INSTRUCTIONS;
                break;
            case 3:
                state.previousScreen = game::ScreenState::MAIN_MENU;
                state.currentScreen = game::ScreenState::CREDITS;
                break;
            case 4:
                state.currentScreen = game::ScreenState::EXIT;
                break;
            default:
                break;
            }
        }

        if (IsKeyPressed(KEY_ESCAPE))
        {
            state.currentScreen = game::ScreenState::EXIT;
        }
    }

    void RenderMainMenu(const game::GameState& state)
    {
        (void)state;
        BeginDrawing();
        ClearBackground(RAYWHITE);

        const int fontSize = 30;
        const int baseY = 200;
        const int spacing = 40;

        DrawText("MAIN MENU", game::GAME_SCREEN_WIDTH / 2 - 100, 100, 40, DARKBLUE);

        const char* menuItems[MAIN_MENU_COUNT] = { "Play", "Options", "Instructions", "Credits", "Exit" };
        for (int i = 0; i < MAIN_MENU_COUNT; i++)
        {
            int posY = baseY + i * spacing;
            Color col = (i == mainMenuSelection) ? RED : BLACK;
            DrawText(menuItems[i], game::GAME_SCREEN_WIDTH / 2 - 50, posY, fontSize, col);
        }
        EndDrawing();
    }

    void UpdatePauseMenu(game::GameState& state)
    {
        if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_P))
        {
            state.currentScreen = game::ScreenState::GAMEPLAY;
            return;
        }

        if (IsKeyPressed(KEY_DOWN))
            pauseMenuSelection = (pauseMenuSelection + 1) % PAUSE_MENU_COUNT;
        if (IsKeyPressed(KEY_UP))
            pauseMenuSelection = (pauseMenuSelection - 1 + PAUSE_MENU_COUNT) % PAUSE_MENU_COUNT;

        const int baseY = 180;
        const int spacing = 40;
        const int fontSize = 30;
        for (int i = 0; i < PAUSE_MENU_COUNT; i++)
        {
            Rectangle itemRec = { (float)(game::GAME_SCREEN_WIDTH / 2 - 100), (float)(baseY + i * spacing), 200, (float)fontSize };
            if (IsMouseOverRect(itemRec))
            {
                pauseMenuSelection = i;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    break;
            }
        }


        if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            switch (pauseMenuSelection)
            {
            case 0:
                state.currentScreen = game::ScreenState::GAMEPLAY;
                break;
            case 1:
                game::InitGame(state);
                state.currentScreen = game::ScreenState::GAMEPLAY;
                break;
            case 2:
                state.previousScreen = game::ScreenState::PAUSE_MENU;
                state.currentScreen = game::ScreenState::OPTIONS;
                break;
            case 3:
                state.previousScreen = game::ScreenState::PAUSE_MENU;
                state.currentScreen = game::ScreenState::INSTRUCTIONS;
                break;
            case 4:
                state.currentScreen = game::ScreenState::MAIN_MENU;
                break;
            default:
                break;
            }
        }
    }

    void RenderPauseMenu(const game::GameState& state)
    {
        (void)state;
        BeginDrawing();
        ClearBackground(RAYWHITE);

        const int fontSize = 30;
        const int baseY = 180;
        const int spacing = 40;

        DrawText("PAUSE MENU", game::GAME_SCREEN_WIDTH / 2 - 100, 100, 40, DARKBLUE);

        const char* menuItems[PAUSE_MENU_COUNT] = { "Continue", "Restart", "Options", "Instructions", "Main Menu" };
        for (int i = 0; i < PAUSE_MENU_COUNT; i++)
        {
            int posY = baseY + i * spacing;
            Color col = (i == pauseMenuSelection) ? RED : BLACK;
            DrawText(menuItems[i], game::GAME_SCREEN_WIDTH / 2 - 100, posY, fontSize, col);
        }

        EndDrawing();
    }


    void UpdateSubMenu(game::GameState& state)
    {

        if (IsKeyPressed(KEY_ESCAPE))
            state.currentScreen = state.previousScreen;


        Rectangle backButton = { (float)(game::GAME_SCREEN_WIDTH / 2 - 150), 400, 300, 20 };
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && IsMouseOverRect(backButton))
            state.currentScreen = state.previousScreen;
    }

    void RenderSubMenu(const game::GameState& state, const char* title, const char* info)
    {
        (void)state;
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(title, game::GAME_SCREEN_WIDTH / 2 - 100, 100, 40, DARKBLUE);
        DrawText(info, game::GAME_SCREEN_WIDTH / 2 - 150, 200, 20, BLACK);
        DrawText("Press ESC to go back", game::GAME_SCREEN_WIDTH / 2 - 150, 400, 20, DARKGRAY);

        EndDrawing();
    }
}

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

        DrawPlayer(state.player);
        DrawShield(state.shieldX, state.shieldY, state.shieldRadius);
        DrawObstacles(state.obstacles, MAX_OBSTACLES);
        DrawEnemies(state.enemies, MAX_ENEMIES);
        DrawPowerUp(state.powerUp);
        DrawText(TextFormat("Score: %d", state.localGameScore),
            10, 10, 20, BLACK);

        if (state.gameOver)
        {
            DrawText("GAME OVER", GAME_SCREEN_WIDTH / 2 - 50,
                GAME_SCREEN_HEIGHT / 2, 30, RED);
            DrawText("Press R to Restart", GAME_SCREEN_WIDTH / 2 - 70,
                GAME_SCREEN_HEIGHT / 2 + 40, 20, DARKGRAY);
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
                UpdateMainMenu(state);
                RenderMainMenu(state);
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
                UpdatePauseMenu(state);
                RenderPauseMenu(state);
                break;

            case ScreenState::OPTIONS:
                UpdateSubMenu(state);
                RenderSubMenu(state, "OPTIONS", "null.");
                break;

            case ScreenState::INSTRUCTIONS:
                UpdateSubMenu(state);
                RenderSubMenu(state, "INSTRUCTIONS", "Use the arrows and A/S to move,\nuse the mouse to select and use ESC to go back.\nP: Pause/Resume");
                break;

            case ScreenState::CREDITS:
                UpdateSubMenu(state);
                RenderSubMenu(state, "CREDITS", "Developed by: Leonardo Brizuela. \n Game version: v0.2");
                break;

            default:
                break;
            }
        }
        CloseWindow();
    }
}