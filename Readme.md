# Strategos: A Chess-Go Hybrid Game

**Strategos** is a two-player, console-based strategy game that combines elements of Chess and Go. Designed for C++23 with a single-screen interface, it emphasizes territorial control, strategic planning, and tactical gameplay.

## Features
- **Platform**: Console-based application.
- **Player Count**: 2 players with alternating turns.
- **Objective**:
  - Capture the opponent’s King.
  - Control a majority of the board by the end of 30 turns. A draw is declared if scores are tied, with Central Region control acting as a tiebreaker.

## Gameplay Mechanics
- Players use **arrow keys** to move a cursor and highlight grid cells.
- **Space bar**: Select a piece or place a Stone.
- **Enter**: Confirm moves.
- **Q**: Quit the game.

### Pieces and Interactions
1. **Stone (S)**: Yellow, immovable, used to block paths or control territory.
2. **King (K)**: Red (Player 1) or Blue (Player 2), critical for victory.
3. **Knight (N)**: White, moves in an “L” shape.
4. **Bishop (B)**: Green, moves diagonally.
5. **Rook (R)**: Cyan, moves vertically or horizontally.

### Scoring
- **Control Points**:
  - 1 point per controlled square.
  - 2 points for Central Region squares.
- **Bonus Points**:
  - Capturing an opponent’s piece: +3 points.

## User Interface
- The board is displayed as an **11x11 ASCII grid**, enhanced with `rang.hpp` for colors:
  - **Cursor**: Highlighted in cyan.
  - **Prompts**: Yellow.
  - **Errors**: Red.
- Row and column labels assist navigation.

## Setup Instructions
1. Install dependencies:
   ```bash
   sudo apt install libncurses5-dev libncursesw5-dev
   ```
2. Clone the repository or extract the provided ZIP file.
3. Build and run:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ./Strategos
   ```

## Example Gameplay
1. **Starting Board**:
   ```
     A B C D E F G H I J K
   1 K N N R . . . . . . .
   2 B . . . . . . . . . .
   3 R . . . . . . . . . .
   4 . . . . . . . . . . .
   5 . . . . . . . . . . .
   6 . . . . . . . . . . .
   7 . . . . . . . . . . .
   8 . . . . . . . . . . .
   9 . . . . . . . . . . R
  10 . . . . . . . . . B .
  11 . . . . . . . . N N K
   ```
2. **Player 1 places a Stone at D5**:
   ```
     A B C D E F G H I J K
   1 K N N R . . . . . . .
   2 B . . . . . . . . . .
   3 R . . . . . . . . . .
   4 . . . . . . . . . . .
   5 . . . S . . . . . . .
   6 . . . . . . . . . . .
   7 . . . . . . . . . . .
   8 . . . . . . . . . . .
   9 . . . . . . . . . . R
  10 . . . . . . . . . B .
  11 . . . . . . . . N N K
   ```

## Development Tools
- **Languages**: C++23.
- **Dependencies**:
  - `ncurses` for terminal rendering.
  - `rang.hpp` for colored output.
- **Build System**: CMake.

## License
This project is open-source and available under the MIT License.

