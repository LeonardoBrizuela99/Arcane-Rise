#include "menu.h"
#include "raylib.h"
#include "game_manager/game.h"
#include"resource_manager/resource_manager.h"
#include <string>


struct MenuOption {
    Rectangle rect;
    const char* text;
};

static const Color BUTTON_NORMAL_BG = { 250, 235, 215, 255 };
static const Color BUTTON_HOVER_BG = { 244, 164, 96, 255 };
static const Color TEXT_NORMAL = BLACK;
static const Color TEXT_HOVER = BLUE;

static const int MAIN_MENU_OPTION_COUNT = 5;
static MenuOption mainMenuOptions[MAIN_MENU_OPTION_COUNT];
static bool mainMenuInitialized = false;

static void InitMainMenuOptions()
{
    float buttonWidth = 300;
    float buttonHeight = 50;
    float startX = game::GAME_SCREEN_WIDTH / 2 - buttonWidth / 2;
    float startY = 200;

    float spacing = 70;

    const char* texts[MAIN_MENU_OPTION_COUNT] = { "Start Game", "Options", "Instructions", "Credits", "Exit" };

    for (int i = 0; i < MAIN_MENU_OPTION_COUNT; i++) {
        mainMenuOptions[i].rect.x = startX;
        mainMenuOptions[i].rect.y = startY + i * spacing;
        mainMenuOptions[i].rect.width = buttonWidth;
        mainMenuOptions[i].rect.height = buttonHeight;
        mainMenuOptions[i].text = texts[i];
    }
    mainMenuInitialized = true;
}

namespace menu {

    void UpdateMainMenu(game::GameState& state)
    {
        if (!mainMenuInitialized)
            InitMainMenuOptions();

        Vector2 mousePos = GetMousePosition();
        for (int i = 0; i < MAIN_MENU_OPTION_COUNT; i++)
        {
            if (CheckCollisionPointRec(mousePos, mainMenuOptions[i].rect))
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    PlaySound(resource::select);
                    switch (i)
                    {
                    case 0:
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
            }
        }
    }

    void RenderMainMenu(const game::GameState&)
    {
        BeginDrawing();

        DrawTexture(resource::backgroundTexture, 0, 0, WHITE);
        Vector2 mousePos = GetMousePosition();
        for (int i = 0; i < MAIN_MENU_OPTION_COUNT; i++) {
            bool hovered = CheckCollisionPointRec(mousePos, mainMenuOptions[i].rect);
            Color btnColor = hovered ? BUTTON_HOVER_BG : BUTTON_NORMAL_BG;
            Color txtColor = hovered ? TEXT_HOVER : TEXT_NORMAL;
            DrawRectangleRec(mainMenuOptions[i].rect, btnColor);
            DrawRectangleLinesEx(mainMenuOptions[i].rect, 2, BLACK);
            int fontSize = 20;
            int textWidth = MeasureText(mainMenuOptions[i].text, fontSize);
            int textX = (int)mainMenuOptions[i].rect.x + (((int)mainMenuOptions[i].rect.width - textWidth) / 2);
            int textY = (int)mainMenuOptions[i].rect.y + (((int)mainMenuOptions[i].rect.height - fontSize) / 2);
            DrawText(mainMenuOptions[i].text, textX, textY, fontSize, txtColor);
        }
        EndDrawing();
    }

    static const int PAUSE_MENU_OPTION_COUNT = 5;
    static MenuOption pauseMenuOptions[PAUSE_MENU_OPTION_COUNT];
    static bool pauseMenuInitialized = false;

    static void InitPauseMenuOptions() {
        float buttonWidth = 300;
        float buttonHeight = 50;
        float startX = game::GAME_SCREEN_WIDTH / 2 - buttonWidth / 2;
        float startY = 180;
        float spacing = 70;
        const char* texts[PAUSE_MENU_OPTION_COUNT] = { "Continue", "Restart", "Options", "Instructions", "Main Menu" };

        for (int i = 0; i < PAUSE_MENU_OPTION_COUNT; i++) {
            pauseMenuOptions[i].rect.x = startX;
            pauseMenuOptions[i].rect.y = startY + i * spacing;
            pauseMenuOptions[i].rect.width = buttonWidth;
            pauseMenuOptions[i].rect.height = buttonHeight;
            pauseMenuOptions[i].text = texts[i];
        }
        pauseMenuInitialized = true;
    }

