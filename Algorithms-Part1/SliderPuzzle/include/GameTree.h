/**
 * \file    GameTree.h
 * \author  Christine Jones 
 * \brief   Class that stores possible solutions to a slider game board.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef GAME_TREE_H
#define GAME_TREE_H

#include "Board.h"
#include <vector>

/**
 * Class that stores possible solutions to a slider puzzle board game within
 * a tree structure.
 * 
 * The initial game board forms the root of the game tree. Neighboring boards
 * (those that can be reached in one move, swapping the blank tile with an
 * adjacent tile) become child nodes. The game tree continues to be formed in
 * a similar manner with subsequent neighboring game boards becoming child 
 * nodes within the game tree. Eventually, if the game board is solvable, one
 * of the leaf nodes is the solved board, and walking back up the path of the
 * tree from leaf to root provides the sequence of game boards that forms the
 * solution.
 */
class GameTree {

public:

    /**
     * Class that forms a single node within the game tree.
     * 
     * A node contains a game board representing a single step in the 
     * sequence towards the solved board. The Hamming and Manhattan priorities
     * of the game node are calculated and cached at node creation in addition
     * to the number of moves taken thus far to reach the node.
     * 
     * A link to a previous node is maintained to form the game tree. Following
     * the path of previous nodes from a leaf node towards the root gives a
     * sequence of game boards that make up a possible solution.
     * 
     * A link to a next node is also maintained. This is used to build a simple
     * linked list of game nodes for the purposes of resource deletion. The
     * next node link is not used in forming the actual game tree.
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
         * \param Node* Previous node in the game tree. Must not be NULL.
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
         * Return a pointer to the previous/next node in the game tree.
         * 
         * \return Pointer to game node.
         */
        Node* prevNode() { return m_prev_node; }
        Node* nextNode() { return m_next_node; }

        /**
         * Set the next node member of the node.
         * 
         * \param Node* Pointer to game node. Must not be NULL.
         */
        void setNextNode(Node* node);

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

        Board m_board;
        int   m_moves{};
        Node* m_prev_node{}; // used to form game tree
        Node* m_next_node{}; // used to form linked list to enable deletion

        int m_hamming{};
        int m_manhattan{};
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
     * Insert a node into the game tree.
     * 
     * \param Board Game board to be stored in the new game tree node.
     * \param Node* Previous node in the game tree. Must not be NULL.
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
    void deleteTree();

    Node* m_root{};
    Node* m_last_node{}; // used to form linked list to enable deletion   

};

#endif // GAME_TREE_H
