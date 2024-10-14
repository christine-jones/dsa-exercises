/**
 * \file    LineSegment.h
 * \author  Christine Jones 
 * \brief   Class definitioin that represents a line segment in a plane.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef LINE_SEGMENT_H
#define LINE_SEGMENT_H

#include "Point.h"
#include <iostream>

class LineSegment {

public:

    LineSegment(const Point& p1, const Point& p2);

    friend std::ostream& operator<<(std::ostream& out, const LineSegment& ls);

private:

    Point m_p1;
    Point m_p2;

};

#endif // LINE_SEGMENT_H
