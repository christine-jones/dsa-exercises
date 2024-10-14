/**
 * \file    Point.cpp
 * \author  Christine Jones 
 * \brief   Class implementation that represents an (x, y) point in a plane.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "Point.h"
#include <algorithm>    // for std::sort, std::adjacent
#include <cassert>

double Point::slope(const Point& p) const {

    assert(p != *this);

    // TBD: handle vertically aligned points, for now return 0
    if (p.m_x == m_x)
        return 0;

    return (static_cast<double>(p.m_y) - static_cast<double>(m_y)) /
           (static_cast<double>(p.m_x) - static_cast<double>(m_x));
}

bool operator==(const Point& p1, const Point& p2) {

    return (p1.m_x == p2.m_x) && (p1.m_y == p2.m_y);
}

bool operator!=(const Point& p1, const Point& p2) {

    return !(operator==(p1, p2));
}

bool operator< (const Point& p1, const Point& p2) {

    return (p1.m_y < p2.m_y) || ((p1.m_y == p2.m_y) && (p1.m_x < p2.m_x));
}

bool operator> (const Point& p1, const Point& p2) {

    return operator<(p2, p1);
}

bool operator<=(const Point& p1, const Point& p2) {

    return !(operator>(p1, p2));
}

bool operator>=(const Point& p1, const Point& p2) {

    return !(operator<(p1, p2));
}

std::ostream& operator<<(std::ostream& out, const Point& p) {

    out << "(" << p.m_x << ", " << p.m_y << ")";
    return out;
}

void Point::sortPoints(std::vector<Point>& points) {

    // std::sort is O(NlogN)
    std::sort(points.begin(), points.end());
}

bool Point::duplicatePoint(const std::vector<Point>& points) {

    // check for duplicate, std::adjacent_find is O(N)
    if (std::adjacent_find(points.begin(), points.end()) != points.end())
        return true;

    return false;
}
