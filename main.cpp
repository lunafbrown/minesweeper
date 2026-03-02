#include <iostream>
#include <algorithm>
#include <cstdlib> // for rand, srand
#include <ctime>   // for time
using namespace std;

// Initialize
const int ROWS = 5;
const int COLS = 5;

int board[ROWS][COLS] = {0}; // table that has minesweeper numbers
int table[ROWS][COLS] = {0}; // table that marks the mines
int printed[ROWS][COLS] = {0}; // table that is visible to the player

int ERR = 0;

void printBoard(int info, int tCol, int tRow) {
    if (info == 0) {
        // Seed random number generator
        srand(time(NULL));
    
        // Place exactly 4 random 1's
        int placed = 0;
        while (placed < 4) {
            int r = rand() % ROWS;
            int c = rand() % COLS;
    
            if (table[r][c] == 0) { // only place if it's empty
                table[r][c] = 1;
                placed++;
            }
        }
        
        // adjust the numbers in the "board" minesweeperly
        int dr[8] = {-1, -1, -1,  0, 0,  1, 1, 1}; // directions
        int dc[8] = {-1,  0,  1, -1, 1, -1, 0, 1};
        
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                if (table[r][c] == 1) {
                    // If this square is a mine, mark as 9
                    board[r][c] = 9;
                } else {
                    int count = 0;
                    // Check all 8 neighbors
                    for (int k = 0; k < 8; k++) {
                        int nr = r + dr[k];
                        int nc = c + dc[k];
                        // Stay inside bounds
                        if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS) {
                            if (table[nr][nc] == 1) {
                                count++;
                            }
                        }
                    }
                    board[r][c] = count;
                }
            }
        }
    }

    // Print the table
    cout << "  A B C D E"; // show columns
    cout << endl; // new line
    for (int i = 0; i < ROWS; i++) {
        cout << i + 1 << " "; // print the row + 1
        for (int j = 0; j < COLS; j++) {
            if (info == 0) {
                cout << "█ "; // print empty squares, spawning the initial board
            }
            else {
                if (i == tRow && j == tCol) { // reveal tile
                    printed[i][j] = board[i][j];
                }
                if (printed[i][j] == -1) {
                    cout << "█ ";
                }
                else if (printed[i][j] == 9) {
                    cout << "* ";
                    ERR = 1;
                }
                else {
                    cout << printed[i][j] << " ";
                }
            }
        }
        cout << endl; // new line after each row
    }
    
    bool arraysAreEqual = true;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (printed[i][j] != board[i][j]) {
                if (printed[i][j] != -1 || board[i][j] != 9) {
                    arraysAreEqual = false;
                    break; // exit inner loop early
                }
            }
        }
        if (!arraysAreEqual) break; // exit outer loop early
    }
    
    if (arraysAreEqual) {
        ERR = 2;
    }
}

// minesweeper
int main()
{
    std::fill(&printed[0][0], &printed[0][0] + ROWS*COLS, -1);
    
    std::cout << "Welcome to Minesweeper" << std::endl << "Press Enter to begin..." << std::endl;
    std::cin.get(); // Waits for the user to press Enter
    
    string input;
    std::cout << "Minesweeper" << std::endl;
    printBoard(0, 0, 0);
    while (true) {
        cin >> input;
        
        // allow quitting
            if (input == "q" || input == "quit") {
                cout << "Goodbye!" << endl;
                break; 
            }
        // Check length first
        if (input.length() == 2) {
            char letter = input[0];
            char number = input[1];
    
            // Check first char is between 'a' and 'e'
            if (letter >= 'a' && letter <= 'e') {
                // Check second char is between '1' and '5'
                if (number >= '1' && number <= '5') {
                    int row = (letter - 'a');
                    int col = (number - '0') - 1;
                    printBoard(1, row, col);
                }
                else {
                    cout << "Invalid input." << endl;
                }
            }
            else {
                cout << "Invalid input." << endl;
            }
        }
        else {
            cout << "Invalid input." << endl;
        }
        if (ERR == 1 || ERR == 2) {
           break;
        }
    }
    if (ERR == 1) {
        cout << endl << "You Lose!" << endl;
    }
    else if (ERR == 2) {
        cout << endl << "You Win!" << endl;
    }
    return 0;
}