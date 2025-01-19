**Game Design Document: Chess-Go Hybrid**

**Title:** Strategos

**Overview:**
Strategos is a two-player console-based strategy game that combines elements of Chess and Go. The game emphasizes territorial control and strategic depth through simple yet engaging mechanics. Each player must outmaneuver their opponent by strategically placing immovable Stones and utilizing Chess-like movable pieces to control the board. The ultimate goal is to dominate a majority of the board while capturing the opponent's King piece.

---

**Game Features:**
1. **Platform:** Console-based application (C++23, single-screen interface).
2. **Player Count:** 2 players, alternating turns.
3. **Objective:**
   - Capture the opponent’s King.
   - Control a majority of the board by the end of a 30-turn limit.

---

**Game Board:**
- **Dimensions:** 11x11 grid.
- **Special Zones:**
  - **Central Region:** 5x5 grid in the center worth bonus points for control.
  - **Corners:** Starting positions for each player.

---

**Game Pieces:**
1. **Stone (Immovable):**
   - Cannot be moved after placement.
   - Used to block paths or control territories.
   - Limited to 10 per player.

2. **King (Movable):**
   - The most critical piece; its capture results in immediate loss.
   - Moves like a King in Chess (one square in any direction).
   - Starts at a designated corner of the board.

3. **Knight (Movable):**
   - Moves in an “L” shape (Chess Knight move).
   - Excellent for tactical strikes.
   - Each player starts with 2.

4. **Bishop (Movable):**
   - Moves diagonally, any number of spaces.
   - Each player starts with 1.

5. **Rook (Movable):**
   - Moves vertically or horizontally, any number of spaces.
   - Each player starts with 1.

---

**Gameplay Mechanics:**
1. **Turn-Based System:**
   - Players alternate turns.
   - On each turn, a player can:
     1. Place a Stone (if available).
     2. Move a Chess-like piece.

2. **Territorial Control:**
   - Players gain points for controlling regions by surrounding them with Stones or movable pieces.
   - The Central Region provides double points for control.

3. **Piece Capture:**
   - Movable pieces can capture an opponent’s piece by landing on the same square.
   - Stones cannot be captured or moved once placed.

4. **Endgame Conditions:**
   - A player captures the opponent’s King.
   - At the end of 30 turns, the player with the highest board control score wins.

---

**Scoring System:**
- **Control Points:**
  - 1 point for each square controlled.
  - 2 points for each square in the Central Region.
- **Bonus Points:**
  - Capturing an opponent’s piece: +3 points.

---

**User Interface (UI):**
1. **Console Layout:**
   - Board displayed as a 11x11 ASCII grid with colors implemented using `rang.hpp` for better visual clarity.
   - Pieces represented by letters:
     - Stone: `S` (yellow).
     - King: `K` (red for Player 1, blue for Player 2).
     - Knight: `N` (white).
     - Bishop: `B` (green).
     - Rook: `R` (cyan).
   - Player’s turn and score displayed below the board.

2. **Input System:**
   - Players enter commands to make moves (e.g., “B2 to C3”).
   - Stones placed by specifying coordinates (e.g., “Place S at D4”).

---

**Example Session:**

**Initial Setup:**
The starting positions of the pieces are as follows:
- Player 1 (White):
  - King (K) at A1
  - Knights (N) at B1 and C1
  - Bishop (B) at A2
  - Rook (R) at A3
- Player 2 (Black):
  - King (K) at K11
  - Knights (N) at J11 and I11
  - Bishop (B) at K10
  - Rook (R) at K9

**Initial Board State:**
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

**Turn 1:** Player 1 places a Stone at D5 (yellow).
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

**Turn 2:** Player 2 moves a Knight from J11 to H9 (white).
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
9 . . . . . . . . N . R
10 . . . . . . . . . B .
11 . . . . . . . . . N K
```

**Turn 3:** Player 1 moves Bishop from A2 to E6 (green).
```
  A B C D E F G H I J K
1 K N N R . . . . . . .
2 . . . . . . . . . . .
3 R . . . . . . . . . .
4 . . . . . . . . . . .
5 . . . S . . . . . . .
6 . . . . . B . . . . .
7 . . . . . . . . . . .
8 . . . . . . . . . . .
9 . . . . . . . . N . R
10 . . . . . . . . . B .
11 . . . . . . . . . N K
```

**Turn 4:** Player 2 places a Stone at G7 (yellow).
```
  A B C D E F G H I J K
1 K N N R . . . . . . .
2 . . . . . . . . . . .
3 R . . . . . . . . . .
4 . . . . . . . . . . .
5 . . . S . . . . . . .
6 . . . . . B . . . . .
7 . . . . . . S . . . .
8 . . . . . . . . . . .
9 . . . . . . . . N . R
10 . . . . . . . . . B .
11 . . . . . . . . . N K
```

---

**Analysis of Gameplay:**
The updated board size and colored visual aid using `rang.hpp` make the game more visually appealing and accessible. The additional moves demonstrate a blend of territorial control, piece maneuvering, and strategic planning. The game maintains a balance of tactical depth and strategic decision-making as players compete for control and capture opportunities.


