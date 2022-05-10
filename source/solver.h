#pragma once
#include <vector>
#include "board.h"


// Sudoku solver
class Solver {
public:
    //Sets board that is given by the user to solve
    void setStartBoard(const Board&);
    //Generates solutions and returns them
    std::vector<Board> solve();
private:
    Board startBoard;
    //Recursive functions to solve
    void solve(const Board&, std::vector<Board>& solutions);
};