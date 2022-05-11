#pragma once
#include <vector>
#include "board.h"


// Sudoku solver
class Solver {
public:
    //Sets board that is given by the user to solve
    void setStartBoard(const Board&);
    //Generates solutions and returns them
    std::vector<Board> solve(std::ostream& log);

    //If true starts to write into the log stream provided
    bool logging = false;
private:
    Board startBoard;
    //Recursive functions to solve
    void solve(const Board&, std::vector<Board>& solutions, std::ostream& log);
};