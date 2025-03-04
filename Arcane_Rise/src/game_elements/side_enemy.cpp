#include "side_enemy.h"
#include "game_manager/game.h"
#include"resource_manager/resource_manager.h"
#include "raylib.h"
#include <cstdlib>

namespace game
{
    const int SIDE_ENEMY_WIDTH = 25;
    const int SIDE_ENEMY_HEIGHT = 25;
    const float SIDE_ENEMY_SPEED = 150.0f;
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

    void ResetSideEnemy(SideEnemy& enemy, int screenWidth, const Player& player)
    {
        int side = rand() % 2;
        enemy.active = true;

        enemy.rect.y = player.y;
        if (side == 0)
        {

            enemy.rect.x = -SIDE_ENEMY_WIDTH - 10;
            enemy.direction = 1;
        }
        else
        {

            enemy.rect.x = static_cast<float>(screenWidth) + 10;
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
        float offsetX = 26.0f;
        float offsetY = 10.0f;
        float scaleX = 2.5f;
        float scaleY = 2.5f;

        for (int i = 0; i < count; i++)
        {
            if (sideEnemies[i].active)
            {
                float t = static_cast<float>(GetTime());
                int frame = ((int)(t * 4)) % 2;

                Texture2D tex = (frame == 0) ? resource::sideEnemyTexture1 : resource::sideEnemyTexture2;
                Rectangle source = { 0, 0, static_cast<float>(tex.width), static_cast<float>(tex.height) };

                float newWidth = sideEnemies[i].rect.width * scaleX;
                float newHeight = sideEnemies[i].rect.height * scaleY;

                Rectangle dest = 
                {
                    sideEnemies[i].rect.x + (sideEnemies[i].rect.width - newWidth) / 2 + offsetX,
                    sideEnemies[i].rect.y + (sideEnemies[i].rect.height - newHeight) / 2 + offsetY,
                    newWidth,
                    newHeight
                };

                Vector2 origin = { newWidth / 2, newHeight / 2 };

                if (sideEnemies[i].direction == -1)
                {
                    source.width = -source.width;
                }
                //DrawRectangleRec(sideEnemies[i].rect, ORANGE);
                DrawTexturePro(tex, source, dest, origin, 0.0f, WHITE);
            }
        }
    }
}