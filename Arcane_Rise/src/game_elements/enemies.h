#ifndef ENEMIES_H
#define ENEMIES_H
#include "raylib.h"

const int MAX_ENEMIES = 5; 

struct Enemies 
{
    Rectangle rect;
    float speed;
    bool active;
};

void InitEnemies();
void UpdateEnemies(float deltaTime);
void DrawEnemies();

#endif