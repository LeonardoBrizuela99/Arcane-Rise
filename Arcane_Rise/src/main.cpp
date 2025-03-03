#include "game_manager/game.h"
#include <ctime>
#include<cstdlib>

using namespace game;

int main(void)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    game::RunGame();
    return 0;
}   