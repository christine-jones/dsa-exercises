/**
 * \file    Rectangle.cpp
 * \author  Christine Jones 
 * \brief   Clas that represents a two-dimensional axis-aligned rectangle with
 *          real-value coordinates.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "Rectangle.h"
#include "Point2D.h"
#include <algorithm>    // std::min
#include <cassert>
#include <cmath>        // std::pow, std::sqrt, std::abs
#include <iostream>

Rectangle::Rectangle():
    m_xmin{0},
    m_ymin{0},
    m_xmax{0},
    m_ymax{0}
{}

Rectangle::Rectangle(double xmin, double ymin, double xmax, double ymax):
    m_xmin{xmin},
    m_ymin{ymin},
    m_xmax{xmax},
    m_ymax{ymax}
{
    assert(m_xmin <= m_xmax);
    assert(m_ymin <= m_ymax);
}

bool Rectangle::contains(const Point2D& p) const {

    return (p.x() >= m_xmin) && (p.x() <= m_xmax) &&
           (p.y() >= m_ymin) && (p.y() <= m_ymax);
}

bool Rectangle::intersects(const Rectangle& r) const {

    return !(m_xmin > r.m_xmax ||
             m_xmax < r.m_xmin ||
             m_ymax < r.m_ymin ||
             m_ymin > r.m_ymax);
}

double Rectangle::distanceTo(const Point2D& p) const {

    return std::sqrt(distanceSquaredTo(p));
}

double Rectangle::distanceSquaredTo(const Point2D& p) const {

    // point inside rectangle
    if (contains(p))
        return 0;

    // point in vertical corridor
    if (p.x() >= m_xmin && p.x() <= m_xmax)
        return std::min(std::pow(std::abs(m_ymax - p.y()), 2),
                        std::pow(std::abs(m_ymin - p.y()), 2));

    // point in horizontal corridor
    if (p.y() >= m_ymin && p.y() <= m_ymax)
        return std::min(std::pow(std::abs(m_xmax - p.x()), 2),
                        std::pow(std::abs(m_xmin - p.x()), 2));

    // point not in corridor, find distance to nearest corner
    Point2D corner{(p.x() > m_xmax) ? m_xmax : m_xmin,
                   (p.y() > m_ymax) ? m_ymax : m_ymin};
    return corner.distanceSquaredTo(p);
}

Rectangle Rectangle::unitSquareRectangle() {

    return Rectangle{0, 0, 1, 1};
}

bool Rectangle::unitSquare() const {

    return m_xmin >= 0 && m_ymin >= 0 && m_xmax <=1 && m_ymax <=1;
}

bool operator==(const Rectangle& r1, const Rectangle& r2) {

    return (r1.m_xmin == r2.m_xmin) && (r1.m_xmax == r2.m_xmax) &&
           (r1.m_ymin == r2.m_ymin) && (r1.m_ymax == r2.m_ymax);
}

bool operator!=(const Rectangle& r1, const Rectangle& r2) {

    return !(operator==(r1, r2));
}

std::ostream& operator<<(std::ostream& out, const Rectangle& r) {

    out << "[" << r.m_xmin << ", " << r.m_xmax << "]"
        << " X "
        << "[" << r.m_ymin << ", " << r.m_ymax << "]";
    return out;
}
