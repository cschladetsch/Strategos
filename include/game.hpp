#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include <string>

class Board;

class Game {
private:
    Board* board;
    int turn_count = 1;
    int player_turn = 1;
    bool piece_selected = false;
    
    // Piece inventory for both players
    std::map<std::string, int> player1_pieces;
    std::map<std::string, int> player2_pieces;

    void initializePieces();
    void handleInput(int input, bool& game_running);
    std::map<std::string, int>& getCurrentPlayerPieces();

public:
    Game();
    ~Game();
    void start();
};

#endif