    void UpdatePauseMenu(game::GameState& state) {
        if (!pauseMenuInitialized)
            InitPauseMenuOptions();

        Vector2 mousePos = GetMousePosition();
        for (int i = 0; i < PAUSE_MENU_OPTION_COUNT; i++) {
            if (CheckCollisionPointRec(mousePos, pauseMenuOptions[i].rect)) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    PlaySound(resource::select);
                    switch (i) {
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
        }
    }

    void RenderPauseMenu(const game::GameState&)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(resource::pause, 0, 0, WHITE);
     
        Vector2 mousePos = GetMousePosition();
        for (int i = 0; i < PAUSE_MENU_OPTION_COUNT; i++) {
            bool hovered = CheckCollisionPointRec(mousePos, pauseMenuOptions[i].rect);
            Color btnColor = hovered ? BUTTON_HOVER_BG : BUTTON_NORMAL_BG;
            Color txtColor = hovered ? TEXT_HOVER : TEXT_NORMAL;

            DrawRectangleRec(pauseMenuOptions[i].rect, btnColor);
            DrawRectangleLinesEx(pauseMenuOptions[i].rect, 2, BLACK);

            int fontSize = 20;
            int textWidth = MeasureText(pauseMenuOptions[i].text, fontSize);
            int textX = (int)pauseMenuOptions[i].rect.x + (((int)pauseMenuOptions[i].rect.width - textWidth) / 2);
            int textY = (int)pauseMenuOptions[i].rect.y + (((int)pauseMenuOptions[i].rect.height - fontSize) / 2);
            DrawText(pauseMenuOptions[i].text, textX, textY, fontSize, txtColor);
        }
        EndDrawing();
    }

    void UpdateSubMenu(game::GameState& state)
    {
        if (IsKeyPressed(KEY_ESCAPE))
            state.currentScreen = state.previousScreen;

        const int backBtnWidth = 150;
        const int backBtnHeight = 50;
        Rectangle backButton = { 20,  600 - backBtnHeight - 20, backBtnWidth, backBtnHeight };

        if (CheckCollisionPointRec(GetMousePosition(), backButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            PlaySound(resource::select);
            state.currentScreen = state.previousScreen;
        }
    }

    void RenderSubMenu(const game::GameState&, const char title[]) {
        BeginDrawing();
        std::string menuTitle = title;
       
        if (menuTitle == "INSTRUCTIONS") 
        {
            DrawTexture(resource::instruction, 0, 0, WHITE);
        }
        else if (menuTitle == "OPTIONS") 
        {
            DrawTexture(resource::options, 0, 0, WHITE);
        }
        else if (menuTitle == "CREDITS")
        {
            
            DrawTexture(resource::credits, 0, 0, WHITE);
        }     
        ClearBackground(RAYWHITE);
        
        const int backBtnWidth = 150;
        const int backBtnHeight = 50;
        Rectangle backButton = { 20, 600 - backBtnHeight - 20, backBtnWidth, backBtnHeight };

        bool hovered = CheckCollisionPointRec(GetMousePosition(), backButton);
        Color btnColor = hovered ? BUTTON_HOVER_BG : BUTTON_NORMAL_BG;
        Color txtColor = hovered ? TEXT_HOVER : TEXT_NORMAL;
        DrawRectangleRec(backButton, btnColor);
        DrawRectangleLinesEx(backButton, 2, BLACK);
        int fontSize = 20;
        int textWidth = MeasureText("Back", fontSize);
        int textX = (int)backButton.x + (((int)backButton.width - textWidth) / 2);
        int textY = (int)backButton.y + (((int)backButton.height - fontSize) / 2);
        DrawText("Back", textX, textY, fontSize, txtColor);

        EndDrawing();
    }
}
