/**
 * \file    KDTree.cpp
 * \author  Christine Jones 
 * \brief   Class that represents a set of points in the unit square using a
 *          2D-tree.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "KDTree.h"
#include "Point2D.h"
#include "Rectangle.h"
#include <cassert>
#include <exception>
#include <iostream>
#include <vector>

KDTree::KDNode::KDNode(const Point2D& p):
    m_point{p},
    m_rectangle{0, 0, 1, 1},
    m_lb{nullptr},
    m_rt{nullptr}
{
    assert(Point2D::validUnitSquarePoint(p));
}

KDTree::KDNode::~KDNode() {

    std::cout << "Deleteing " << m_point << '\n';

    if (m_lb) {
        delete m_lb;
        m_lb = nullptr;
    }

    if (m_rt) {
        delete m_rt;
        m_rt = nullptr;
    }
}

KDTree::KDTree():
    m_root{nullptr},
    m_num_nodes{0}
{}

KDTree::~KDTree()
{
    if (m_root) {
        delete m_root;
        m_root = nullptr;
    }
}

void KDTree::insert(const Point2D& p) {

    std::cout << "Inserting " << p << '\n';

    if (!Point2D::validUnitSquarePoint(p)) {
        std::cerr << "KDTree::insert: point not in unit square" << '\n';
        return;
    }

    if (isEmpty()) {
        m_root = createNewNode(p);
        ++m_num_nodes;
        return;
    }

    KDNode* node{m_root};
    int level{0};

    while (node != nullptr) {

        double p_coord{(level % 2) ? p.y() : p.x()};
        double n_coord{(level % 2) ? node->point().y() : node->point().x()};

        if (p_coord < n_coord) {

            if (!node->lb()) {
                node->set_lb(createNewNode(p));
                break;
            }
            node = node->lb();

        } else if (p_coord > n_coord) {

            if (!node->rt()) {
                node->set_rt(createNewNode(p));
                break;
            }
            node = node->rt();
        
        } else {
            assert(p == node->point());
            std::cerr << "KDTree::insert: duplicate point" << '\n';
            return;
        }

        ++level;
    }

    ++m_num_nodes;
}

bool KDTree::contains(const Point2D& p) const {

    if (!Point2D::validUnitSquarePoint(p)) {
        std::cerr << "KDTree::contains: point not in unit square" << '\n';
        return false;
    }

    KDNode* node{m_root};
    int level{0};

    while (node != nullptr) {

        double p_coord{(level % 2) ? p.y() : p.x()};
        double n_coord{(level % 2) ? node->point().y() : node->point().x()};

        if      (p_coord < n_coord) node = node->rt();
        else if (p_coord > n_coord) node = node->lb();
        else {
            assert(p == node->point());
            return true;
        }

        ++level;
    }

    return false;
}

std::vector<Point2D> KDTree::range([[maybe_unused]] const Rectangle& r) const {

    return std::vector<Point2D>{};
}

Point2D KDTree::nearest([[maybe_unused]] const Point2D& p) const {

    if (isEmpty()) {
        std::cerr << "PointSET::nearest: set is empty" << '\n';
        throw std::out_of_range("point set empty, no such element");
    }

    return Point2D{};
}

void KDTree::printTree(std::ostream& out) const {

    printNode(out, m_root);
}

KDTree::KDNode* KDTree::createNewNode(const Point2D& p) {

    KDNode* new_node = new (std::nothrow) KDNode{p};
    if (!new_node) {
        std::cerr << "KDTree::createNewNode: " 
                  << "failed to allocate memory for new node" << '\n';
    }

    return new_node;
}

void KDTree::printNode(std::ostream& out, KDTree::KDNode* node) const {

    if (!node)
        return;

    out << node->point();
    out << " [";
    printNode(out, node->lb());
    out << ", ";
    printNode(out, node->rt());
    out << "] ";
}

std::ostream& operator<<(std::ostream& out, const KDTree& t) {

    t.printTree(out);
    return out;
}
