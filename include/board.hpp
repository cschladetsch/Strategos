#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <string>
#include <map>
#include <vector>
#include <utility>

struct Position {
    int x;
    int y;
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

class Board {
private:
    static const int size = 11;
    static const int central_size = 5;
    static constexpr const char* EMPTY_CELL = "·";  // UTF-8 middle dot

    std::array<std::array<std::string, size>, size> grid;
    int cursor_x = 0;
    int cursor_y = 0;
    
    Position selected_pos{-1, -1};
    bool has_selection = false;
    std::vector<Position> valid_moves;

    bool isValidPosition(const Position& pos) const;
    bool isCentralRegion(const Position& pos) const;
    bool isPathClear(const Position& from, const Position& to) const;
    bool isValidPieceMove(const std::string& piece, const Position& from, const Position& to) const;
    bool isPieceOwner(const Position& pos, int player) const;
    bool isOpponentPiece(const Position& pos, int player) const;
    std::string getPieceAt(const Position& pos) const;
    void setPieceAt(const Position& pos, const std::string& piece);
    void updateValidMoves();
    std::string colorPiece(const std::string& piece, int y) const;

public:
    Board() = default;
    void initialize();
    void display(const std::map<std::string, int>& current_pieces, int turn_count, int player_turn) const;
    bool isGameOver(int& winner) const;
    int getScore(int player) const;

    void moveCursor(int input);
    int getCursorX() const { return cursor_x; }
    int getCursorY() const { return cursor_y; }
    void clearSelection();

    bool selectPiece(int player_turn);
    bool placePiece(const std::string& piece, int player_turn);
    bool movePiece();
    bool hasPieceMoved() const { return has_selection; }
    
    int countTerritory(int player) const;
    int countCentralTerritory(int player) const;
    bool isControlled(const Position& pos, int player) const;
};

#endif