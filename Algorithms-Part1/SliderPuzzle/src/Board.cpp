/**
 * \file    Board.cpp
 * \author  Christine Jones 
 * \brief   
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "Board.H"
#include <algorithm>    // std::swap
#include <cassert>
#include <cmath>        // std::log10, std::abs
#include <iomanip>      // std::setw, std::right
#include <vector>

Board::Board():
    m_dimension{0},
    m_valid{false},
    m_solved{false},
    m_hamming{0},
    m_manhattan{0},
    m_blank_tile{Tile{0, 0}}
{}

Board::Board(const board& b):
    m_board{b},
    m_dimension{b.size()},
    m_valid{false},
    m_solved{false},
    m_hamming{0},
    m_manhattan{0},
    m_blank_tile{Tile{0, 0}}
{
    validateBoard();
    if (!m_valid)
        return;

    assessBoard();
}

std::vector<Board> Board::neighbors() const {

    assert(m_valid);

    std::vector<Board> nboards{};

    // top neighbor
    if (m_blank_tile.row > 0) {

        nboards.emplace_back(Board{*this});
        nboards.back().swapBlankTile(Tile{m_blank_tile.row - 1,
                                          m_blank_tile.col});
    }
    
    // bottom neighbor
    if (m_blank_tile.row < (m_dimension - 1)) {

        nboards.emplace_back(Board{*this});
        nboards.back().swapBlankTile(Tile{m_blank_tile.row + 1, 
                                          m_blank_tile.col});
    }

    // left neighbor
    if (m_blank_tile.col > 0) {

        nboards.emplace_back(Board{*this});
        nboards.back().swapBlankTile(Tile{m_blank_tile.row,
                                          m_blank_tile.col - 1});
    }

    // right neighbor
    if (m_blank_tile.col < (m_dimension - 1)) {

        nboards.emplace_back(Board{*this});
        nboards.back().swapBlankTile(Tile{m_blank_tile.row,
                                          m_blank_tile.col + 1});
    }

    return nboards;
}

Board Board::twin() const {

    assert(m_valid);

    Board b{*this};

    Tile t1{0, 0};
    Tile t2{1, 0};

    if (t1 == b.m_blank_tile)
        ++t1.col;

    if (t2 == b.m_blank_tile)
        ++t2.col;

    std::swap(b.m_board[t1.row][t1.col], b.m_board[t2.row][t2.col]);
    b.assessBoard();

    return b;
}

void Board::swapBlankTile(const Tile& new_blank) {

    std::swap(m_board[m_blank_tile.row][m_blank_tile.col],
              m_board[new_blank.row][new_blank.col]);
    m_blank_tile = new_blank;
    assessBoard();
}

void Board::validateBoard() {

    if (m_dimension < s_min_board_size || m_dimension > s_max_board_size) {
        m_valid = false;
        return;
    }

    std::vector<int> values(m_dimension * m_dimension, 0);

    for (std::size_t row{0}; row < m_dimension; ++row) {

        // check that all rows are the correct length
        if (m_board[row].size() != m_dimension) {
            m_valid = false;
            return;
        }

        for (std::size_t col{0}; col < m_dimension; ++col) {

            // check that tile value is within min and max range
            if (m_board[row][col] < 0 || 
                m_board[row][col] >=
                            static_cast<int>(m_dimension * m_dimension)) {

                m_valid = false;
                return;
            }

            // check that a tile value is not repeated
            if (values[static_cast<std::size_t>(m_board[row][col])] != 0) {
                m_valid = false;
                return;
            }

            // while we're at it, record the blank tile
            if (m_board[row][col] == 0) {
                m_blank_tile = Tile{row, col};
            }

            ++values[static_cast<std::size_t>(m_board[row][col])];
        }
    }

    m_valid = true;
}

void Board::assessBoard() {

    assert(m_valid);

    m_solved    = false;
    m_hamming   = 0;
    m_manhattan = 0;

    determineIfSolved();
    if (!m_solved) {
        calculateDistances();
    }
}

void Board::determineIfSolved() {

    assert(m_valid);

    int  value{1};
    bool solved{true};

    for (std::size_t row{0}; row < m_dimension && solved; ++row) {
        for (std::size_t col{0}; col < m_dimension; ++col) {

            if (m_board[row][col] != value) {
                solved = false;
                break;
            }
            ++value;
        }
    }

    if (static_cast<std::size_t>(value) == (m_dimension * m_dimension)) {
        assert(m_board[m_dimension - 1][m_dimension - 1] == 0);
        m_solved = true;
        return;
    }

    m_solved = false;
}

void Board::calculateDistances() {

    assert(m_valid && !m_solved);

    m_hamming   = 0;
    m_manhattan = 0;

    int  value{1};

    for (std::size_t row{0}; row < m_dimension; ++row) {
        for (std::size_t col{0}; col < m_dimension; ++col) {

            if (m_board[row][col] != value &&
                m_board[row][col] != 0) {

                ++m_hamming;

                Tile goal_position{valueToTile(m_board[row][col])};
                m_manhattan +=
                    std::abs(static_cast<int>(goal_position.row - row));
                m_manhattan +=
                    std::abs(static_cast<int>(goal_position.col - col));
            }

            ++value;
        }
    }
}

Board::Tile Board::valueToTile(int value) const {

    assert(value > 0);
    return Tile{static_cast<std::size_t>(value - 1) / m_dimension,
                static_cast<std::size_t>(value - 1) % m_dimension};
}

bool operator==(const Board& b1, const Board& b2) {

    return b1.m_board == b2.m_board;
}

bool operator!=(const Board& b1, const Board& b2) {

    return !(operator==(b1, b2));
}

std::ostream& operator<<(std::ostream& out, const Board& b) {

    int width = static_cast<int>(std::log10(b.m_dimension * b.m_dimension)) + 1;

    out << "dimension = " << b.m_dimension << " "
        << "valid = " << (b.m_valid  ? "true" : "false") << " "
        << "solved = " << (b.m_solved ? "true" : "false") << " "
        << "hamming = " << b.m_hamming << " "
        << "manhattan = " << b.m_manhattan << " "
        << "blank_space = (" << b.m_blank_tile.row << ", "
        << b.m_blank_tile.col << ")" << '\n'; 

    for (const auto& row : b.m_board) {
        for (const auto& tile : row) {
            out << std::setw(width) << std::right << tile << ' ';
        }
        out << '\n';
    }

    return out;
}
