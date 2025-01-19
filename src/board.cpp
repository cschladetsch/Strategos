#include "board.hpp"
#include <ncurses.h>

void Board::initialize() {
    for (auto& row : grid) {
        row.fill("."); // Initialize all cells
    }
    grid[0][0] = "K";           // Player 1's King
    grid[size - 1][size - 1] = "K"; // Player 2's King
}

void Board::display() const {
    clear(); // Clear the screen using ncurses

    // Display column labels
    mvprintw(0, 4, "  A B C D E F G H I J K");

    // Display rows and cells
    for (int y = 0; y < size; ++y) {
        mvprintw(y + 1, 0, "%2d ", y + 1); // Row label
        for (int x = 0; x < size; ++x) {
            if (x == cursor_x && y == cursor_y) {
                attron(A_REVERSE); // Highlight cursor
                mvprintw(y + 1, 4 + x * 2, "%s", grid[y][x].c_str());
                attroff(A_REVERSE);
            } else {
                mvprintw(y + 1, 4 + x * 2, "%s", grid[y][x].c_str());
            }
        }
    }

    refresh(); // Refresh the screen
}

void Board::moveCursor(char direction) {
    switch (direction) {
        case 'w': if (cursor_y > 0) --cursor_y; break; // Move up
        case 's': if (cursor_y < size - 1) ++cursor_y; break; // Move down
        case 'a': if (cursor_x > 0) --cursor_x; break; // Move left
        case 'd': if (cursor_x < size - 1) ++cursor_x; break; // Move right
    }
}

void Board::placeStone() {
    if (grid[cursor_y][cursor_x] == ".") {
        grid[cursor_y][cursor_x] = "S"; // Place stone
    } else {
        mvprintw(size + 2, 0, "Invalid move: Cell is already occupied.");
    }
}

