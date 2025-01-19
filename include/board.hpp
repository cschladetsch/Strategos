#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <string>

class Board {
private:
    static const int size = 11;
    std::array<std::array<std::string, size>, size> grid;

public:
    void initialize();
    void display() const;
};

#endif
