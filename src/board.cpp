#include "board.hpp"
#include <ncurses.h>
#include <spdlog/spdlog.h>

void Board::initialize() {
    spdlog::info("Initializing board...");
    for (auto& row : grid) {
        row.fill("·"); // Centered dot for empty cells
    }
}

void Board::display(const std::map<std::string, int>& pieces, int player_turn) const {
    clear();

    // Display column labels
    mvprintw(0, 4, "  A B C D E F G H I J K");

    // Display rows and cells
    for (int y = 0; y < size; ++y) {
        mvprintw(y + 1, 0, "%2d ", y + 1);
        for (int x = 0; x < size; ++x) {
            if (x == cursor_x && y == cursor_y) {
                attron(A_REVERSE);
                mvprintw(y + 1, 4 + x * 2, "%s", grid[y][x].c_str());
                attroff(A_REVERSE);
            } else if (grid[y][x] == "K" || grid[y][x] == "N" || grid[y][x] == "B" || grid[y][x] == "R") {
                int color_pair = (player_turn == 1) ? 1 : 2;
                attron(COLOR_PAIR(color_pair));
                mvprintw(y + 1, 4 + x * 2, "%s", grid[y][x].c_str());
                attroff(COLOR_PAIR(color_pair));
            } else {
                mvprintw(y + 1, 4 + x * 2, "%s", grid[y][x].c_str());
            }
        }
    }

    // Display available pieces and current player
    mvprintw(size + 2, 0, "Player %d's turn.", player_turn);
    mvprintw(size + 3, 0, "Available pieces:");
    int offset = 20;
    for (const auto& [piece, count] : pieces) {
        mvprintw(size + 3, offset, "%s:%d", piece.c_str(), count);
        offset += 10;
    }

    refresh();
}

void Board::moveCursor(int input) {
    switch (input) {
        case KEY_UP: if (cursor_y > 0) --cursor_y; break;
        case KEY_DOWN: if (cursor_y < size - 1) ++cursor_y; break;
        case KEY_LEFT: if (cursor_x > 0) --cursor_x; break;
        case KEY_RIGHT: if (cursor_x < size - 1) ++cursor_x; break;
    }
}

bool Board::placePiece(const std::string& piece, int player_turn) {
    if (grid[cursor_y][cursor_x] == "·") { // Check for an empty cell
        grid[cursor_y][cursor_x] = piece;
        spdlog::info("Placed {} by Player {} at ({}, {}).", piece, player_turn, cursor_y, cursor_x);
        return true;
    } else {
        spdlog::warn("Cell occupied at ({}, {}).", cursor_y, cursor_x);
        return false;
    }
}
