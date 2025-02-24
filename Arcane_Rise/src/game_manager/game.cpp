#include "raylib.h"
#include "game.h"

namespace game
{
    void RunGame()
    {
        InitWindow(screenWidth, screenHeight, "Arcane Rise");
        SetTargetFPS(60);

        Player player = { static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight) - 50.0f, 20.0f };
        float shieldRadius = 30.0f;
        float shieldX = 0.0f, shieldY = 0.0f;
        float shieldDistance = 60.0f;
        bool gameOver = false;
 
        while (!WindowShouldClose())
        {
            float deltaTime = GetFrameTime();
            if (!gameOver)
            {
                
                UpdatePlayer(player, deltaTime);
                UpdateShieldPosition(player, shieldDistance, shieldX, shieldY);
                BeginDrawing();
                ClearBackground(RAYWHITE);

                if (!gameOver)
                {
                    DrawPlayer(player);
                    DrawShield(shieldX, shieldY, shieldRadius);
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