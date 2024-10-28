/**
 * \file    GameTree.h
 * \author  Christine Jones 
 * \brief
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef GAME_TREE_H
#define GAME_TREE_H

#include "Board.h"
#include <vector>

class GameTree {

public:

    class Node {

    public:

        explicit Node(const Board& b);
        Node(const Board& b, Node* prev_node);

        Board& board()       { return m_board; }
        int    moves() const { return m_moves; }
        Node*  prevNode()    { return m_prev_node; }

        void                addChild(Node* child);
        std::vector<Node*>& childNodes() { return m_children; }

        int hamming() const   { return m_hamming; }
        int manhattan() const { return m_manhattan; }

        // copying, assigning, moving a node is not supported
        Node(const Node& node) = delete;
        Node(Node& node) = delete;
        Node& operator= (const Node& node) = delete;
        Node& operator= (Node& node) = delete;

    private:

        Board              m_board;
        int                m_moves{};
        Node*              m_prev_node{};
        std::vector<Node*> m_children{};

        int      m_hamming{};
        int      m_manhattan{};
    };

    GameTree();
    explicit GameTree(const Board& b);
    ~GameTree();

    Node* root() { return m_root; }
    int   numNodes() { return m_num_nodes; }

    Node* addNode(const Board& b, Node* prev_node);

    // copying, assigning, moving a GameTree is not supported
    GameTree(const GameTree& tree) = delete;
    GameTree(GameTree& tree) = delete;
    GameTree& operator= (const GameTree& tree) = delete;
    GameTree& operator= (GameTree& tree) = delete;

private:

    void deleteTree(Node* node);

    Node*    m_root{};
    int      m_num_nodes{};

};

#endif // GAME_TREE_H
