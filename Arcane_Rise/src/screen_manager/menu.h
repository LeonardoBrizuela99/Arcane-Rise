#pragma once
#ifndef MENU_H
#define MENU_H

#include "game_manager/game.h"

namespace menu
{
    void UpdateMainMenu(game::GameState& state);
    void RenderMainMenu(const game::GameState&);
    void UpdatePauseMenu(game::GameState& state);
    void RenderPauseMenu(const game::GameState&);
    void UpdateSubMenu(game::GameState& state);
    void RenderSubMenu(const game::GameState&, const char title[], const char info[]);
}
#endif
