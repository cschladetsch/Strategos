#include "game.hpp"
#include "board.hpp"
#include "rang.hpp"
#include <iostream>

void Game::start() {
    rang::setControlMode(rang::control::Force);
    Board board;
    board.initialize();

    // Placeholder game loop
    bool game_running = true;
    while (game_running) {
        board.display();
        std::cout << "Enter your move (or type 'help'): ";
        std::string command;
        std::cin >> command;
        
        if (command == "help") {
            std::cout << "Help: Move pieces by selecting them with cursor and placing them.\n";
            std::cin.ignore();
            std::cin.get(); // Wait for Enter key
        } else if (command == "quit") {
            game_running = false;
        } else {
            std::cout << "Command not recognized: " << command << "\n";
        }
    }
}

