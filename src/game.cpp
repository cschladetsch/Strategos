#include "game.hpp"
#include "board.hpp"
#include <ncurses.h>
#include <spdlog/spdlog.h>
#include <map>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <random>

Game::Game() : board(new Board()) {
    initializePieces();
    spdlog::info("Game instance created");
}

Game::~Game() {
    delete board;
    spdlog::info("Game instance destroyed");
}

void Game::initializePieces() {
    player1_pieces = {
        {"K", 1}, {"N", 2}, {"B", 1}, {"R", 1}, {"S", 10}
    };
    player2_pieces = player1_pieces;
}

void Game::handleInput(int input, bool& game_running) {
    auto& current_pieces = getCurrentPlayerPieces();

    switch (input) {
        case 'q':
        case 'Q':
            game_running = false;
            spdlog::info("Game quit by user");
            break;

        case 27: // Escape key to cancel selection
            if (piece_selected) {
                board->clearSelection();
                piece_selected = false;
                spdlog::info("Selection cancelled");
            }
            break;

        case KEY_UP:
        case KEY_DOWN:
        case KEY_LEFT:
        case KEY_RIGHT:
            board->moveCursor(input);
            break;

        case ' ': // Space bar
            if (!piece_selected) {
                // Try to select a piece
                if (board->selectPiece(player_turn)) {
                    piece_selected = true;
                    spdlog::info("Player {} selected a piece", player_turn);
                }
            } else {
                // Try to move the selected piece
                if (board->movePiece()) {
                    piece_selected = false;
                    player_turn = 3 - player_turn; // Switch players
                    turn_count++;
                    spdlog::info("Piece moved, turn {}", turn_count);
                }
            }
            break;

        default:
            if (!piece_selected && std::isalpha(input)) {
                std::string piece(1, std::toupper(input));
                if (current_pieces[piece] > 0 && board->placePiece(piece, player_turn)) {
                    current_pieces[piece]--;
                    player_turn = 3 - player_turn;
                    turn_count++;
                    spdlog::info("Placed piece {}", piece);
                }
            }
            break;
    }
}

void Game::start() {
    spdlog::info("Starting game");
    
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    // Initialize colors
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);    // Player 1
        init_pair(2, COLOR_BLUE, COLOR_BLACK);   // Player 2
        init_pair(3, COLOR_YELLOW, COLOR_BLACK); // Stones
    }

    board->initialize();
    player_turn = 1;
    turn_count = 1;
    piece_selected = false;

    bool game_running = true;
    int winner = 0;

    while (game_running && turn_count <= 30) {
        board->display(getCurrentPlayerPieces(), turn_count, player_turn);

        if (board->isGameOver(winner)) {
            game_running = false;
            break;
        }

        int input = getch();
        handleInput(input, game_running);
    }

    // Determine winner if game ended by turn limit
    if (winner == 0 && game_running) {
        int p1_score = board->getScore(1);
        int p2_score = board->getScore(2);
        winner = (p1_score > p2_score) ? 1 : (p2_score > p1_score) ? 2 : 0;
    }

    mvprintw(12, 0, "Game Over! Winner: Player %d", winner);
    refresh();
    getch();
    endwin();
}

std::map<std::string, int>& Game::getCurrentPlayerPieces() {
    return (player_turn == 1) ? player1_pieces : player2_pieces;
}