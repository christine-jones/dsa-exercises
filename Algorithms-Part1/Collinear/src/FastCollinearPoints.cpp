/**
 * \file    FastCollinearPoints.cpp
 * \author  Christine Jones 
 * \brief
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "FastCollinearPoints.h"

FastCollinearPoints::FastCollinearPoints(const std::vector<Point>& points):
    m_points{points},
    m_num_segments{0},
    m_segments{}
{
    Point::sortPoints(m_points);

    if (Point::duplicatePoint(m_points)) {

        std::cerr << "FastCollinearPoints::BruteCollinearPoints: "
                  << "duplicate points" << '\n';
        throw std::invalid_argument("duplicate points in vector");
    }

    findSegments();
}

void FastCollinearPoints::findSegments() {

    // vector of points already sorted with no duplicates

}
