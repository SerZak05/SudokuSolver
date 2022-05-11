#include "button.h"
#include "texture.h"
#include "common_textures.h"
#include <iostream>

Button::Button() : mWidth(0), mHeight(0), mCurrentState(BUTTON_MOUSE_OUT) {
    mPosition.x = 0;
    mPosition.y = 0;
}

Button::Button(int x, int y, int width, int height) : mWidth(width), mHeight(height) {
    mPosition.x = x;
    mPosition.y = y;
    mCurrentState = BUTTON_MOUSE_OUT;
}

void Button::setPosition(int x, int y) {
    mPosition.x = x;
    mPosition.y = y;
}

void Button::setNumber(int num) {
    if (num >= 0 && num < 10)
        mNum = num;
}

void Button::handleEvent(const SDL_Event* e) {
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);
        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if (x < mPosition.x || x > mPosition.x + mWidth || y < mPosition.y || y > mPosition.y + mHeight)
            mCurrentState = BUTTON_MOUSE_OUT;
        else {
            //Set mouse over sprite
            switch (e->type)
            {
            case SDL_MOUSEMOTION:
                mCurrentState = BUTTON_MOUSE_OVER_MOTION;
                break;

            case SDL_MOUSEBUTTONDOWN:
                mCurrentState = BUTTON_MOUSE_DOWN;
                break;

            case SDL_MOUSEBUTTONUP:
                mCurrentState = BUTTON_MOUSE_OVER_MOTION;
                //Updating number
                SDL_MouseButtonEvent mouseEvent = e->button;
                if (mouseEvent.button == SDL_BUTTON_LEFT) {
                    mNum++;
                    if (mNum > 9)
                        mNum = 0;
                }
                else if (mouseEvent.button == SDL_BUTTON_RIGHT) {
                    mNum--;
                    if (mNum < 0)
                        mNum = 9;
                }
                else if (mouseEvent.button == SDL_BUTTON_MIDDLE) {
                    mNum = 0;
                }
                break;
            }
        }
    }
}

void Button::render(SDL_Renderer* r) {
    // std::cout << mWidth << std::endl;
    switch (mCurrentState) {
    case BUTTON_MOUSE_OUT:
        SDL_SetRenderDrawColor(r, 230, 230, 230, 255);
        break;
    case BUTTON_MOUSE_OVER_MOTION:
        SDL_SetRenderDrawColor(r, 200, 200, 200, 255);
        break;
    case BUTTON_MOUSE_DOWN:
        SDL_SetRenderDrawColor(r, 100, 100, 100, 255);
        break;
    default:
        SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
    }

    SDL_Rect buttonRect = { mPosition.x, mPosition.y, mWidth, mHeight };
    SDL_RenderFillRect(r, &buttonRect);
    SDL_RenderDrawRect(r, &buttonRect);

    //drawing number on top
    if (mNum != 0) {
        Texture& numberTexture = CommonTextures::numbers[mNum];
        numberTexture.render(r, mPosition.x + 5, mPosition.y + 5, mWidth - 10, mHeight - 10);
    }
}
