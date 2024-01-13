#include <iostream>
#include <vector>

/**
 * @brief Function to display the current state of the Connect Four board.
 *
 * @param board - 2D vector representing the game board
 * @param rows - number of rows in the board
 * @param columns - number of columns in the board
 */
void displayBoard(const std::vector<std::vector<char>>& board, int rows, int columns) {
    // Display the board with the origin (0,0) at the bottom-left
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            std::cout << board[rows - i - 1][j] << " ";
        }
        std::cout << "\n";
    }

    // Display column indices
    for (int i = 0; i < columns; ++i) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

/**
 * @brief Function to check if a player has won the Connect Four game.
 *
 * @param board - 2D vector representing the game board
 * @param player - symbol of the current player ('X' or 'O')
 * @param rows - number of rows in the board
 * @param columns - number of columns in the board
 * @return bool - true if the player has won, false otherwise
 */
bool checkWin(const std::vector<std::vector<char>>& board, char player, int rows, int columns) {
    // Check horizontal connections
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns - 3; ++j) {
            if (board[i][j] == player &&
                board[i][j + 1] == player &&
                board[i][j + 2] == player &&
                board[i][j + 3] == player) {
                return true;
            }
        }
    }

    // Check vertical connections
    for (int i = 0; i < rows - 3; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] == player &&
                board[i + 1][j] == player &&
                board[i + 2][j] == player &&
                board[i + 3][j] == player) {
                return true;
            }
        }
    }

    // Check diagonal connections (top-left to bottom-right)
    for (int i = 0; i < rows - 3; ++i) {
        for (int j = 0; j < columns - 3; ++j) {
            if (board[i][j] == player &&
                board[i + 1][j + 1] == player &&
                board[i + 2][j + 2] == player &&
                board[i + 3][j + 3] == player) {
                return true;
            }
        }
    }

    // Check diagonal connections (top-right to bottom-left)
    for (int i = 0; i < rows - 3; ++i) {
        for (int j = 3; j < columns; ++j) {
            if (board[i][j] == player &&
                board[i + 1][j - 1] == player &&
                board[i + 2][j - 2] == player &&
                board[i + 3][j - 3] == player) {
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief Function to play the Connect Four game.
 *
 * @param rows - number of rows in the board
 * @param columns - number of columns in the board
 */
void playConnectFour(int rows, int columns) {
    std::vector<std::vector<char>> board(rows, std::vector<char>(columns, ' '));
    int moves = 0;
    char currentPlayer = 'X';

    while (true) {
        displayBoard(board, rows, columns);

        // Get player move
        int col;
        do {
            std::cout << "\nPlayer " << currentPlayer << ", enter column (0-" << columns - 1 << "): ";
            std::cin >> col;
        } while (col < 0 || col >= columns || board[rows - 1][col] != ' ');

        // Make the move
        for (int i = 0; i < rows; ++i) {
            if (board[i][col] == ' ') {
                board[i][col] = currentPlayer;
                ++moves;
                break;
            }
        }

        // Check for a win
        if (checkWin(board, currentPlayer, rows, columns)) {
            displayBoard(board, rows, columns);
            std::cout << "\nPlayer " << currentPlayer << " wins!\n";
            break;
        }

        // Check for a draw
        if (moves == rows * columns) {
            displayBoard(board, rows, columns);
            std::cout << "\nIt's a draw!\n";
            break;
        }

        // Switch players
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

int main() {
    std::cout << "Welcome to 'Connect Four' game!\n";
    std::cout << "This is a game for two players, that can be played on a custom board.\n";
    std::cout << "Good Luck!\n\n";

    // Get user input for the number of rows and columns
    int rows, columns;
    std::cout << "Enter the number of rows: ";
    std::cin >> rows;
    std::cout << "Enter the number of columns: ";
    std::cin >> columns;

    // Play Connect Four
    playConnectFour(rows, columns);

    return 0;
}
