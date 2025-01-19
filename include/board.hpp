#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <string>
#include <map>

class Board {
private:
    static const int size = 11;
    std::array<std::array<std::string, size>, size> grid;
    int cursor_x = 0; // Cursor position
    int cursor_y = 0;

public:
    void initialize();
    void display(const std::map<std::string, int>& pieces, int player_turn) const;
    void moveCursor(int input); // Arrow key movement
    bool placePiece(const std::string& piece, int player_turn);
};

#endif
