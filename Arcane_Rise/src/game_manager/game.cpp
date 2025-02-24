#include "raylib.h"
#include "game.h"

namespace game
{
    void RunGame()
    {
        InitWindow(screenWidth, screenHeight, "Arcane Rise");
        SetTargetFPS(60);

        Player player = { static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight) - 50.0f, 20.0f };
        bool gameOver = false;
 
        while (!WindowShouldClose())
        {
            float deltaTime = GetFrameTime();
            if (!gameOver)
            {
                
                UpdatePlayer(player, deltaTime);
                BeginDrawing();
                ClearBackground(RAYWHITE);

                if (!gameOver)
                {
                    DrawPlayer(player);
                }
                else 
                {
                    DrawText("GAME OVER", screenWidth / 2 - 50, screenHeight / 2, 30, RED);
                    DrawText("Press R to Restart", screenWidth / 2 - 70, screenHeight / 2 + 40, 20, DARKGRAY);       
                    gameOver = false;
                }
            }
            EndDrawing();
        }
        CloseWindow();
    }
} 