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
#include <exception>
#include <iostream>
#include <vector>

KDTree::KDTree()
{}

void KDTree::insert(const Point2D& p) {

    // no duplicates allowed
    if (contains(p))
        return;
}

bool KDTree::contains(const Point2D& p) const {

    return false;
}

std::vector<Point2D> KDTree::range(const Rectangle& r) const {

    return std::vector<Point2D>{};
}

Point2D KDTree::nearest(const Point2D& p) const {

    if (isEmpty()) {
        std::cerr << "PointSET::nearest: set is empty" << '\n';
        throw std::out_of_range("point set empty, no such element");
    }

    return Point2D{};
}

std::ostream& operator<<(std::ostream& out, const KDTree& t) {

    return out;
}
