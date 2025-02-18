/**
 * \file    Point2D.cpp
 * \author  Christine Jones 
 * \brief   Class that represents a two-dimensional point with real-value
 *          coordinates.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "Point2D.h"
#include <cmath>        // std::pow, std::sqrt
#include <iostream>

Point2D::Point2D():
    m_x{0},
    m_y{0}
{}

Point2D::Point2D(double x, double y):
    m_x{x},
    m_y{y}   
{}

bool Point2D::unitSquare() const {

    return (m_x >= 0 && m_x <= 1) && (m_y >= 0 && m_y <= 1);
}

double Point2D::distanceTo(const Point2D& p) const {

    return std::sqrt(distanceSquaredTo(p));
}

double Point2D::distanceSquaredTo(const Point2D& p) const {

    return std::pow(p.m_x - m_x, 2) + std::pow(p.m_y - m_y, 2);
}

int Point2D::compareByX(const Point2D& p1, const Point2D& p2) {

    if (p1 == p2)
        return 0;

    // p1 < p2
    if ((p1.x() < p2.x()) || ((p1.x() == p2.x()) && (p1.y() < p2.y())))
        return -1;

    // p1 > p2
    return 1;
}

int Point2D::compareByY(const Point2D& p1, const Point2D& p2) {

    if (p1 == p2)
        return 0;

    if (p1 < p2)
        return -1;

    // p1 > p2
    return 1;
}

bool operator==(const Point2D& p1, const Point2D& p2) {

    return (p1.m_x == p2.m_x) && (p1.m_y == p2.m_y);
}

bool operator!=(const Point2D& p1, const Point2D& p2) {

    return !(operator==(p1, p2));
}

bool operator<(const Point2D& p1, const Point2D& p2) {

    return (p1.m_y < p2.m_y) || ((p1.m_y == p2.m_y) && (p1.m_x < p2.m_x));
}

bool operator>(const Point2D& p1, const Point2D& p2) {

    return operator<(p2, p1);
}

bool operator<=(const Point2D& p1, const Point2D& p2) {

    return !(operator>(p1, p2));
}

bool operator>=(const Point2D& p1, const Point2D& p2) {

    return !(operator<(p1, p2));
}

std::ostream& operator<<(std::ostream& out, const Point2D& p) {

    out << "(" << p.m_x << ", " << p.m_y << ")";
    return out;
}
