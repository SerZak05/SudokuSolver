#pragma once
#include <iostream>

// Data class for a sudoku board

class Board {
public:
    Board();
    int get(int i, int j) const;
    void set(int val, int i, int j);
    bool isEmpty(int i, int j) const;
private:
    // Array for numbers on the board, 0 for empty space
    int board[9][9];
};