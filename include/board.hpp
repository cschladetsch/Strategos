
#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <string>

class Board {
private:
    static const int size = 11;
    std::array<std::array<std::string, size>, size> grid;
    int cursor_x = 0; // Cursor position
    int cursor_y = 0;

public:
    void initialize();
    void display() const;
    void moveCursor(char direction);
    void placeStone();
};

#endif
