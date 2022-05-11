#pragma once
#include <SDL.h>
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
    Button();
    Button(int x, int y, int width, int height);

    //Sets top left position
    void setPosition(int x, int y);

    void setNumber(int num);

    //Gets top left position
    inline SDL_Point getPosition() const { return mPosition; }

    //Handles mouse event
    void handleEvent(const SDL_Event* e);

    void render(SDL_Renderer* r);

    //Returns number displayed on the button (0, if none)
    inline int getNumber() const { return mNum; }
private:
    //Top left position
    SDL_Point mPosition;

    //Currently used global sprite
    ButtonState mCurrentState;

    //Current number on a button (0 for empty)
    int mNum = 0;

    int mWidth, mHeight;
};