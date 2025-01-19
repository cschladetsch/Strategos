#include "board.hpp"
#include "utils.hpp"
#include "rang.hpp" // Ensure this is included for rang functionality
#include <iostream>

void Board::initialize() {
    for (auto& row : grid) {
        row.fill(".");
    }
    grid[0][0] = color("K", "red");
    grid[size - 1][size - 1] = color("K", "blue");
}

void Board::display() const {
    // Clear screen using ANSI codes and reset style
    std::cout << "\033[2J\033[H" << rang::style::reset;

    // Display the board with colors
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
}

