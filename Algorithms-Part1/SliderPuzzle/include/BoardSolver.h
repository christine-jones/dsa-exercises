/**
 * \file    BoardSolver.h
 * \author  Christine Jones 
 * \brief   Class that implements an A* algorithm to solve an n-by-n slider
 *          puzzle.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef BOARD_SOLVER_H
#define BOARD_SOLVER_H

#include "Board.h"
#include "GameTree.h"
#include <queue>

/**
 * 
 */
class BoardSolver {

public:

    // available priority functions
    enum Priority {
        HAMMING,
        MANHATTAN,
    }; 

    /**
     * Constructor. Solves the given game board, if valid, using the specified
     * priority function which defaults to HAMMING. 
     */
    explicit BoardSolver(const Board& b, Priority priority = HAMMING);

    /**
     * Reports if the game board is solvable.
     * 
     * \return True if the board is solvable; False if not.
     */
    bool isSolvable() const;

    /**
     * Reports the minimum number of moves to solve the game board.
     * 
     * \return Number of moves to solve board; -1 if board is not solvable.
     */
    int  moves() const;

    /**
     * Returns the sequence of game boards for the shortest solution.
     * 
     * \return Vector of game boards; null if board is not solvable.
     */
    std::vector<Board> solution() const;

    // copying, assigning, moving a BoardSolver is not supported
    BoardSolver(const BoardSolver& solver) = delete;
    BoardSolver(BoardSolver& solver) = delete;
    BoardSolver& operator= (const BoardSolver& solver) = delete;
    BoardSolver& operator= (BoardSolver& solver) = delete;

private:

    void solve();

    // function to compare nodes within the priority queue
    struct CompareNodes {

        bool operator()(GameTree::Node* n1,
                        GameTree::Node* n2) {

            if (m_priority == HAMMING) 
                return n1->hamming() > n2->hamming();
            else  
                return n1->manhattan() > n2->manhattan();
        }

        Priority m_priority{};
    };

    GameTree m_game_tree{};
    GameTree m_twin_tree{};

    std::priority_queue<GameTree::Node*,
                        std::vector<GameTree::Node*>,
                        CompareNodes> m_pq{};
    std::priority_queue<GameTree::Node*,
                        std::vector<GameTree::Node*>,
                        CompareNodes> m_twin_pq{};

    GameTree::Node* m_solved_board{};
};

#endif // BOARD_SOLVER_H
