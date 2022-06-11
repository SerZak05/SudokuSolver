#include "solver.h"
#include <set>
#include <map>
#include <utility>

int getSquareIndex(int i, int j) {
    return i / 3 + (j / 3) * 3;
}

std::pair<int, int> getIndexFromSquare(int sqInd) {
    return { (sqInd % 3) * 3, (sqInd / 3) * 3 };
}

void Solver::setStartBoard(const Board& b) {
    startBoard = b;
}

std::vector<Board> Solver::solve(std::ostream& log) {
    if (logging)
        log << "===Beginning solving...===" << std::endl;
    std::vector<Board> res;
    solve(startBoard, res, log);
    if (logging) {
        log << "===Stopped solving===" << std::endl;
        log << "In total " << res.size() << " solutions were found." << std::endl;
    }
    return res;
}

void Solver::solve(const Board& b, std::vector<Board>& solutions, std::ostream& log) {
    if (logging)
        log << "Solving board:\n" << b.toString() << std::endl;
    //Map of rows, columns and 3x3 squares mached with a set of numbers NOT in it
    std::set<int> rows[9], cols[9], squares[9];
    //Initiallizing sets
    for (int i = 0; i < 9; ++i) {
        for (int num = 1; num <= 9; ++num) {
            rows[i].insert(num);
            cols[i].insert(num);
            squares[i].insert(num);
        }
    }

    //Ordered set of pairs (number of numbers NOT in a row/column/square, row/column/square)
    //The first pair is the row/column/square with the MOST numbers in it
    //Therefore, there are less options to sort through
    std::set<std::pair<int, int>> rows_ord, cols_ord, squares_ord;
    /*Squares are indexed like:
      012
      345
      678
     */

    //Counting numbers
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (b.isEmpty(i, j))
                continue;
            int num = b.get(i, j);
            if (rows[i].find(num) == rows[i].end()) {
                //We already found this number in this row!
                if (logging)
                    log << "Number " << num << " is already in row " << i << std::endl;
                return;
            }
            rows[i].erase(num);

            if (cols[j].find(num) == cols[j].end()) {
                //We already found this number in this column!
                if (logging)
                    log << "Number " << num << " is already in column " << j << std::endl;
                return;
            }
            cols[j].erase(num);

            int sqInd = getSquareIndex(i, j);
            if (squares[sqInd].find(num) == squares[sqInd].end()) {
                //We already found this number in this square!
                if (logging)
                    log << "Number " << num << " is already in square " << sqInd << std::endl;
                return;
            }
            squares[sqInd].erase(num);
        }
    }

    //Initializing oredered sets
    for (int i = 0; i < 9; ++i) {
        rows_ord.insert({ rows[i].size(), i });
        cols_ord.insert({ cols[i].size(), i });
        squares_ord.insert({ squares[i].size(), i });
    }

    Board currBoard = b;

    bool uncertain = false; //becomes true, if there are more than one possible solutions
    struct UncertainPosition {
        int i, j; //empty position
        std::set<int> numbers; //possible numbers
        int operator<(const UncertainPosition& other) const {
            return numbers.size() < other.numbers.size();
        }
    };

    //Stores uncertain positions for row, colomn and square that we find
    std::set<UncertainPosition> uncertainPositions;

    //while not solved and we could make a decision
    while (!rows_ord.empty() && !cols_ord.empty() && !squares_ord.empty() && !uncertain) {
        bool uncertainRow = false, uncertainCol = false, uncertainSquare = false;
        uncertainPositions.clear();

        //Solving rows
        {
            std::pair<int, int> min_row = *rows_ord.begin();
            if (min_row.first == 0) {
                //Forgetting about full rows
                rows_ord.erase(min_row);
                if (logging)
                    log << "Row " << min_row.second << " is full." << std::endl;
            }
            else {
                int i = min_row.second;
                //Finding empty space
                int j = 0;
                while (!currBoard.isEmpty(i, j))
                    j++;
                int sqInd = getSquareIndex(i, j);

                //Solving definite places
                if (min_row.first == 1) {
                    rows_ord.erase(min_row);

                    //Updating the board and sets
                    int num = *rows[i].begin(); //the last number to place in this row
                    if (logging)
                        log << "Filling (" << i << ' ' << j << ") with " << num << std::endl;

                    if (cols[j].find(num) == cols[j].end()) {
                        //The only solution is incorrect
                        if (logging)
                            log << num << " is already in column!" << std::endl;
                        return;
                    }
                    if (squares[sqInd].find(num) == squares[sqInd].end()) {
                        //The only solution is incorrect
                        if (logging)
                            log << num << " is already in square!" << std::endl;
                        return;
                    }
                    //Updating
                    cols_ord.erase({ cols[j].size(), j });
                    squares_ord.erase({ squares[sqInd].size(), sqInd });

                    currBoard.set(num, i, j);
                    cols[j].erase(num);
                    squares[sqInd].erase(num);

                    cols_ord.insert({ cols[j].size(), j });
                    squares_ord.insert({ squares[sqInd].size(), sqInd });
                }
                else {
                    //Every row is missing more than 1 number - uncertainty
                    uncertainRow = true;
                    uncertainPositions.insert({ i, j, rows[i] });
                }
            }
        }

        //Solving squares
        {
            std::pair<int, int> min_square = *squares_ord.begin();
            if (min_square.first == 0) {
                //Forgetting about full squares
                squares_ord.erase(min_square);
                if (logging)
                    log << "Square " << min_square.second << " is full." << std::endl;
            }
            else {
                int sqInd = min_square.second;
                //Finding empty space
                int i, j;
                auto leftUpperCorner = getIndexFromSquare(sqInd);
                for (i = leftUpperCorner.first; i < leftUpperCorner.first + 3; ++i) {
                    bool found = false;
                    for (j = leftUpperCorner.second; j < leftUpperCorner.second + 3; ++j)
                        if (currBoard.isEmpty(i, j)) {
                            found = true;
                            break;
                        }
                    if (found)
                        break;
                }

                if (min_square.first == 1) { 
                    squares_ord.erase(min_square);

                    //Updating the board and sets
                    int num = *squares[sqInd].begin(); //the last number to place in this column
                    if (logging)
                        log << "Filling (" << i << ' ' << j << ") with " << num << std::endl;

                    if (rows[i].find(num) == rows[i].end()) {
                        //The only solution is incorrect
                        if (logging)
                            log << num << " is already in row!" << std::endl;
                        return;
                    }
                    if (cols[j].find(num) == cols[j].end()) {
                        //The only solution is incorrect
                        if (logging)
                            log << num << " is already in column!" << std::endl;
                        return;
                    }
                    //Updating
                    rows_ord.erase({ rows[i].size(), i });
                    cols_ord.erase({ cols[j].size(), j });

                    currBoard.set(num, i, j);
                    rows[i].erase(num);
                    cols[j].erase(num);

                    rows_ord.insert({ rows[i].size(), i });
                    cols_ord.insert({ cols[j].size(), j });
                }
                else {
                    //Every square is missing more than 1 number - uncertainty
                    uncertainSquare = true;
                    uncertainPositions.insert({ i, j, squares[sqInd] });
                }
            }
        }

        //Solving columns
        {
            std::pair<int, int> min_col = *cols_ord.begin();
            if (min_col.first == 0) {
                //Forgetting about full columns
                cols_ord.erase(min_col);
                if (logging)
                    log << "Column " << min_col.second << " is full." << std::endl;
            }
            else {
                int j = min_col.second;
                //Finding empty space
                int i = 0;
                while (!currBoard.isEmpty(i, j))
                    i++;
                int sqInd = getSquareIndex(i, j);

                if (min_col.first == 1) {
                    //Only one solution is possible
                    cols_ord.erase(min_col);

                    //Updating the board and sets
                    int num = *cols[j].begin(); //the last number to place in this column
                    if (logging)
                        log << "Filling (" << i << ' ' << j << ") with " << num << std::endl;

                    if (rows[i].find(num) == rows[i].end()) {
                        //The only solution is incorrect
                        if (logging)
                            log << num << " is already in row!" << std::endl;
                        return;
                    }
                    if (squares[sqInd].find(num) == squares[sqInd].end()) {
                        //The only solution is incorrect
                        if (logging)
                            log << num << " is already in square!" << std::endl;
                        return;
                    }
                    //Updating
                    rows_ord.erase({ rows[i].size(), i });
                    squares_ord.erase({ squares[sqInd].size(), sqInd });

                    currBoard.set(num, i, j);
                    rows[i].erase(num);
                    squares[sqInd].erase(num);

                    rows_ord.insert({ rows[i].size(), i });
                    squares_ord.insert({ squares[sqInd].size(), sqInd });
                }
                else {
                    //Every column is missing more than 1 number - uncertainty
                    uncertainCol = true;
                    uncertainPositions.insert({ i, j, cols[j] });
                }
            }
        }

        if (uncertainRow && uncertainCol && uncertainSquare) {
            //Should iterate through possibilities after the loop
            uncertain = true;
            if (logging)
                log << "No more certain filling!" << std::endl;
        }
    }

    /* after the loop:
     * 1. currBoard is full, or
     * 2. we've encountered at least one uncertainty,
     * so we recursively should call this function on every possibility
     */

    if (!uncertain) {
        //We solved this board
        solutions.push_back(currBoard);
        if (logging)
            log << "Board solved:\n" << currBoard.toString() << std::endl;
    }
    else {
        //Taking uncertain position with the least amount of possible numbers available
        UncertainPosition pos = *uncertainPositions.begin();
        for (int num : pos.numbers) {
            if (logging)
                log << "Trying number " << num <<
                " on the position (" << pos.i << ' ' << pos.j << ")" << std::endl;
            currBoard.set(num, pos.i, pos.j);
            solve(currBoard, solutions, log);
        }
    }
}
