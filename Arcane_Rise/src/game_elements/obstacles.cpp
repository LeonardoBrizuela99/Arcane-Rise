#include "obstacles.h"
#include <raylib.h>
#include <cstdlib>

namespace game {

    Obstacle obstacles[MAX_OBSTACLES];

    void InitObstacles() {
        // Inicializa cada obst�culo con una posici�n aleatoria en X y por encima de la ventana (Y negativo)
        for (int i = 0; i < MAX_OBSTACLES; i++) {
            obstacles[i].rect = { static_cast<float>(rand() % (1280 - 30)), -30.0f, 30.0f, 30.0f };
            obstacles[i].speedY = static_cast<float>(150 + rand() % 150);
            obstacles[i].active = true;
        }
    }

    void UpdateObstacles(float deltaTime) {
        // Actualiza la posici�n de cada obst�culo (se mueven verticalmente)
        for (int i = 0; i < MAX_OBSTACLES; i++) {
            if (obstacles[i].active) {
                obstacles[i].rect.y += obstacles[i].speedY * deltaTime;
                // Cuando el obst�culo sale por abajo, se reinicia en la parte superior
                if (obstacles[i].rect.y > 720) {
                    obstacles[i].rect.y = -30.0f;
                    obstacles[i].rect.x = static_cast<float>(rand() % (1280 - 30));
                }
            }
        }
    }

    void DrawObstacles() {
        // Dibuja cada obst�culo activo
        for (int i = 0; i < MAX_OBSTACLES; i++) {
            if (obstacles[i].active) {
                DrawRectangleRec(obstacles[i].rect, RED);
            }
        }
    }

} // namespace game
