#include <iostream>
#include <vector>
#include <string>

/**
 * @brief Wrapper Function to print a given message to the console.
 *
 * @param message The message to be printed.
 */
void print(const std::string& message) {
    std::cout << message;
}

/**
 * @brief Class (Model) representing the 'Connect Four' game board.
 */
class Board {
private:
    std::vector<std::vector<char>> board; // 2D vector representing the game board.
    int rows, columns; // Number of rows and columns of the game board.
    const int WIN_LENGTH = 3; // Length of the line needed to win the game (0->3 = 4).

public:
    /**
     * @brief Construct a new Board object.
     *
     * @param r Number of rows for the board.
     * @param c Number of columns for the board.
     */
    Board(int r, int c) : rows(r), columns(c), board(r, std::vector<char>(c, ' ')) {}

    /**
     * @brief Check if a cell in the board is empty.
     *
     * @param row Row of the cell.
     * @param col Column of the cell.
     * @return true If the cell is empty.
     * @return false If the cell is not empty.
     */
    bool isCellEmpty(int row, int col) const { return board[row][col] == ' '; }

    /**
     * @brief Set the cell at the given row and column to the player's symbol.
     *
     * @param row Row of the cell.
     * @param col Column of the cell.
     * @param player The player's symbol.
     */
    void setCell(int row, int col, char player) { board[row][col] = player; }

    /**
     * @brief Get the number of rows of the board.
     *
     * @return int Number of rows.
     */
    int getRows() const { return rows; }

    /**
     * @brief Get the number of columns of the board.
     *
     * @return int Number of columns.
     */
    int getColumns() const { return columns; }

    /**
     * @brief Get the symbol of the cell at the given row and column.
     *
     * @param row Row of the cell.
     * @param col Column of the cell.
     * @return char The symbol of the cell.
     */
    char getCell(int row, int col) const { return board[row][col]; }

    /**
     * @brief Check if the board is full (no empty cells).
     *
     * @return true If the board is full.
     * @return false If there are empty cells.
     */
    bool isFull() const {
        for (const auto& row : board) {
            for (char cell : row) {
                if (cell == ' ') return false;
            }
        }
        return true;
    }
};

/**
 * @brief Class (View) for displaying the game board.
 */
class BoardView {
public:
    /**
     * @brief Display the current state of the board.
     *
     * @param board The game board to be displayed.
     */
    static void displayBoard(const Board& board) {
        std::string output;
        for (int i = 0; i < board.getRows(); ++i) {
            for (int j = 0; j < board.getColumns(); ++j) {
                output += board.getCell(board.getRows() - i - 1, j);
                output += " ";
            }
            output += "\n";
        }
        for (int i = 0; i < board.getColumns(); ++i) {
            output += std::to_string(i) + " ";
        }
        output += "\n";
        print(output);
    }
};

/**
 * @brief Class (Controller) to control the game logic.
 */
class GameController {
private:
    Board &board; // Reference to the game board.
    const int WIN_LENGTH = 3; // Length of the line needed to win the game (0->3 = 4).

public:
    /**
     * @brief Construct a new GameController object.
     *
     * @param b Reference to the game board.
     */
    GameController(Board &b) : board(b) {}

