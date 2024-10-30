/**
 * \file    GameTree.h
 * \author  Christine Jones 
 * \brief   Class that stores possible solutions to slider puzzle.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef GAME_TREE_H
#define GAME_TREE_H

#include "Board.h"
#include <vector>

/**
 * 
 */
class GameTree {

public:

    /**
     * 
     */
    class Node {

    public:

        /**
         * Constructor. Instantiates game node with given board.
         * 
         * \param Board Game board.
         */
        explicit Node(const Board& b);

        /**
         * Constructor. Instantiates game node with given board and previous
         * game node within the tree.
         * 
         * \param Board Game board to be stored in the node.
         * \param Node* Previous node in the game tree.
         */
        Node(const Board& b, Node* prev_node);

        /**
         * Return reference to game board stored in the node.
         * 
         * \return Reference to game board.
         */
        Board& board() { return m_board; }

        /**
         * Return the number of moves taken to get to this game node.
         * 
         * \return Number of moves.
         */
        int moves() const { return m_moves; }

        /**
         * Return a pointer to the previous node in the game tree.
         * 
         * \return Pointer to game node.
         */
        Node* prevNode() { return m_prev_node; }

        /**
         * Add child node to game node.
         * 
         * \param Node* Pointer to game node.
         */
        void addChild(Node* child);

        /**
         * Return child nodes.
         * 
         * \return Vector of game node pointers. 
         */
        std::vector<Node*>& childNodes() { return m_children; }

        /**
          * Reports the Hamming priority of the game node. The Hamming priority
          * of a game node is the hamming distance of the node's game board
          * plus the number of moves taken thus far to get to this game node.
          * 
          * \return Hamming priority.
          */
        int hamming() const { return m_hamming; }

        /**
         * Reports the Manhattan priority of the game node. The Manhattan
         * priority of a game node is the manhattan distance of the node's game
         * board plus the number of moves taken thus far to get to this game
         * node.
         * 
         * \return Manhattan priority.
         */
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

    /**
     * Constructor. Instantiates empty game tree. 
     */
    GameTree();

    /**
     * Constructor. Instantiates game tree with initial game board to be
     * solved. The initial game board forms the root of the game tree.
     * 
     * \param Board Game board.
     */
    explicit GameTree(const Board& b);

    /**
     * Destructor. Releases memory for all game tree nodes.
     */
    ~GameTree();

    /**
     * Returns the root node of the game tree. The root node is the initial
     * game board to be solved.
     * 
     * \return Game tree node.
     */
    Node* root() { return m_root; }

    /**
     * Returns the number of nodes in the game tree.
     * 
     * \return Number of nodes.
     */
    int numNodes() { return m_num_nodes; }

    /**
     * Insert a node into the game tree.
     * 
     * \param Board Game board to be stored in the new game tree node.
     * \param Node* Previous node in the game tree.
     * 
     * \return Newly created game tree node.
     */
    Node* addNode(const Board& b, Node* prev_node);

    // copying, assigning, moving a GameTree is not supported
    GameTree(const GameTree& tree) = delete;
    GameTree(GameTree& tree) = delete;
    GameTree& operator= (const GameTree& tree) = delete;
    GameTree& operator= (GameTree& tree) = delete;

private:

    // release memory allocated to game tree
    void deleteTree(Node* node);

    Node*    m_root{};
    int      m_num_nodes{};

};

#endif // GAME_TREE_H
