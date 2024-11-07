/**
 * \file    PointSet.cpp
 * \author  Christine Jones 
 * \brief   Class that represents a set of points in the unit square using a
 *          red-black BST.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "Point2D.h"
#include "PointSet.h"
#include "Rectangle.h"
#include <exception>
#include <iostream>
#include <set>
#include <vector>

PointSET::PointSET():
    m_pset{}
{}

void PointSET::insert(const Point2D& p) {

    if (!Point2D::validUnitSquarePoint(p)) {
        std::cerr << "PointSET::insert: point not in unit square" << '\n';
        return;
    }

    if (contains(p)) {
        std::cerr << "PointSET::insert: duplicate point" << '\n';
        return;
    }

    m_pset.insert(p);
}

bool PointSET::contains(const Point2D& p) const {

    return m_pset.find(p) != m_pset.end();
}

std::vector<Point2D> PointSET::range(const Rectangle& r) const {

    if (!Rectangle::validUnitSquareRectangle(r)) {
        std::cerr << "PointSET::range: rectangle not in unit square" << '\n';
        return std::vector<Point2D>{};
    }

    std::vector<Point2D> prange{};

    for (const auto& p : m_pset) {
        if (r.contains(p))
            prange.push_back(p);
    }

    return prange;
}

Point2D PointSET::nearest(const Point2D& p) const {

    if (!Point2D::validUnitSquarePoint(p)) {
        std::cerr << "PointSET::nearest: point not in unit square" << '\n';
        throw std::out_of_range("point not in unit square");
    } 

    if (isEmpty()) {
        std::cerr << "PointSET::nearest: set is empty" << '\n';
        throw std::out_of_range("point set empty, no such element");
    }

    // record distance of nearest point to reduce recalculations
    std::set<Point2D>::const_iterator pnearest{m_pset.cbegin()};
    double dnearest{(*pnearest).distanceTo(p)};

    for (std::set<Point2D>::const_iterator iter{++m_pset.cbegin()};
         iter != m_pset.cend(); ++iter) {

        if ((*iter).distanceTo(p) < dnearest) {
            pnearest = iter;
            dnearest = (*iter).distanceTo(p);
        }
    }

    return *pnearest;
}

std::ostream& operator<<(std::ostream& out, const PointSET& ps) {

    for (const auto& p : ps.m_pset)
        out << p << " ";
    out << '\n';

    return out;
}
