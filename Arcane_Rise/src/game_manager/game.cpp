#include "raylib.h"
#include "game.h"
//#include "player.h"
//#include "obstacles.h"

namespace game {

    void RunGame() {
        InitWindow(screenWidth, screenHeight, "Arcane Rise");
        SetTargetFPS(60);

        // El jugador inicia centrado horizontalmente y a 50px de la parte inferior
        Player player = { static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight) - 50.0f, 20.0f };

        // Variables para el escudo (opcional)
        float shieldRadius = 30.0f;
        float shieldX = 0.0f, shieldY = 0.0f;
        float shieldDistance = 60.0f;
        bool gameOver = false;

        // Inicializar obstáculos
        InitObstacles();

        while (!WindowShouldClose()) {
            float deltaTime = GetFrameTime();

            if (!gameOver) {
                UpdatePlayer(player, deltaTime);
                UpdateShieldPosition(player, shieldDistance, shieldX, shieldY);
                UpdateObstacles(deltaTime);

                // Verificar colisión entre el jugador y cada obstáculo
                for (int i = 0; i < MAX_OBSTACLES; i++) {
                    if (obstacles[i].active &&
                        CheckCollisionCircleRec({ player.x, player.y }, player.radius, obstacles[i].rect)) {
                        gameOver = true;
                        break;
                    }
                }
            }

            BeginDrawing();
            ClearBackground(RAYWHITE);

            if (!gameOver) {
                DrawPlayer(player);
                DrawShield(shieldX, shieldY, shieldRadius);
                DrawObstacles();
            }
            else {
                DrawText("GAME OVER", screenWidth / 2 - 50, screenHeight / 2, 30, RED);
                DrawText("Press R to Restart", screenWidth / 2 - 70, screenHeight / 2 + 40, 20, DARKGRAY);

                if (IsKeyPressed(KEY_R)) {
                    gameOver = false;
                    // Reinicia la posición del jugador y reinyecta los obstáculos
                    player = { static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight) - 50.0f, 20.0f };
                    InitObstacles();
                }
            }

            EndDrawing();
        }
        CloseWindow();
    }

}
