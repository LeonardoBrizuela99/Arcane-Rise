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


/*OPTIONS", "null.")
"INSTRUCTIONS", "Use the arrows and A/S to move,\nuse the mouse to select and use ESC to go back.\nP: Pause/Resume"
"CREDITS", "Developed by: Leonardo Brizuela. \n Game version: v0.2"
*/