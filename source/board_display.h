#pragma once
#include <SDL.h>
#include "board.h"

//Displays sudoku board at given coordinates
class BoardDisplay {
public:
    BoardDisplay(int x, int y, int width, int height);

    //Displayed board
    Board board;

    void render(SDL_Renderer*);
private:
    SDL_Point mPosition;
    int mWidth, mHeight;
};