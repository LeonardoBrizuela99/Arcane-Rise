#ifndef MENU_H
#define MENU_H

#include "game_manager/game.h"

namespace menu
{
    void UpdateMainMenu(game::GameState& state);
    void RenderMainMenu(const game::GameState& state);
    void UpdatePauseMenu(game::GameState& state);
    void RenderPauseMenu(const game::GameState& state);
    void UpdateSubMenu(game::GameState& state);
    void RenderSubMenu(const game::GameState& state, const char title[], const char info[]);
}

#endif