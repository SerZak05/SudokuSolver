#pragma once
#include "button.h"
#include "board.h"
#include <SDL.h>

//A button board to input sudoku board
class ButtonBoard {
public:
    ButtonBoard(int x, int y, int width, int height);

    //Returns sudoku board that is displayed on buttons
    Board getBoard() const;

    void setNumber(int val, int i, int j);

    //Passes events to buttons
    void handleEvent(const SDL_Event*);
    void render(SDL_Renderer* r);
private:
    Button mButtons[9][9];

    SDL_Point mPosition;
    int mWidth, mHeight;
};