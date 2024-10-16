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
#include <limits>       // for infinity()

Point::Point():
    m_x{0},
    m_y{0}
{}

Point::Point(int x, int y):
    m_x{x},
    m_y{y}
{}

double Point::slope(const Point& p) const {

    // return negative infinity for point and itself, i.e., degenerate line
    if (p == *this)
        return -std::numeric_limits<double>::infinity();

    // return postive infinity for vertical slope
    if (p.m_x == m_x)
        return std::numeric_limits<double>::infinity();

    return (static_cast<double>(p.m_y) - static_cast<double>(m_y)) /
           (static_cast<double>(p.m_x) - static_cast<double>(m_x));
}

bool Point::slopeOrder(const Point& p, const Point& q) const {

    double p_slope{slope(p)};
    double q_slope{slope(q)};

    if (p_slope < q_slope)
        return true;

    if (q_slope < p_slope)
        return false;

    // slopes are equal, order on base point comparison
    return p < q;
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
