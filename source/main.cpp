#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "button_board.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


// Initialising SDL library
bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL_Init failed!" << std::endl;
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        std::cerr << "IMG_Init PNG failed!" << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Sudoku solver",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cerr << "Could not create a window!" << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cerr << "Could not create a renderer!" << std::endl;
        return false;
    }

    // Initializing textures for numbers on buttons
    for (int i = 1; i <= 9; ++i) {
        Button::numberTextures[i] = Texture();
        std::string path = "numberTextures/number_";
        path += '0' + i;
        path += ".png";
        Button::numberTextures[i].loadFromFile(renderer, path);
    }

    return true;
}

// Closing SDL library
void close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    SDL_Quit();
    IMG_Quit();
}

int main(int argc, char* argv[]) {
    if (!init()) {
        std::cerr << "Init failed!" << std::endl;
        return -1;
    }

    ButtonBoard bb(10, 10, 540, 540);

    SDL_Event e;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                // Solve
                break;
            default:
                bb.handleEvent(&e);
            }
        }
        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
        SDL_RenderClear(renderer);
        bb.render(renderer);
        SDL_RenderPresent(renderer);
    }

    close();
    return 0;
}