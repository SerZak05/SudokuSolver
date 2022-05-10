#include "board.h"

Board::Board() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j] = 0;
        }
    }
}

int Board::get(int i, int j) const {
    return board[i][j];
}

void Board::set(int val, int i, int j) {
    if (val < 0 || val > 9) {
        std::cerr << "Board::set: invalid number" << std::endl;
        return;
    }
    board[i][j] = val;
}

bool Board::isEmpty(int i, int j) const {
    return board[i][j] == 0;
}
