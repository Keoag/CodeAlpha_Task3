#include <iostream>
#include <vector>

// Size of the Sudoku grid
const int N = 9;

// Function to print the Sudoku grid
void printGrid(const std::vector<std::vector<int>>& grid) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Function to check if a number can be placed in a specific cell
bool isSafe(const std::vector<std::vector<int>>& grid, int row, int col, int num) {
    // Check if the number is not present in the current row and column
    for (int i = 0; i < N; ++i) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    // Check if the number is not present in the 3x3 subgrid
    int subgridStartRow = row - row % 3;
    int subgridStartCol = col - col % 3;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[subgridStartRow + i][subgridStartCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to find an empty cell in the Sudoku grid
bool findEmptyCell(const std::vector<std::vector<int>>& grid, int& row, int& col) {
    for (row = 0; row < N; ++row) {
        for (col = 0; col < N; ++col) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Sudoku solver using backtracking
bool solveSudoku(std::vector<std::vector<int>>& grid) {
    int row, col;

    // If there is no empty cell, the Sudoku is solved
    if (!findEmptyCell(grid, row, col)) {
        return true;
    }

    // Try placing numbers from 1 to 9
    for (int num = 1; num <= 9; ++num) {
        // Check if the current number can be placed in the cell
        if (isSafe(grid, row, col, num)) {
            // Place the number in the cell
            grid[row][col] = num;

            // Recursively solve the remaining puzzle
            if (solveSudoku(grid)) {
                return true;
            }

            // If placing the current number leads to an invalid solution, backtrack
            grid[row][col] = 0;
        }
    }

    // If no number can be placed, backtrack
    return false;
}

int main() {
    std::vector<std::vector<int>> sudokuGrid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    std::cout << "Sudoku Puzzle:\n";
    printGrid(sudokuGrid);

    if (solveSudoku(sudokuGrid)) {
        std::cout << "\nSolved Sudoku:\n";
        printGrid(sudokuGrid);
    }
    else {
        std::cout << "\nNo solution exists.\n";
    }

    return 0;
}
