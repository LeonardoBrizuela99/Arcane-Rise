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

        InitObstacles();
        InitEnemies();

        while (!WindowShouldClose()) 
        {
            float deltaTime = GetFrameTime();

            if (!gameOver) 
            {
                UpdatePlayer(player, deltaTime);
                UpdateShieldPosition(player, shieldDistance, shieldX, shieldY);
                UpdateObstacles(deltaTime);
                UpdateEnemies(deltaTime);
               
                for (int i = 0; i < MAX_OBSTACLES; i++)
                {
                    if (obstacles[i].active) 
                    {
                        if (CheckCollisionCircleRec({ shieldX, shieldY }, shieldRadius, obstacles[i].rect))
                        {                            
                            obstacles[i].rect.y = -30.0f;
                            obstacles[i].rect.x = static_cast<float>(rand() % (screenWidth - 30));
                        }
                        else if (CheckCollisionCircleRec({ player.x, player.y }, player.radius, obstacles[i].rect)) 
                        {                          
                            gameOver = true;
                            break;
                        }
                    }
                }

                for (int i = 0; i < MAX_ENEMIES; i++) 
                {
                    if (enemies[i].active) 
                    {
                        if (CheckCollisionCircleRec({ shieldX, shieldY }, shieldRadius, enemies[i].rect))
                        {                        
                            enemies[i].rect.y = -20.0f;
                            enemies[i].rect.x = static_cast<float>(rand() % (screenWidth - 20));
                            enemies[i].time = 0.0f;
                        }
                        else if (CheckCollisionCircleRec({ player.x, player.y }, player.radius, enemies[i].rect))
                        {
                            gameOver = true;
                            break;
                        }
                    }
                }
            }
            BeginDrawing();
            ClearBackground(RAYWHITE);
            if (!gameOver) 
            {
                DrawPlayer(player);
                DrawShield(shieldX, shieldY, shieldRadius);
                DrawObstacles();
                DrawEnemies();
            }
            else 
            {
                DrawText("GAME OVER", screenWidth / 2 - 50, screenHeight / 2, 30, RED);
                DrawText("Press R to Restart", screenWidth / 2 - 70, screenHeight / 2 + 40, 20, DARKGRAY);

                if (IsKeyPressed(KEY_R)) 
                {
                    gameOver = false;
                    player = { static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight) - 50.0f, 20.0f };
                    InitObstacles();
                    InitEnemies();
                }
            }
            EndDrawing();
        }
        CloseWindow();
    }
}