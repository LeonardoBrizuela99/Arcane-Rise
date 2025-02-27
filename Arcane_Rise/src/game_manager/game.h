#ifndef GAME_H
#define GAME_H

#include "game_elements/player.h"
#include "game_elements/powerup.h"
#include "game_elements/obstacles.h"
#include "game_elements/enemies.h"
#include "game_elements/side_enemy.h"  

namespace game
{
    const int GAME_SCREEN_WIDTH = 800;
    const int GAME_SCREEN_HEIGHT = 600;

    const float EFFECT_DURATION = 5.0f;

    const float SHIELD_INIT_RADIUS = 20.0f;
    const float SHIELD_NO_POWERUP_RADIUS = 30.0f;
    const float SHIELD_POWERUP_RADIUS = 40.0f;
    const float SHIELD_DISTANCE = 60.0f;

    const float BASE_PLAYER_SPEED = 300.0f;
    const float SPEED_POWER_MULTIPLIER = 1.25f;

    const int MAX_OBSTACLES = 20;
    const int MAX_ENEMIES = 5;

    const int SCORE_INCREMENT_OBSTACLE = 20;
    const int SCORE_INCREMENT_ENEMY = 50;
    const int SCORE_INCREMENT_POWERUP = 100;

    const int TARGET_FPS = 60;

    enum class ScreenState
    {
        MAIN_MENU,
        GAMEPLAY,
        PAUSE_MENU,
        OPTIONS,
        INSTRUCTIONS,
        CREDITS,
        EXIT
    };

    struct GameState
    {
        Player player;
        float shieldX;
        float shieldY;
        float shieldRadius;
        float shieldDistance;
        int localGameScore;
        float spawnTimer;
        bool gameOver;

        ScreenState currentScreen;
        ScreenState previousScreen;

        float basePlayerSpeed;
        float currentPlayerSpeed;
        float shieldPowerTimer;
        float speedPowerTimer;

        PowerUp powerUp;
        Obstacle obstacles[MAX_OBSTACLES];
        Enemies enemies[MAX_ENEMIES];
        SideEnemy sideEnemies[MAX_SIDE_ENEMIES];

        int activeObstacles;
        int activeEnemies;
        int activeSideEnemies;
        int lastObstacleScoreThreshold;
        int lastEnemyScoreThreshold;
        int lastPowerUpScoreThreshold;
        int lastSideEnemyScoreThreshold;
        float sideEnemyRespawnTimers[MAX_SIDE_ENEMIES];

    };

    void InitGame(GameState& state);
    void UpdateGame(GameState& state, float deltaTime);
    void ProcessCollisions(GameState& state);
    void RenderFrame(const GameState& state);
    void RunGame();
}
#endif