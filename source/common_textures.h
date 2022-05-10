#pragma once
#include <SDL.h>
#include "texture.h"

namespace CommonTextures {
    //Textures for numbers
    extern Texture numbers[];
    void loadTextures(SDL_Renderer*);
}