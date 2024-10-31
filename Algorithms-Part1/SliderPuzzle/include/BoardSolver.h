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
 * Class that implements an A* search algorithm to solve a given n-by-n slider
 * puzzle game board.
 * 
 * The initial puzzle board forms the root node of a game tree with an assigned
 * number of moves set to 0. Neighboring boards (those that can be reached in
 * one move, swapping the blank tile with an adjacent tile) become child nodes
 * with number of moves set to 1. The game tree continues to be constructed in
 * a similar manner with subsequent neighboring game boards becoming child
 * nodes within the game tree and a move count incremented by 1.
 * 
 * To determine the shortest solution to the given game board, the initial 
 * board (which forms the root of the game tree) is inserted into a priority 
 * queue. For each iteration of the algorithm, the game board with minimum
 * priority is removed from the priority queue (which is the initial game board
 * in the first round of the algorithm). All neighboring game boards are then
 * inserted into the priority queue. This procedure is repeated until the game
 * board removed from the priority queue is the solved game board.
 * 
 * The choice of priority function for determining the minimum priority game
 * board within the priority queue is crucial for the effectiveness of this
 * algorithm. Two priority functions are provided.
 * 
 *  * Hamming:   The Hamming Distance of the game board plus the number of
 *               moves made thus far to get to the game board. The Hamming
 *               Distance of a game board is the number of tiles in the wrong
 *               position with respect to the solved board.
 *
 *  * Manhattan: The Manhattan Distance of the game board plus the number of
 *               moves made thus far to get to the game board. The Manhattan
 *               Distance of a game board is the sum of the vertical and
 *               horizontal distances of each tile to their solved position. 
 * 
 * Not all game boards are solvable. However, boards are divided into two 
 * equivalence classes with respect to solvability. (1) Those that are
 * solvable, and (2) those that can be solved if the board is modified by
 * swapping any pair of tiles, not including the blank tile.
 * 
 * This fact is used to prevent the algorithm from boundlessly running to 
 * determine a solution for an unsolvable game board. The A* algorithm
 * described above is actually run on two game boards simultaneously, one with
 * the initial game board and one with the initial game board modified by
 * swapping a pair of tiles. The algorithm is run in lockstep with both
 * boards. Exactly one of the two game boards leads to the solved board.
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
     * 
     * \param Board Game board to be solved.
     * \param Priority Priority function to use; defaults to HAMMING. 
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

    GameTree::Node* m_solved_board{}; // node in game tree that represents
                                      // shortest solution
};

#endif // BOARD_SOLVER_H
