/**
 * \file    BoardSolver.cpp
 * \author  Christine Jones 
 * \brief
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "Board.h"
#include "BoardSolver.h"
#include <cassert>

BoardSolver::BoardSolver(const Board& b, Priority priority):
    m_game_tree{b},
    m_twin_tree{b.twin()},
    m_pq{CompareNodes{priority}},
    m_twin_pq{CompareNodes{priority}},
    m_solved_board{nullptr}
{
    assert(b.isValid());

    if (!m_game_tree.root())
        return;

    m_pq.push(m_game_tree.root());
    m_twin_pq.push(m_twin_tree.root());
    solve();
}

bool BoardSolver::isSolvable() const {
    
    return m_solved_board ? true : false;
}

int BoardSolver::moves() const {
    
    return m_solved_board ? m_solved_board->moves() : -1;
}

std::vector<Board> BoardSolver::solution() const {

    if (!m_solved_board)    
        return std::vector<Board>{};

    std::size_t moves{static_cast<std::size_t>(m_solved_board->moves())};

    std::vector<Board> sequence{moves + 1};
    
    for (GameTree::Node* node{m_solved_board};
         node != nullptr;
         node = node->prevNode(), --moves) {

        sequence[moves] = node->board();
    }

    return sequence;
}

void BoardSolver::solve() {

    assert(!m_pq.empty() && !m_twin_pq.empty());

    GameTree::Node* node{m_pq.top()};
    GameTree::Node* twin_node{m_twin_pq.top()};

    m_pq.pop();
    m_twin_pq.pop();

    while (!node->board().isSolved() && !twin_node->board().isSolved()) {

        for (auto& n : node->board().neighbors()) {

            GameTree::Node* new_node{m_game_tree.addNode(n, node)};
            if (new_node->board() != node->board())
                m_pq.push(new_node);
        }

        for (auto& n : twin_node->board().neighbors()) {

            GameTree::Node* new_node{m_twin_tree.addNode(n, twin_node)};
            if (new_node->board() != twin_node->board())
                m_twin_pq.push(new_node);
        }

        node      = m_pq.top();
        twin_node = m_twin_pq.top();

        m_pq.pop();
        m_twin_pq.pop();
    }

    if (twin_node->board().isSolved()) {
        assert(!node->board().isSolved());
        return;
    }

    assert(node->board().isSolved());
    m_solved_board = node;
}
