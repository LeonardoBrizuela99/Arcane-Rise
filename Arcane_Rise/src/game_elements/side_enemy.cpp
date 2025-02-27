#include "side_enemy.h"
#include "game_manager/game.h"
#include "raylib.h"
#include <cstdlib>

namespace game
{
    const int SIDE_ENEMY_WIDTH = 25;
    const int SIDE_ENEMY_HEIGHT = 25;
    const float SIDE_ENEMY_SPEED = 80.0f;
    void InitSideEnemies(SideEnemy sideEnemies[], int count, int screenWidth, int screenHeight, const Player& player)
    {

        screenWidth = screenWidth;
        screenHeight = screenHeight;

        for (int i = 0; i < count; i++)
        {
            sideEnemies[i].active = false;
            sideEnemies[i].rect.x = -SIDE_ENEMY_WIDTH;
            sideEnemies[i].rect.y = player.y;
            sideEnemies[i].rect.width = SIDE_ENEMY_WIDTH;
            sideEnemies[i].rect.height = SIDE_ENEMY_HEIGHT;
            sideEnemies[i].speedX = SIDE_ENEMY_SPEED;
            sideEnemies[i].direction = 0;
        }
    }

    void ResetSideEnemy(SideEnemy& enemy, int screenWidth, int screenHeight, const Player& player)
    {

        screenHeight = screenHeight;


        int side = rand() % 2;
        enemy.active = true;
        enemy.rect.y = player.y;
        if (side == 0)
        {
            enemy.rect.x = 0;
            enemy.direction = 1;
        }
        else
        {
            enemy.rect.x = static_cast<float>(screenWidth - SIDE_ENEMY_WIDTH);
            enemy.direction = -1;
        }
        enemy.speedX = SIDE_ENEMY_SPEED;
    }

    void UpdateSideEnemies(SideEnemy sideEnemies[], int count, float deltaTime)
    {
        for (int i = 0; i < count; i++)
        {
            if (sideEnemies[i].active)
            {
                sideEnemies[i].rect.x += sideEnemies[i].speedX * sideEnemies[i].direction * deltaTime;

                if (sideEnemies[i].direction == 1 && sideEnemies[i].rect.x > GAME_SCREEN_WIDTH)
                    sideEnemies[i].active = false;
                else if (sideEnemies[i].direction == -1 && sideEnemies[i].rect.x + sideEnemies[i].rect.width < 0)
                    sideEnemies[i].active = false;
            }
        }
    }

    void DrawSideEnemies(const SideEnemy sideEnemies[], int count)
    {
        for (int i = 0; i < count; i++)
        {
            if (sideEnemies[i].active)
            {
                DrawRectangleRec(sideEnemies[i].rect, ORANGE);
            }
        }
    }
}
