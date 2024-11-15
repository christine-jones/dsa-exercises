/**
 * \file    KDTree.h
 * \author  Christine Jones 
 * \brief   Class that represents a set of points in the unit square using a
 *          2D-tree.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef KD_TREE_H
#define KD_TREE_H

#include "Point2D.h"
#include "Rectangle.h"
#include <vector>

class KDTree {

public:

    /**
     * Constructor. Instantiates an empty tree.
     */
    KDTree();

    /**
     * Destructor. Releases all resources allocated to the tree.
     */
    ~KDTree();

    /**
     * Determines if the tree is empty.
     * 
     * \return True if the tree is empty; false if not.
     */
    bool isEmpty() const { return m_root == nullptr; }

    /**
     * Determines the number of points in the tree.
     * 
     * \returns Number of points in the tree.
     */
    int size() const { return m_num_nodes; }

    /**
     * Inserts a point into the tree. Must be unique, no duplicates allowed.
     * The point to be inserted must be within the unit square, i.e., x and y
     * coordinates between 0 and 1, inclusive; if it is not in the unit square,
     * the point is not inserted into the set.
     * 
     * \param Point2D Point to be inserted into the tree.
     */
    void insert(const Point2D& p);

    /**
     * Determines if the given point is contained within the tree.
     * 
     * \param Point2D Point to query the tree.
     * 
     * \return True if the point is contained in the tree; false if not.
     */
    bool contains(const Point2D& p) const;

    /**
     * Determines the range of points contained within the given rectangle,
     * including the boundary.
     * 
     * \param Rectangle Rectangle to query tree.
     * 
     * \return Vector of points contained within the given rectangle. Empty
     *         vector if no points within the rectangle.
     */
    std::vector<Point2D> range(const Rectangle& r) const;

    /**
     * Determines the nearest point in the tree to the given point. Throws an
     * exception if the tree is empty.
     * 
     * \param Point2D Point to query the tree.
     * 
     * \return Point nearest to the given point.
     */
    Point2D nearest(const Point2D& p) const;

    // output operator
    friend std::ostream& operator<<(std::ostream& out, const KDTree& ps);

    // copying, assigning, moving a PointSET is not supported
    KDTree(const KDTree& tree) = delete;
    KDTree(KDTree& tree) = delete;
    KDTree& operator=(const KDTree& tree) = delete;
    KDTree& operator=(KDTree& tree) = delete;

private:

    // represents a single node within the KDTree
    class KDNode {
    public:

        KDNode(const Point2D& p, const Rectangle& r);
        ~KDNode();

        const Point2D&   point() const     { return m_point; }
        const Rectangle& rectangle() const { return m_rectangle; }

        KDNode* lb() { return m_lb; }
        KDNode* rt() { return m_rt; }
        const KDNode* lb() const { return m_lb; }
        const KDNode* rt() const { return m_rt; }

        void set_lb(KDNode* node) { m_lb = node; }
        void set_rt(KDNode* node) { m_rt = node; }

        // copying, assigning, moving a KDNode is not supported
        KDNode(const KDNode& node) = delete;
        KDNode(KDNode& node) = delete;
        KDNode& operator=(const KDNode& node) = delete;
        KDNode& operator=(KDNode& node) = delete;

    private:

        Point2D   m_point{};
        Rectangle m_rectangle{};

        KDNode* m_lb{}; // left/bottom subtree
        KDNode* m_rt{}; // right/top subtree
    };

    void   insert(KDTree::KDNode* node, const Point2D& p, int level);
    bool contains(KDTree::KDNode* node, const Point2D& p, int level) const;

    void   range(const KDTree::KDNode* node,
                 const Rectangle& r,
                 std::vector<Point2D>& points) const;
    void nearest(const KDTree::KDNode* node,
                 const Point2D& p,
                 Point2D& pnearest,
                 int level) const;

    KDNode* createNewNode(
                const Point2D& p,
                const Rectangle& r = Rectangle::unitSquareRectangle()) const;

    void printTree(std::ostream& out) const;
    void printNode(std::ostream& out, KDNode* node, int level) const;

    KDNode* m_root{};
    int     m_num_nodes{};

};

#endif // KD_TREE_H
