#include "game.hpp"
#include "board.hpp"
#include <ncurses.h>
#include <spdlog/spdlog.h>
#include <chrono>
#include <random>
#include <algorithm>
#include <cctype>

Game::Game() : board(new Board()) {
    spdlog::info("Game instance created");
    initializePieces();
}

Game::~Game() {
    delete board;
    spdlog::info("Game instance destroyed");
}

void Game::initializePieces() {
    // Initialize piece counts for both players
    player1_pieces = {
        {"K", 1}, {"N", 2}, {"B", 1}, {"R", 1}, {"S", 10}
    };
    player2_pieces = player1_pieces;
}

void Game::initializeNcurses() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);    // Player 1
        init_pair(2, COLOR_BLUE, COLOR_BLACK);   // Player 2
        init_pair(3, COLOR_YELLOW, COLOR_BLACK); // Stones
        init_pair(4, COLOR_WHITE, COLOR_BLACK);  // Neutral
    }
    
    spdlog::info("Ncurses initialized");
}

std::map<std::string, int>& Game::getCurrentPlayerPieces() {
    return (player_turn == 1) ? player1_pieces : player2_pieces;
}

void Game::showStartScreen() {
    clear();
    mvprintw(1, 30, "STRATEGOS");
    mvprintw(3, 10, "A Chess-Go Hybrid Game");
    
    mvprintw(5, 5, "Controls:");
    mvprintw(6, 7, "→ Arrow keys: Move cursor");
    mvprintw(7, 7, "→ Space: Select/Place piece");
    mvprintw(8, 7, "→ K: King   N: Knight   B: Bishop   R: Rook   S: Stone");
    mvprintw(9, 7, "→ Q: Quit game");
    
    mvprintw(11, 5, "Game Rules:");
    mvprintw(12, 7, "→ Capture the opponent's King or control the most territory");
    mvprintw(13, 7, "→ Central 5x5 region worth double points");
    mvprintw(14, 7, "→ Game ends after 30 turns or when a King is captured");
    
    mvprintw(16, 5, "Press any key to start...");
    refresh();
    getch();
    
    spdlog::info("Start screen displayed");
}

void Game::showEndScreen(int winner, int p1_score, int p2_score) {
    clear();
    mvprintw(2, 30, "GAME OVER");
    
    if (winner > 0) {
        mvprintw(4, 20, "Player %d wins!", winner);
    } else {
        mvprintw(4, 20, "Game ended in a draw!");
    }
    
    mvprintw(6, 20, "Final Scores:");
    mvprintw(7, 22, "Player 1: %d", p1_score);
    mvprintw(8, 22, "Player 2: %d", p2_score);
    
    if (turn_count > 30) {
        mvprintw(10, 20, "Maximum turns reached!");
    }
    
    mvprintw(12, 20, "Press any key to exit...");
    refresh();
    getch();
    
    spdlog::info("End screen displayed - Winner: Player {}, Scores: P1={}, P2={}", 
                 winner, p1_score, p2_score);
}

void Game::displayGameStatus() const {
    auto& pieces = (player_turn == 1) ? player1_pieces : player2_pieces;
    mvprintw(23, 0, "Turn: %d/30  |  Player %d's turn", turn_count, player_turn);
    
    int offset = 40;
    mvprintw(23, offset, "Available: ");
    for (const auto& [piece, count] : pieces) {
        printw("%s:%d ", piece.c_str(), count);
    }

    if (turn_state == TurnState::PIECE_SELECTION) {
        mvprintw(24, 0, "Select a piece to move or place a new piece (K,N,B,R,S)");
    } else {
        mvprintw(24, 0, "Select destination or press Space to cancel selection");
    }
    
    refresh();
}

int Game::determineFirstPlayer() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(1, 2);
    int first_player = distribution(generator);
    spdlog::info("First player determined: Player {}", first_player);
    return first_player;
}

void Game::handleInput(int input, bool& game_running) {
    auto& current_pieces = getCurrentPlayerPieces();

    switch (input) {
        case 'q':
        case 'Q':
            game_running = false;
            spdlog::info("Game quit by user");
            break;

        case KEY_UP:
        case KEY_DOWN:
        case KEY_LEFT:
        case KEY_RIGHT:
            board->moveCursor(input);
            break;

        case ' ': // Space bar
            if (turn_state == TurnState::PIECE_SELECTION) {
                if (board->selectPiece(player_turn)) {
                    turn_state = TurnState::MOVE_TARGET;
                    spdlog::info("Piece selected by Player {}", player_turn);
                }
            } else {
                bool moved = board->movePiece();
                if (moved) {
                    player_turn = 3 - player_turn;
                    turn_count++;
                    spdlog::info("Turn {} completed", turn_count-1);
                }
                turn_state = TurnState::PIECE_SELECTION;
                board->clearSelection();
            }
            break;

        default:
            if (turn_state == TurnState::PIECE_SELECTION && std::isalpha(input)) {
                std::string piece(1, std::toupper(input));
                if (current_pieces[piece] > 0 && board->placePiece(piece, player_turn)) {
                    current_pieces[piece]--;
                    player_turn = 3 - player_turn;
                    turn_count++;
                    spdlog::info("Piece {} placed", piece);
                }
            }
            break;
    }
}

void Game::cleanup() {
    endwin();
    spdlog::info("Game cleanup completed");
}

void Game::start() {
    spdlog::info("Game starting");
    
    initializeNcurses();
    showStartScreen();
    
    board->initialize();
    player_turn = determineFirstPlayer();
    bool game_running = true;
    int winner = 0;

    while (game_running && turn_count <= 30) {
        board->display(getCurrentPlayerPieces(), turn_count, player_turn);
        displayGameStatus();

        if (board->isGameOver(winner)) {
            game_running = false;
            spdlog::info("Game over - Player {} wins by king capture", winner);
            break;
        }

        int input = getch();
        handleInput(input, game_running);
    }

    if (winner == 0 && game_running) {
        int p1_score = board->getScore(1);
        int p2_score = board->getScore(2);
        
        if (p1_score > p2_score) winner = 1;
        else if (p2_score > p1_score) winner = 2;
        
        spdlog::info("Game over by turn limit - Winner: Player {}", winner);
    }

    showEndScreen(winner, board->getScore(1), board->getScore(2));
    cleanup();
}