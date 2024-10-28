/**
 * \file    Board.h
 * \author  Christine Jones 
 * \brief   Class that models an n-by-n slider puzzle board.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>

/**
 * Class that represents a generalized n-by-n, 8-puzzle board game.
 * 
 * A board is an n-by-n grid with (n^2 - 1) tiles labeled 1 through (n^2 - 1),
 * plus a blank tile. A board is solved if the tiles are arranged in row-major
 * order with the blank tile in the bottom right corner. The following diagram
 * shows a sequence of moves from an initial board (left) to the solved board
 * (right).
 * 
 *   1 3     1   3     1 2 3     1 2 3     1 2 3
 * 4 2 5 --> 4 2 5 --> 4   5 --> 4 5   --> 4 5 6
 * 7 8 6     7 8 6     7 8 6     7 8 6     7 8 0
 * 
 * All methods are performed in time proportional to n^2 or better in the worst
 * case.
 */
class Board {

public:

    // type definition of underlying n-by-n game board
    using board = std::vector<std::vector<int>>;

    /**
     * Constructor. Instantiates empty, invalid board game.
     */
    Board();

    /**
     * Constructor. Instantiates game from given board. The validity of the
     * given game board is determined.
     * 
     * \param board n-by-n game board
     */
    explicit Board(const board& b);

    /**
     * Reports the given dimension of the n-by-n game board.
     * 
     * \return Dimension n.
     */
    std::size_t dimension() const { return m_dimension; }

    /**
     * Reports if the game board is valid.
     * 
     * \return True if the game board is valid; False if not.
     */
    bool isValid() const   { return m_valid; }

    /**
     * Reports if the game board is in a solved state.
     * 
     * \return True if the game board is solved; False if not.
     */
    bool isSolved() const  { return m_solved; }

    /**
     * Reports the Hamming Distance of the game board. The Hamming Distance
     * between a board and its respective solved board is the number of tiles
     * in the wrong position.
     * 
     * \return Hamming distance.
     */
    int hamming() const   { return m_hamming; }

    /**
     * Reports the Manhattan Distance of the game board. The Manhattan Distance
     * between a board and its respective solved board is the sum of the 
     * vertical and horizontal distances of each tile to their solved position.
     * 
     * \return Manhattan distance.
     */
    int manhattan() const { return m_manhattan; }

    /**
     * Returns the set of neighboring boards. A neighboring board is one in
     * which the blank tile is swapped with an adjacent tile. A board can have
     * 2, 3, or 4 neighbors depending on the position of the blank tile.
     * 
     * \return Vector of neighboring Boards.
     */
    std::vector<Board> neighbors() const;

    /**
     * Returns a copy of the game board, but with a pair of tiles swapped. The
     * swapped tiles will not include the blank tile.
     * 
     * \return Board.
     */
    Board twin() const;

    // comparison operators
    friend bool operator==(const Board& b1, const Board& b2);
    friend bool operator!=(const Board& b1, const Board& b2);

    // output operator
    friend std::ostream& operator<<(std::ostream& out, const Board& b);

private:

    // represents a single tile within the n-by-n game board
    struct Tile {

        std::size_t row{};
        std::size_t col{};

        friend bool operator==(const Tile& t1, const Tile& t2) {
            return (t1.row == t2.row) && (t1.col == t2.col);
        }
    };

    // swap blank tile with adjacent tile to create neighbor board
    void swapBlankTile(const Tile& new_blank);

    // determine if the board is a valid game board
    void validateBoard();

    // determine if the game board is in the solved state; if not, calculate
    // the hamming and manhattan distances of the board
    void assessBoard();
    void determineIfSolved();
    void calculateDistances();

    // determine the solved tile position of a board value
    Tile valueToTile(int value) const;

    // minimum and maximum dimensions allowed for a game board
    static constexpr std::size_t s_min_board_size{2};
    static constexpr std::size_t s_max_board_size{127};

    board       m_board{};
    std::size_t m_dimension{};

    bool m_valid{};
    bool m_solved{};
    int  m_hamming{};
    int  m_manhattan{};

    Tile m_blank_tile{}; // current position of the blank tile

};

#endif // BOARD_H
