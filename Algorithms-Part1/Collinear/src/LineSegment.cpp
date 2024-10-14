/**
 * \file    LineSegment.cpp
 * \author  Christine Jones 
 * \brief   Class implementation that represents a line segment in a plane.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "LineSegment.h"
#include <exception>

LineSegment::LineSegment(const Point& p1, const Point& p2):
        m_p1{p1},
        m_p2{p2}
{
    if (p1 == p2) {

        std::cerr << "LineSegment::LineSegment: duplicate points" << '\n';
        throw std::invalid_argument("duplicate points as arguments");
    }
}

std::ostream& operator<<(std::ostream& out, const LineSegment& ls) {

    out << ls.m_p1 << " -> " << ls.m_p2;
    return out;
}
