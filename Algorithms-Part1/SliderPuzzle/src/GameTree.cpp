/**
 * \file    GameTree.cpp
 * \author  Christine Jones 
 * \brief   Class that stores possible solutions to a slider game board.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "GameTree.h"
#include <cassert>
#include <iostream>
#include <vector>

GameTree::Node::Node(const Board& b):
    m_board{b},
    m_moves{0},
    m_prev_node{nullptr},
    m_next_node{nullptr},
    m_hamming{b.hamming()},
    m_manhattan{b.manhattan()}
{}

GameTree::Node::Node(const Board& b, Node* prev_node):
    m_board{b},
    m_moves{prev_node->moves() + 1},
    m_prev_node{prev_node},
    m_next_node{nullptr},
    m_hamming{b.hamming() + m_moves},
    m_manhattan{b.manhattan() + m_moves}
{}

void GameTree::Node::setNextNode(Node* node) {

    assert(node);
    m_next_node = node;
}

GameTree::GameTree():
    m_root{nullptr},
    m_last_node{nullptr}
{}

GameTree::GameTree(const Board& b):
    m_root{nullptr},
    m_last_node{nullptr}
{
    m_root = new (std::nothrow) Node{b};
    if (!m_root) {
        std::cerr << "GameTree::GameTree: failed to allocate memory" << '\n';
    }

    m_last_node = m_root;
}

GameTree::~GameTree() {

    deleteTree();
}

GameTree::Node* GameTree::addNode(const Board& b, Node* prev_node) {

    assert(m_root && m_last_node);
    assert(prev_node);

    Node* new_node = new (std::nothrow) Node{b, prev_node};
    if (!new_node) {
        std::cerr << "GameTree::addNode: failed to allocate memory" << '\n';
        return nullptr;
    }

    m_last_node->setNextNode(new_node);
    m_last_node = new_node;
    return new_node;
}

void GameTree::deleteTree() {

    Node* node = m_root;
    while (node != nullptr) {

        Node* next{node->nextNode()};
        delete node;
        node = next;
    }

    m_root      = nullptr;
    m_last_node = nullptr;
}
