/**
 * \file    Board.h
 * \author  Christine Jones 
 * \brief
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>

using board = std::vector<std::vector<int>>;

class Board {

public:

    Board();
    explicit Board(const board& b);

    std::size_t dimension() const { return m_dimension; }
    bool        isValid() const   { return m_valid; }
    bool        isSolved() const  { return m_solved; }
    int         hamming() const   { return m_hamming; }
    int         manhattan() const { return m_manhattan; }

    std::vector<Board> neighbors() const;
    Board              twin() const;

    // comparison operators
    friend bool operator==(const Board& b1, const Board& b2);
    friend bool operator!=(const Board& b1, const Board& b2);

    // output operator
    friend std::ostream& operator<<(std::ostream& out, const Board& b);

private:

    struct Tile {

        std::size_t row{};
        std::size_t col{};

        friend bool operator==(const Tile& t1, const Tile& t2) {
            return (t1.row == t2.row) && (t1.col == t2.col);
        }
    };

    void swapBlankTile(const Tile& new_blank);

    void validateBoard();
    void assessBoard();
    void determineIfSolved();
    void calculateDistances();

    Tile valueToTile(int value) const;

    static constexpr std::size_t s_min_board_size{2};
    static constexpr std::size_t s_max_board_size{127};

    board       m_board{};
    std::size_t m_dimension{};

    bool m_valid{};
    bool m_solved{};
    int  m_hamming{};
    int  m_manhattan{};

    Tile m_blank_tile{};

};

#endif // BOARD_H
