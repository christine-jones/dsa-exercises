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

KDTree::KDNode::KDNode(const Point2D& p, const Rectangle& r):
    m_point{p},
    m_rectangle{r},
    m_lb{nullptr},
    m_rt{nullptr}
{
    assert(Point2D::validUnitSquarePoint(p));
    assert(Rectangle::validUnitSquareRectangle(r));
}

KDTree::KDNode::~KDNode() {

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

    if (!Point2D::validUnitSquarePoint(p)) {
        std::cerr << "KDTree::insert: point not in unit square" << '\n';
        return;
    }

    if (isEmpty()) {
        m_root = createNewNode(p);
        ++m_num_nodes;
        return;
    }

    insert(m_root, p, 0);
}

void KDTree::insert(KDTree::KDNode* node, const Point2D& p, int level) {

    assert(node);

    bool ylevel{static_cast<bool>(level % 2)};
    int  cmp{ylevel ? Point2D::compareByY(p, node->point()) :
                      Point2D::compareByX(p, node->point())};

    if (cmp < 0) {

        if (!node->lb()) {
            node->set_lb(
                createNewNode(p, Rectangle{
                                    node->rectangle().xmin(),
                                    node->rectangle().ymin(),
                                    (ylevel ? node->rectangle().xmax() :
                                              node->point().x()),
                                    (ylevel ? node->point().y() :
                                              node->rectangle().ymax())}));
                ++m_num_nodes;
        
        } else insert(node->lb(), p, level + 1);

    } else if (cmp > 0) {

        if (!node->rt()) {
            node->set_rt(
                createNewNode(p, Rectangle(
                                    (ylevel ? node->rectangle().xmin() :
                                              node->point().x()),
                                    (ylevel ? node->point().y() :
                                              node->rectangle().ymin()),
                                    node->rectangle().xmax(),
                                    node->rectangle().ymax())));
                ++m_num_nodes;

        } else insert(node->rt(), p, level + 1);
        
    } else {
        assert(p == node->point());
        std::cerr << "KDTree::insert: duplicate point" << '\n';
    }
}

bool KDTree::contains(const Point2D& p) const {

    if (!Point2D::validUnitSquarePoint(p)) {
        std::cerr << "KDTree::contains: point not in unit square" << '\n';
        return false;
    }

    return contains(m_root, p, 0);
}

bool KDTree::contains(KDTree::KDNode* node,
                      const Point2D& p,
                      int level) const {

    if (!node)
        return false;

    int cmp{(level % 2) ? Point2D::compareByY(p, node->point()) :
                          Point2D::compareByX(p, node->point())};

    if      (cmp < 0) return contains(node->lb(), p, level + 1);
    else if (cmp > 0) return contains(node->rt(), p, level + 1);
    else {
        assert(p == node->point());
        return true;
    }
}

std::vector<Point2D> KDTree::range(const Rectangle& r) const {

    std::vector<Point2D> prange{};
    range(m_root, r, prange);
    return prange;
}

void KDTree::range(const KDNode* node,
                   const Rectangle& r,
                   std::vector<Point2D>& points) const {

    if (!node)
        return;

    if (!r.intersects(node->rectangle()))
        return;

    if (r.contains(node->point()))
        points.push_back(node->point());

    range(node->lb(), r, points);
    range(node->rt(), r, points);
}

Point2D KDTree::nearest(const Point2D& p) const {

    if (isEmpty()) {
        std::cerr << "PointSET::nearest: set is empty" << '\n';
        throw std::out_of_range("point set empty, no such element");
    }

    Point2D pnearest{m_root->point()};
    nearest(m_root, p, pnearest, 0);
    return pnearest;
}

void KDTree::nearest(const KDTree::KDNode* node,
                     const Point2D& p,
                     Point2D& pnearest,
                     int level) const {

    if (!node)
        return;

    if (p.distanceTo(pnearest) < node->rectangle().distanceTo(p))
        return;

    if (p.distanceTo(node->point()) < p.distanceTo(pnearest))
        pnearest = node->point();

    int cmp{(level % 2) ? Point2D::compareByY(p, node->point()) :
                          Point2D::compareByX(p, node->point())};

    if (cmp < 0) {
        nearest(node->lb(), p, pnearest, level + 1);
        nearest(node->rt(), p, pnearest, level + 1);

    } else if (cmp > 0) {
        nearest(node->rt(), p, pnearest, level + 1);
        nearest(node->lb(), p, pnearest, level + 1);


    } else {
        assert(p == node->point()); // can't get closer than this
        return;
    }
}

KDTree::KDNode*
KDTree::createNewNode(const Point2D& p, const Rectangle& r) const {

    KDNode* new_node = new (std::nothrow) KDNode{p, r};
    if (!new_node) {
        std::cerr << "KDTree::createNewNode: " 
                  << "failed to allocate memory for new node" << '\n';
    }

    return new_node;
}

void KDTree::printTree(std::ostream& out) const {

    printNode(out, m_root, 0);
}

void KDTree::printNode(std::ostream& out,
                       KDTree::KDNode* node,
                       int level) const {

    if (!node) {
        out << '\n';
        return;
    }

    out << node->point() << ": " << node->rectangle() << '\n';

    for (int i{0}; i < level; ++i)
        out << '\t';
    out << "L" << level + 1 << ": ";
    printNode(out, node->lb(), level + 1);

    for (int i{0}; i < level; ++i)
        out << '\t';
    out << "R" << level + 1 << ": ";
    printNode(out, node->rt(), level + 1);
}

std::ostream& operator<<(std::ostream& out, const KDTree& t) {

    t.printTree(out);
    return out;
}
