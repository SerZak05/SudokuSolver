#include <iostream>
#include <SDL.h>
#include "texture.h"
#include "button_board.h"
#include "board_display.h"
#include "common_textures.h"

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

    CommonTextures::loadTextures(renderer);

    return true;
}

// Closing SDL library
void close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (!init()) {
        std::cerr << "Init failed!" << std::endl;
        return -1;
    }

    ButtonBoard bb(10, 10, 540, 540);
    BoardDisplay bd(550, 10, 243, 243);

    SDL_Event e;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                // Solve //
                // SDL_KeyboardEvent keyboardEvent = e.key;
                // if (e.key.keysym.sym == SDLK_)
                bd.board = bb.getBoard();
                break;
            default:
                bb.handleEvent(&e);
            }
        }
        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
        SDL_RenderClear(renderer);
        bb.render(renderer);
        bd.render(renderer);
        SDL_RenderPresent(renderer);
    }

    close();
    return 0;
}