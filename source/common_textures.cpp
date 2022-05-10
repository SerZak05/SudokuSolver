#include "common_textures.h"

Texture CommonTextures::numbers[10];

void CommonTextures::loadTextures(SDL_Renderer* r) {
    // Initializing textures for numbers on buttons
    for (int i = 1; i <= 9; ++i) {
        numbers[i] = Texture();
        std::string path = "numberTextures/number_";
        path += '0' + i;
        path += ".png";
        numbers[i].loadFromFile(r, path);
    }
}
