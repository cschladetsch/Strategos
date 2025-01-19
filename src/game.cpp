
#include "game.hpp"
#include "board.hpp"
#include <ncurses.h>
#include <spdlog/spdlog.h>
#include <map>
#include <algorithm>
#include <cctype>

void Game::start() {
    spdlog::info("Initializing game...");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    // Initialize colors
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);  // Player 1's pieces
        init_pair(2, COLOR_BLUE, COLOR_BLACK); // Player 2's pieces
    }

    Board board;
    board.initialize();

    std::map<std::string, int> player1_pieces = {{"K", 1}, {"N", 2}, {"B", 1}, {"R", 1}};
    std::map<std::string, int> player2_pieces = player1_pieces;
    int player_turn = 1;

    while (true) {
        auto& current_pieces = player_turn == 1 ? player1_pieces : player2_pieces;
        board.display(current_pieces, player_turn);

        int input = getch();
        if (std::isalpha(input)) {
            std::string piece(1, std::toupper(input));
            if (current_pieces[piece] > 0 && board.placePiece(piece, player_turn)) {
                current_pieces[piece]--;
                if (std::all_of(current_pieces.begin(), current_pieces.end(),
                                [](const auto& pair) { return pair.second == 0; })) {
                    player_turn = 3 - player_turn;
                }
            }
        } else if (input == 'q') {
            break;
        }
    }

    endwin();
}
