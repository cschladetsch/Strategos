#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include <string>

class Board;

class Game {
private:
    enum class TurnState {
        PIECE_SELECTION,
        MOVE_TARGET
    };

    Board* board;
    TurnState turn_state = TurnState::PIECE_SELECTION;
    int turn_count = 1;
    int player_turn = 1;
    
    // Piece inventory for both players
    std::map<std::string, int> player1_pieces;
    std::map<std::string, int> player2_pieces;

    void initializeNcurses();
    void initializePieces();
    void showStartScreen();
    void showEndScreen(int winner, int p1_score, int p2_score);
    void displayGameStatus() const;
    void handleInput(int input, bool& game_running);
    int determineFirstPlayer();
    void cleanup();
    std::map<std::string, int>& getCurrentPlayerPieces();

public:
    Game();
    ~Game();
    void start();
};

#endif