    /**
     * @brief Handle a player's move at the specified column.
     *
     * @param col Column where the move is made.
     * @param player The player's symbol.
     * @return true If the move is successful.
     * @return false If the move is unsuccessful.
     */
    bool makeMove(int col, char player) {
        for (int i =

                0; i < board.getRows(); ++i) {
            if (board.isCellEmpty(i, col)) {
                board.setCell(i, col, player);
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Check if a player has won the game.
     *
     * @param player The player's symbol.
     * @return true If the player has won.
     * @return false If the player has not won.
     */
    bool checkWin(char player) const {
        // Horizontal win check
        for (int i = 0; i < board.getRows(); ++i) {
            for (int j = 0; j < board.getColumns() - WIN_LENGTH + 1; ++j) {
                if (board.getCell(i, j) == player &&
                    board.getCell(i, j + 1) == player &&
                    board.getCell(i, j + 2) == player &&
                    board.getCell(i, j + 3) == player) {
                    return true;
                }
            }
        }

        // Vertical win check
        for (int i = 0; i < board.getRows() - WIN_LENGTH + 1; ++i) {
            for (int j = 0; j < board.getColumns(); ++j) {
                if (board.getCell(i, j) == player &&
                    board.getCell(i + 1, j) == player &&
                    board.getCell(i + 2, j) == player &&
                    board.getCell(i + 3, j) == player) {
                    return true;
                }
            }
        }

        // Diagonal (top-left to bottom-right) win check
        for (int i = 0; i < board.getRows() - WIN_LENGTH + 1; ++i) {
            for (int j = 0; j < board.getColumns() - WIN_LENGTH + 1; ++j) {
                if (board.getCell(i, j) == player &&
                    board.getCell(i + 1, j + 1) == player &&
                    board.getCell(i + 2, j + 2) == player &&
                    board.getCell(i + 3, j + 3) == player) {
                    return true;
                }
            }
        }

        // Diagonal (top-right to bottom-left) win check
        for (int i = 0; i < board.getRows() - WIN_LENGTH + 1; ++i) {
            for (int j = WIN_LENGTH - 1; j < board.getColumns(); ++j) {
                if (board.getCell(i, j) == player &&
                    board.getCell(i + 1, j - 1) == player &&
                    board.getCell(i + 2, j - 2) == player &&
                    board.getCell(i + 3, j - 3) == player) {
                    return true;
                }
            }
        }

        return false;
    }
};

/**
 * @brief Function for the computer's move in the game.
 *
 * @param controller Reference to the game controller.
 * @param columns Number of columns in the game board.
 */
void computerMove(GameController &controller, int columns) {
    srand(time(0));
    int col;
    do {
        col = rand() % columns;
    } while (!controller.makeMove(col, 'O'));
}

/**
 * @brief Main function to play the Connect Four game.
 *
 * @param rows Number of rows in the game board.
 * @param columns Number of columns in the game board.
 * @param vsComputer Boolean to choose between playing against a computer or another player.
 */
void playConnectFour(int rows, int columns, bool vsComputer) {
    Board board(rows, columns);
    GameController controller(board);
    char currentPlayer = 'X';

    while (true) {
        BoardView::displayBoard(board);
        if (!vsComputer || currentPlayer == 'X') {
            int col;
            do {
                std::string message = "\nPlayer " + std::string(1, currentPlayer) + ", enter column (0-" +
                                      std::to_string(columns - 1) + "): ";
                print(message);
                std::cin >> col;
            } while (col < 0 || col >= columns || !controller.makeMove(col, currentPlayer));
        } else {
            computerMove(controller, columns);
        }

        if (controller.checkWin(currentPlayer)) {
            BoardView::displayBoard(board);
            print("\nPlayer " + std::string(1, currentPlayer) + " wins!\n");
            break;
        }

        if (board.isFull()) {
            BoardView::displayBoard(board);
            print("\nIt's a draw!\n");
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

/**
 * @brief Entry point for the 'Connect Four' game application.
 */
int main() {
    int rows, columns;
    bool vsComputer;

    print("Hi! Welcome to the 'Connect Four' game!\n"
          "You can play this game in two modes: against the computer or against a friend.\n"
          "The recommended size is 6x7.\n"
          "Good Luck & Have Fun!\n\n");

    print("Enter the number of rows: ");
    std::cin >> rows;
    print("Enter the number of columns: ");
    std::cin >> columns;
    print("Play against computer? (Type '1' for yes, '0' for no): ");
    std::cin >> vsComputer;

    playConnectFour(rows, columns, vsComputer);
    return 0;
}
