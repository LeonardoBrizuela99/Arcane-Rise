#include "menu.h"
#include "raylib.h"
#include "game_manager/game.h"


static int mainMenuSelection = 0;
static const int MAIN_MENU_COUNT = 5;

static int pauseMenuSelection = 0;
static const int PAUSE_MENU_COUNT = 5;

static bool IsMouseOverRect(Rectangle rec)
{
    Vector2 mousePos = GetMousePosition();
    return CheckCollisionPointRec(mousePos, rec);
}

namespace menu
{
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
            Rectangle itemRec = { static_cast<float>(game::GAME_SCREEN_WIDTH / 2 - 50),
                                  static_cast<float>(baseY + i * spacing),
                                  200,
                                  static_cast<float>(fontSize) };
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


    void RenderMainMenu(const game::GameState&)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        const int fontSize = 30;
        const int baseY = 200;
        const int spacing = 40;

        DrawText("MAIN MENU", game::GAME_SCREEN_WIDTH / 2 - 100, 100, 40, DARKBLUE);


        char menuItems[MAIN_MENU_COUNT][32] = {
            "Play",
            "Options",
            "Instructions",
            "Credits",
            "Exit"
        };
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
            Rectangle itemRec = { static_cast<float>(game::GAME_SCREEN_WIDTH / 2 - 100),
                                  static_cast<float>(baseY + i * spacing),
                                  200,
                                  static_cast<float>(fontSize) };
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

    void RenderPauseMenu(const game::GameState&)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        const int fontSize = 30;
        const int baseY = 180;
        const int spacing = 40;

        DrawText("PAUSE MENU", game::GAME_SCREEN_WIDTH / 2 - 100, 100, 40, DARKBLUE);

        char menuItems[PAUSE_MENU_COUNT][32] = {
            "Continue",
            "Restart",
            "Options",
            "Instructions",
            "Main Menu"
        };
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


        Rectangle backButton = { static_cast<float>(game::GAME_SCREEN_WIDTH / 2 - 150), 400, 300, 20 };
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && IsMouseOverRect(backButton))
            state.currentScreen = state.previousScreen;
    }

    void RenderSubMenu(const game::GameState&, const char title[], const char info[])
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(title, game::GAME_SCREEN_WIDTH / 2 - 100, 100, 40, DARKBLUE);
        DrawText(info, game::GAME_SCREEN_WIDTH / 2 - 150, 200, 20, BLACK);
        DrawText("Press ESC to go back", game::GAME_SCREEN_WIDTH / 2 - 150, 400, 20, DARKGRAY);

        EndDrawing();
    }
}
