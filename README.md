# SudokuSolver
## Program for solving sudoku puzzles
### Compiling:
This program requires *SDL2* and *SDL Image* libraries to compile. You can find them here: http://libsdl.org/download-2.0.php and http://www.libsdl.org/projects/SDL_image/.
### Usage:
Input board is on the left. Click on the buttons:
- *LMB* to increment a number on the board
- *RMB* to decrement a number on the board
- *MMB* to erase number on the board

After you are finished pressing buttons, press *SPACE* to start solving sudoku. The given board will be shown in the right upper corner. This process can last from a couple of seconds up to a couple of minutes on a empty board and make the program unresponsive. One of the possible solutions will be shown in the right lower corner. All of the solutions will be written in *sudoku_solutions.out* file.

### Executing from console
The program can be executed from console. There are two options available:
 - **-f** or **--file** + *fileName* enables input from a text file. Program will read sudoku board from a file and initialize the button board accordingly.
 - **-l** or **--log** enables logging into *sudoku.log* file
