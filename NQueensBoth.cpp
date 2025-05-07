#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Utility to print the board
void printBoard(const vector<string>& board) {
    for (const string& row : board) {
        cout << row << endl;
    }
    cout << endl;
}

// BACKTRACKING - Generate all possible solutions
void solveNQueensBacktracking(int row, int n, vector<string>& board, vector<vector<string>>& solutions) {
    if (row == n) {
        solutions.push_back(board);
        return;
    }

    for (int col = 0; col < n; col++) {
        bool safe = true;
        for (int prevRow = 0; prevRow < row; prevRow++) {
            int prevCol = -1;
            for (int k = 0; k < n; k++) {
                if (board[prevRow][k] == 'Q') {
                    prevCol = k;
                    break;
                }
            }
            if (prevCol == col || abs(prevCol - col) == abs(prevRow - row)) {
                safe = false;
                break;
            }
        }

        if (safe) {
            board[row][col] = 'Q';
            solveNQueensBacktracking(row + 1, n, board, solutions);
            board[row][col] = '.';
        }
    }
}

// BRANCH AND BOUND - Stop at first valid solution
bool solveOneNQueensBranchAndBound(int row, int n, vector<string>& board,
                                   vector<int>& left, vector<int>& upperDiag, vector<int>& lowerDiag) {
    if (row == n) {
        printBoard(board);
        return true;
    }

    for (int col = 0; col < n; col++) {
        if (!left[col] && !upperDiag[row + col] && !lowerDiag[n - 1 + col - row]) {
            board[row][col] = 'Q';
            left[col] = upperDiag[row + col] = lowerDiag[n - 1 + col - row] = 1;

            if (solveOneNQueensBranchAndBound(row + 1, n, board, left, upperDiag, lowerDiag))
                return true;

            board[row][col] = '.';
            left[col] = upperDiag[row + col] = lowerDiag[n - 1 + col - row] = 0;
        }
    }
    return false;
}

int main() {
    int n;
    cout << "Enter value of n: ";
    cin >> n;

    vector<string> board(n, string(n, '.'));

    // Part 1: Backtracking - all solutions
    vector<vector<string>> allSolutions;
    solveNQueensBacktracking(0, n, board, allSolutions);

    cout << "\nAll possible solutions using Backtracking:\n";
    for (const auto& solution : allSolutions) {
        printBoard(solution);
    }

    // Part 2: Branch and Bound - only one optimal solution
    vector<int> left(n, 0), upperDiag(2 * n - 1, 0), lowerDiag(2 * n - 1, 0);
    vector<string> boardOptimal(n, string(n, '.'));

    cout << "\nOne optimal solution using Branch and Bound:\n";
    if (!solveOneNQueensBranchAndBound(0, n, boardOptimal, left, upperDiag, lowerDiag)) {
        cout << "No solution exists.\n";
    }

    return 0;
}

