#pragma once
#include "button.h"
#include "board.h"
#include <SDL.h>

class ButtonBoard {
public:
    ButtonBoard();

    Board getBoard() const;

    void render(SDL_Renderer* r);
private:
    Button buttonBoard[9][9];
};