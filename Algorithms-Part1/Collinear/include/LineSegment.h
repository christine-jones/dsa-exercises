/**
 * \file    LineSegment.h
 * \author  Christine Jones 
 * \brief   Class definition that represents a line segment in a plane.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef LINE_SEGMENT_H
#define LINE_SEGMENT_H

#include "Point.h"
#include <iostream>

/**
 * Class that represents a line segment between two points in a plane.
 */
class LineSegment {

public:

    /**
     * Constructor. Instantiates a line segment between two given points.
     * 
     * NOTE: Two given points MUST NOT be the same point.
     * 
     * \param Point
     * \param Point
     */
    LineSegment(const Point& p1, const Point& p2);

    // output operator
    friend std::ostream& operator<<(std::ostream& out, const LineSegment& ls);

private:

    Point m_p1{};
    Point m_p2{};

};

#endif // LINE_SEGMENT_H
