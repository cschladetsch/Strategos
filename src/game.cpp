#include "game.hpp"
#include "board.hpp"
#include <ncurses.h>

void Game::start() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0); // Hide cursor

    Board board;
    board.initialize();

    int input;
    bool running = true;

    while (running) {
        board.display();
        input = getch(); // Get user input
        switch (input) {
            case KEY_UP: board.moveCursor('w'); break;
            case KEY_DOWN: board.moveCursor('s'); break;
            case KEY_LEFT: board.moveCursor('a'); break;
            case KEY_RIGHT: board.moveCursor('d'); break;
            case ' ': board.placeStone(); break; // Place a stone
            case 'q': running = false; break;    // Quit the game
        }
    }

    endwin(); // End ncurses mode
}

