/**
 * \file    BoardSolver.h
 * \author  Christine Jones 
 * \brief
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef BOARD_SOLVER_H
#define BOARD_SOLVER_H

#include "Board.h"
#include "GameTree.h"
#include <queue>

class BoardSolver {

public:

    enum Priority {
        HAMMING,
        MANHATTAN,
    }; 

    explicit BoardSolver(const Board& b, Priority priority = HAMMING);

    bool isSolvable() const;
    int  moves() const;
    std::vector<Board> solution() const;

    // copying, assigning, moving a BoardSolver is not supported
    BoardSolver(const BoardSolver& solver) = delete;
    BoardSolver(BoardSolver& solver) = delete;
    BoardSolver& operator= (const BoardSolver& solver) = delete;
    BoardSolver& operator= (BoardSolver& solver) = delete;

private:

    void solve();

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
