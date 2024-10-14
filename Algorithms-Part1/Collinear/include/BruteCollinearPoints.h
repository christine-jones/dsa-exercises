/**
 * \file    BruteCollinearPoints.h
 * \author  Christine Jones 
 * \brief
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef BRUTE_COLLINEAR_POINTS_H
#define BRUTE_COLLINEAR_POINTS_H

#include "LineSegment.h"
#include "Point.h"
#include <vector>

class BruteCollinearPoints {

public:

    BruteCollinearPoints(const std::vector<Point>& points);

    int numberOfSegments() const { return m_num_segments; }

    const std::vector<LineSegment>& segments() const { return m_segments; }

private:

    void findSegments();

    std::vector<Point>       m_points;

    int                      m_num_segments;
    std::vector<LineSegment> m_segments;

};

#endif // BRUTE_COLLINEAR_POINTS_H
