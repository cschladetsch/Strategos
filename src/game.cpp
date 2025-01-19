#include "game.hpp"
#include "board.hpp"
#include <ncurses.h>
#include <spdlog/spdlog.h>
#include "rang.hpp"
#include <map>
#include <algorithm>

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

void Game::showStartScreen() const {
    clear();
    mvprintw(1, 30, "STRATEGOS");
    mvprintw(3, 10, "A Chess-Go Hybrid Game");
    mvprintw(5, 10, "Controls:");
    mvprintw(6, 12, "→ Arrow keys: Move cursor");
    mvprintw(7, 12, "→ Space: Select/place piece");
    mvprintw(8, 12, "→ K: King   N: Knight   B: Bishop   R: Rook   S: Stone");
    mvprintw(9, 12, "→ ESC: Cancel selection");
    mvprintw(10, 12, "→ Ctrl-C: Quit game");
    mvprintw(12, 10, "Press any key to start...");
    refresh();
    getch();
}

void Game::showEndScreen(int winner) const {
    clear();
    mvprintw(2, 30, "GAME OVER");
    
    if (winner > 0) {
        std::string win_msg = "Player " + std::to_string(winner) + " wins!";
        if (winner == 1) {
            win_msg = rang::fg::red + win_msg + rang::fg::reset;
        } else {
            win_msg = rang::fg::blue + win_msg + rang::fg::reset;
        }
        mvprintw(4, 20, "%s", win_msg.c_str());
    } else {
        mvprintw(4, 20, "Game ended in a draw!");
    }
    
    mvprintw(6, 20, "Final Scores:");
    mvprintw(7, 22, "Player 1: %d", board->getScore(1));
    mvprintw(8, 22, "Player 2: %d", board->getScore(2));
    
    if (turn_count > 30) {
        mvprintw(10, 20, "Maximum turns reached!");
    }
    
    mvprintw(12, 20, "Press any key to exit...");
    refresh();
    getch();
}

std::map<std::string, int>& Game::getCurrentPlayerPieces() {
    return (player_turn == 1) ? player1_pieces : player2_pieces;
}

void Game::handleInput(int input, bool& game_running) {
    auto& current_pieces = getCurrentPlayerPieces();

    switch (input) {
        case 27: // ESC
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

        case ' ': // Space
            if (!piece_selected) {
                if (board->selectPiece(player_turn)) {
                    piece_selected = true;
                    spdlog::info("Player {} selected a piece", player_turn);
                }
            } else {
                if (board->movePiece()) {
                    piece_selected = false;
                    player_turn = 3 - player_turn;
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
    
    // Initialize UTF-8
    setlocale(LC_ALL, "");
    
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    
    // Show start screen and initialize game
    showStartScreen();
    board->initialize();
    
    // Main game loop
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

    showEndScreen(winner);
    endwin();
}