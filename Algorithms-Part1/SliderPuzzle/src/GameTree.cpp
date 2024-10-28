/**
 * \file    GameTree.cpp
 * \author  Christine Jones 
 * \brief
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
    m_hamming{b.hamming()},
    m_manhattan{b.manhattan()}
{}

GameTree::Node::Node(const Board& b, Node* prev_node):
    m_board{b},
    m_moves{prev_node->moves() + 1},
    m_prev_node{prev_node},
    m_hamming{b.hamming() + m_moves},
    m_manhattan{b.manhattan() + m_moves}
{}

void GameTree::Node::addChild(Node* child) {

    assert(child);
    m_children.push_back(child);
}

GameTree::GameTree():
    m_root{nullptr}
{}

GameTree::GameTree(const Board& b):
    m_root{nullptr},
    m_num_nodes{0}
{
    m_root = new (std::nothrow) Node{b};
    if (!m_root) {
        std::cerr << "GameTree::GameTree: failed to allocate memory" << '\n';
    }
}

GameTree::~GameTree() {

    if (!m_root)
        return;

    deleteTree(m_root);
}

GameTree::Node* GameTree::addNode(const Board& b, Node* prev_node) {

    assert(prev_node);

    Node* new_node = new (std::nothrow) Node{b, prev_node};
    if (!new_node) {
        std::cerr << "GameTree::addNode: failed to allocate memory" << '\n';
        return nullptr;
    }

    prev_node->addChild(new_node);
    ++m_num_nodes;
    return new_node;
}

void GameTree::deleteTree(Node* node) {

    assert(node);

    for (auto& c : node->childNodes()) {
        deleteTree(c);
    }

    delete node;
    node = nullptr;
}
