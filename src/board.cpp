#include "board.hpp"
#include <ncurses.h>
#include <spdlog/spdlog.h>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>

void Board::initialize() {
    spdlog::info("Initializing board");
    
    for (auto& row : grid) {
        row.fill(EMPTY_CELL);
    }
    
    // Set up Player 1 pieces (top)
    grid[0][0] = "K";
    grid[0][1] = "N";
    grid[0][2] = "N";
    grid[1][0] = "B";
    grid[2][0] = "R";

    // Set up Player 2 pieces (bottom)
    grid[10][10] = "K";
    grid[10][9] = "N";
    grid[10][8] = "N";
    grid[9][10] = "B";
    grid[8][10] = "R";
    
    cursor_x = 0;
    cursor_y = 0;
    clearSelection();
}

void Board::display(const std::map<std::string, int>& current_pieces, int turn_count, int player_turn) const {
    clear();

    // Display column headers (A-K)
    mvprintw(0, 8, "A B C D E F G H I J K");
    
    for (int y = 0; y < size; ++y) {
        mvprintw(y + 1, 0, "%2d", y + 1);
        mvprintw(y + 1, 2, "  ");
        
        for (int x = 0; x < size; ++x) {
            Position pos{x, y};
            bool is_cursor = (x == cursor_x && y == cursor_y);
            bool is_selected = pos == selected_pos;
            bool is_valid_move = std::find(valid_moves.begin(), valid_moves.end(), pos) != valid_moves.end();
            
            // Set colors
            if (grid[y][x] != EMPTY_CELL && grid[y][x] != "S") {
                bool is_top_half = y < size/2;
                attron(COLOR_PAIR(is_top_half ? 1 : 2));
            } else if (grid[y][x] == "S") {
                attron(COLOR_PAIR(3));
            }
            
            // Apply highlighting attributes
            if (is_valid_move) attron(A_BOLD);
            if (is_selected || is_cursor) attron(A_REVERSE);

            // Print piece or valid move marker
            if (is_valid_move) {
                mvprintw(y + 1, 8 + x * 2, "*");
            } else {
                mvprintw(y + 1, 8 + x * 2, "%s", grid[y][x].c_str());
            }

            // Reset attributes
            attroff(A_REVERSE | A_BOLD);
            attroff(COLOR_PAIR(1) | COLOR_PAIR(2) | COLOR_PAIR(3));
        }
    }

    // Status display
    mvprintw(size + 2, 0, "Turn %d | Player %d", turn_count, player_turn);
    mvprintw(size + 3, 0, "Available:");
    int offset = 10;
    for (const auto& [piece, count] : current_pieces) {
        if (count > 0) {
            mvprintw(size + 3, offset, "%s:%d", piece.c_str(), count);
            offset += 5;
        }
    }

    // Help text
    if (has_selection) {
        mvprintw(size + 4, 0, "Select destination (*) or press ESC to cancel (Ctrl-C to quit)");
    } else {
        mvprintw(size + 4, 0, "SPACE to select piece, K/N/B/R/S to place new piece (Ctrl-C to quit)");
    }

    refresh();
}

bool Board::isValidPosition(const Position& pos) const {
    return pos.x >= 0 && pos.x < size && pos.y >= 0 && pos.y < size;
}

bool Board::isCentralRegion(const Position& pos) const {
    int start = (size - central_size) / 2;
    int end = start + central_size;
    return pos.x >= start && pos.x < end && pos.y >= start && pos.y < end;
}

std::string Board::getPieceAt(const Position& pos) const {
    if (!isValidPosition(pos)) return "";
    return grid[pos.y][pos.x];
}

void Board::setPieceAt(const Position& pos, const std::string& piece) {
    if (isValidPosition(pos)) {
        grid[pos.y][pos.x] = piece;
    }
}

bool Board::isValidPieceMove(const std::string& piece, const Position& from, const Position& to) const {
    if (!isValidPosition(to)) return false;
    if (from == to) return false;
    
    std::string target = getPieceAt(to);
    if (target == "S") return false;  // Can't move onto stones
    if (target != EMPTY_CELL && !isOpponentPiece(to, isPieceOwner(from, 1) ? 1 : 2)) return false;

    int dx = to.x - from.x;
    int dy = to.y - from.y;

    switch (piece[0]) {
        case 'K':  // King moves one square in any direction
            return std::abs(dx) <= 1 && std::abs(dy) <= 1;
            
        case 'N':  // Knight moves in L-shape (2+1)
            return (std::abs(dx) == 2 && std::abs(dy) == 1) || 
                   (std::abs(dx) == 1 && std::abs(dy) == 2);
            
        case 'B':  // Bishop moves diagonally
            if (std::abs(dx) != std::abs(dy)) return false;
            return isPathClear(from, to);
            
        case 'R':  // Rook moves horizontally or vertically
            if (dx != 0 && dy != 0) return false;
            return isPathClear(from, to);
            
        case 'S':  // Stones cannot be moved
            return false;
    }
    return false;
}

