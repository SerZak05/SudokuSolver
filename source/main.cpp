#include <iostream>
#include <SDL.h>
#include <fstream>
#include "texture.h"
#include "button_board.h"
#include "board_display.h"
#include "common_textures.h"
#include "solver.h"

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

Board inputBoard(std::string fileName) {
    std::ifstream input(fileName);
    Board res;
    for (int i = 0; i < 9; ++i) {
        std::string row;
        std::getline(input, row);
        if (row.size() != 9) {
            std::cerr << "Incorrect row size!" << std::endl;
            std::cerr << "Row " << i + '0' << " size: " << row.size() + '0' << std::endl;
            return Board();
        }
        for (int j = 0; j < 9; ++j) {
            if (std::isspace(row[j])) continue;

            if (!std::isdigit(row[j])) {
                std::cerr << "Incorrect input format!" << std::endl;
                std::cerr << "Found: \'" << row[j] << "\'" << std::endl;
                return Board();
            } else
                res.set(row[j] - '0', i, j);
        }
    }
    return res;
}

int main(int argc, char* argv[]) {
    if (!init()) {
        std::cerr << "Init failed!" << std::endl;
        return -1;
    }

    ButtonBoard bb(10, 10, 540, 540);
    BoardDisplay startBoardDisplay(550, 10, 243, 243);
    BoardDisplay solutionBoardDisplay(550, 253, 243, 243);

    //Additional parameters
    if (argc > 1) {
        std::string param(argv[1]);
        if (param == "--file" || param == "-f") { //File input
            if (argc > 2) {
                std::string fileName(argv[2]);
                Board givenBoard = inputBoard(fileName);
                //Setting button board accordingly
                for (int i = 0; i < 9; ++i) {
                    for (int j = 0; j < 9; ++j) {
                        bb.setNumber(givenBoard.get(i, j), i, j);
                    }
                }
            }
        }
    }

    std::ofstream log("sudoku.log");

    SDL_Event e;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                SDL_KeyboardEvent keyboardEvent = e.key;
                if (e.key.keysym.sym == SDLK_SPACE) {
                    // Solving
                    startBoardDisplay.board = bb.getBoard();
                    Solver solver;
                    solver.setStartBoard(bb.getBoard());
                    auto solutions = solver.solve();
                    std::cout << "Done!" << std::endl;
                    if (solutions.empty()) {
                        std::cout << "No solutions found" << std::endl;
                        solutionBoardDisplay.board = Board();
                    }
                    else {
                        solutionBoardDisplay.board = solutions.front();
                        log << solutions.front().toString() << std::endl;
                    }
                }
                break;
            default:
                bb.handleEvent(&e);
            }
        }
        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
        SDL_RenderClear(renderer);
        bb.render(renderer);
        startBoardDisplay.render(renderer);
        solutionBoardDisplay.render(renderer);
        SDL_RenderPresent(renderer);
    }

    close();
    return 0;
}