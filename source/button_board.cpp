#include "button_board.h"

ButtonBoard::ButtonBoard(int x, int y, int width, int height) : mWidth(width), mHeight(height) {
    mPosition.x = x;
    mPosition.y = y;
    //Positioning all buttons
    int stepX = width / 9;
    int stepY = width / 9;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            mButtons[i][j] = Button(x + stepX * i, y + stepY * j, stepX, stepY);
        }
    }
}

Board ButtonBoard::getBoard() const {
    Board res;
    //Reading buttons' numbers
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            res.set(mButtons[i][j].getNumber(), i, j);
        }
    }
    return res;
}

void ButtonBoard::setNumber(int val, int i, int j) {
    if (i >= 0 && i < 9 && j >= 0 && j < 9)
        mButtons[i][j].setNumber(val);
}

void ButtonBoard::handleEvent(const SDL_Event* e) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            mButtons[i][j].handleEvent(e);
        }
    }
}

void ButtonBoard::render(SDL_Renderer* r) {
    //Drawing buttons
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            mButtons[i][j].render(r);
        }
    }

    //Drawing 3x3 squares
    SDL_SetRenderDrawColor(r, 50, 50, 50, 255);
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            //Left upper corner
            SDL_Point startPos = mButtons[i][j].getPosition();
            SDL_RenderDrawLine(r, startPos.x, startPos.y, startPos.x, startPos.y + mHeight / 3);
            SDL_RenderDrawLine(r, startPos.x, startPos.y + mHeight / 3, startPos.x + mWidth / 3, startPos.y + mHeight / 3);
            SDL_RenderDrawLine(r, startPos.x + mWidth / 3, startPos.y + mHeight / 3, startPos.x + mWidth / 3, startPos.y);
            SDL_RenderDrawLine(r, startPos.x + mWidth / 3, startPos.y, startPos.x, startPos.y);
        }
    }

    //Drawing contour
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderDrawLine(r, mPosition.x, mPosition.y, mPosition.x, mPosition.y + mHeight);
    SDL_RenderDrawLine(r, mPosition.x, mPosition.y + mHeight, mPosition.x + mWidth, mPosition.y + mHeight);
    SDL_RenderDrawLine(r, mPosition.x + mWidth, mPosition.y + mHeight, mPosition.x + mWidth, mPosition.y);
    SDL_RenderDrawLine(r, mPosition.x + mWidth, mPosition.y, mPosition.x, mPosition.y);
}