bool Board::isPathClear(const Position& from, const Position& to) const {
    int dx = to.x - from.x;
    int dy = to.y - from.y;
    int steps = std::max(std::abs(dx), std::abs(dy));
    
    for (int i = 1; i < steps; ++i) {
        Position pos{
            from.x + (dx * i) / steps,
            from.y + (dy * i) / steps
        };
        if (getPieceAt(pos) != EMPTY_CELL) return false;
    }
    return true;
}

void Board::moveCursor(int input) {
    switch (input) {
        case KEY_UP:    if (cursor_y > 0) --cursor_y; break;
        case KEY_DOWN:  if (cursor_y < size - 1) ++cursor_y; break;
        case KEY_LEFT:  if (cursor_x > 0) --cursor_x; break;
        case KEY_RIGHT: if (cursor_x < size - 1) ++cursor_x; break;
    }
}

bool Board::selectPiece(int player_turn) {
    Position pos{cursor_x, cursor_y};
    std::string piece = getPieceAt(pos);
    
    if (piece != EMPTY_CELL && piece != "S" && isPieceOwner(pos, player_turn)) {
        selected_pos = pos;
        has_selection = true;
        updateValidMoves();
        spdlog::info("Selected {} at ({},{})", piece, pos.x, pos.y);
        return true;
    }
    return false;
}

void Board::updateValidMoves() {
    valid_moves.clear();
    if (!has_selection) return;
    
    std::string piece = getPieceAt(selected_pos);
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            Position pos{x, y};
            if (isValidPieceMove(piece, selected_pos, pos)) {
                valid_moves.push_back(pos);
            }
        }
    }
}

bool Board::placePiece(const std::string& piece, int player_turn) {
    Position pos{cursor_x, cursor_y};
    bool valid_zone = (player_turn == 1 && pos.y <= size/2) ||
                     (player_turn == 2 && pos.y > size/2);
    
    if (getPieceAt(pos) == EMPTY_CELL && valid_zone) {
        setPieceAt(pos, piece);
        spdlog::info("Placed {} at ({},{}) by Player {}", piece, pos.x, pos.y, player_turn);
        return true;
    }
    return false;
}

bool Board::movePiece() {
    if (!has_selection) return false;
    
    Position to{cursor_x, cursor_y};
    if (std::find(valid_moves.begin(), valid_moves.end(), to) != valid_moves.end()) {
        std::string piece = getPieceAt(selected_pos);
        std::string captured = getPieceAt(to);
        
        if (captured != EMPTY_CELL) {
            spdlog::info("Captured {} at ({},{})", captured, to.x, to.y);
        }
        
        setPieceAt(to, piece);
        setPieceAt(selected_pos, EMPTY_CELL);
        clearSelection();
        return true;
    }
    return false;
}

void Board::clearSelection() {
    has_selection = false;
    selected_pos = Position{-1, -1};
    valid_moves.clear();
}

bool Board::isOpponentPiece(const Position& pos, int player) const {
    std::string piece = getPieceAt(pos);
    if (piece == EMPTY_CELL || piece == "S") return false;
    return isPieceOwner(pos, 3 - player);
}

bool Board::isPieceOwner(const Position& pos, int player) const {
    if (!isValidPosition(pos)) return false;
    bool is_top_half = pos.y < size/2;
    return (player == 1 && is_top_half) || (player == 2 && !is_top_half);
}

bool Board::isControlled(const Position& pos, int player) const {
    if (!isValidPosition(pos)) return false;
    std::string piece = getPieceAt(pos);
    if (piece == EMPTY_CELL) return false;
    if (piece == "S") return isPieceOwner(pos, player);
    return isPieceOwner(pos, player);
}

int Board::countTerritory(int player) const {
    int count = 0;
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            Position pos{x, y};
            if (isControlled(pos, player)) {
                count += isCentralRegion(pos) ? 2 : 1;
            }
        }
    }
    return count;
}

int Board::countCentralTerritory(int player) const {
    int count = 0;
    int start = (size - central_size) / 2;
    int end = start + central_size;
    
    for (int y = start; y < end; ++y) {
        for (int x = start; x < end; ++x) {
            if (isControlled(Position{x, y}, player)) {
                count++;
            }
        }
    }
    return count;
}

bool Board::isGameOver(int& winner) const {
    bool king1_alive = false;
    bool king2_alive = false;
    
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            if (grid[y][x] == "K") {
                if (y <= size/2) king1_alive = true;
                else king2_alive = true;
            }
        }
    }
    
    if (!king1_alive) {
        winner = 2;
        return true;
    }
    if (!king2_alive) {
        winner = 1;
        return true;
    }
    
    return false;
}

int Board::getScore(int player) const {
    return countTerritory(player);
}