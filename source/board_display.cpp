#include "board_display.h"
#include "common_textures.h"

BoardDisplay::BoardDisplay(int x, int y, int width, int height) : mWidth(width), mHeight(height) {
    mPosition.x = x;
    mPosition.y = y;
}

void BoardDisplay::render(SDL_Renderer* r) {
    int stepX = mWidth / 9;
    int stepY = mHeight / 9;
    //Drawing numbers
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int num = board.get(i, j);
            if (num != 0) {
                Texture& numberTexture = CommonTextures::numbers[num];
                numberTexture.render(r, mPosition.x + stepX * i, mPosition.y + stepY * j,
                    stepX, stepY);
            }
        }
    }

    //Drawing 3x3 squares
    SDL_SetRenderDrawColor(r, 50, 50, 50, 255);
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            //Left upper corner
            SDL_Point startPos;
            startPos.x = mPosition.x + stepX * i;
            startPos.y = mPosition.y + stepY * j;
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
