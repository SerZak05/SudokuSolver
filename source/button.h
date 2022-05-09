#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"

enum ButtonState {
    BUTTON_MOUSE_OUT,
    BUTTON_MOUSE_OVER_MOTION,
    BUTTON_MOUSE_DOWN,
    BUTTON_STATES_TOTAL
};

//The mouse button with a number
class Button {
public:
    Button(int x, int y, int width, int height);

    //Sets top left position
    void setPosition(int x, int y);

    //Handles mouse event
    void handleEvent(const SDL_Event* e);

    void render(SDL_Renderer* r);

    //Textures for numbers
    static Texture numberTextures[10];
private:
    //Top left position
    SDL_Point mPosition;

    //Currently used global sprite
    ButtonState mCurrentState;

    //Current number on a button (0 for empty)
    int mNum = 0;

    int mWidth, mHeight;
};