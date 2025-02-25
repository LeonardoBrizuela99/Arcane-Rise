#include "raylib.h"
#include "game.h"

namespace game
{
    
    Player player;
    float shieldX = 0.0f, shieldY = 0.0f;
    float shieldRadius = 30.0f;   
    float shieldDistance = 60.0f; 
    int localGameScore = 0;       
    float spawnTimer = 0.0f;
    bool gameOver = false;

    float GetSpawnInterval(int score)
    {
        if (score < 500) return 1.0f;
        else if (score < 1000) return 0.75f;
        else if (score < 1500) return 0.5f;
        else return 0.25f;
    }

    void InitGame()
    {
        player = { static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight) - 50.0f, 20.0f };
        localGameScore = 0;
        spawnTimer = 0.0f;
        gameOver = false;
        InitObstacles();
        InitEnemies();
        InitPowerUp();
    }

    
    void UpdateGame(float deltaTime)
    {
        UpdatePlayer(player, deltaTime);
        UpdateShieldPosition(player, shieldDistance, shieldX, shieldY);
        UpdateObstacles(deltaTime);
        UpdateEnemies(deltaTime);
        UpdatePowerUp(deltaTime);

        spawnTimer += deltaTime;
        if (spawnTimer >= GetSpawnInterval(localGameScore))
        {
            spawnTimer = 0.0f;
            localGameScore += 20;
        }
    }

    
    void ProcessCollisions()
    {
        
        for (int i = 0; i < MAX_OBSTACLES; i++)
        {
            if (obstacles[i].active)
            {
                if (CheckCollisionCircleRec({ shieldX, shieldY }, shieldRadius, obstacles[i].rect))
                {
                   
                    ResetObstacle(i);
                }
                else if (CheckCollisionCircleRec({ player.x, player.y }, player.radius, obstacles[i].rect))
                {
                    gameOver = true;
                    return;
                }
            }
        }

       
        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            if (enemies[i].active)
            {
                if (CheckCollisionCircleRec({ shieldX, shieldY }, shieldRadius, enemies[i].rect))
                {
                  
                    ResetEnemies(i);
                }
                else if (CheckCollisionCircleRec({ player.x, player.y }, player.radius, enemies[i].rect))
                {
                    gameOver = true;
                    return;
                }
            }
        }

       
        if (powerUp.active)
        {
            if (CheckCollisionCircleRec({ player.x, player.y }, player.radius, powerUp.rect) ||
                CheckCollisionCircleRec({ shieldX, shieldY }, shieldRadius, powerUp.rect))
            {               
                ResetPowerUp();
                localGameScore += 100;
            }
        }
    }
   
    void RenderFrame()
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!gameOver)
        {
            DrawPlayer(player);
            DrawShield(shieldX, shieldY, shieldRadius);
            DrawObstacles();
            DrawEnemies();
            DrawPowerUp();
            DrawText(TextFormat("Score: %d", localGameScore), 10, 10, 20, BLACK);
        }
        else
        {
            DrawText("GAME OVER", screenWidth / 2 - 50, screenHeight / 2, 30, RED);
            DrawText("Press R to Restart", screenWidth / 2 - 70, screenHeight / 2 + 40, 20, DARKGRAY);
        }
        EndDrawing();
    }

   
    void RunGame()
    {
        InitWindow(screenWidth, screenHeight, "Arcane Rise");
        SetTargetFPS(60);
        InitGame();

        while (!WindowShouldClose())
        {
            float deltaTime = GetFrameTime();

            if (!gameOver)
            {
                UpdateGame(deltaTime);
                ProcessCollisions();
            }
            else if (IsKeyPressed(KEY_R))
            {
                InitGame();
            }
            RenderFrame();
        }
        CloseWindow();
    }
}