/**
 * \file    FastCollinearPoints.h
 * \author  Christine Jones 
 * \brief
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef FAST_COLLINEAR_POINTS_H
#define FAST_COLLINEAR_POINTS_H

#include "LineSegment.h"
#include "Point.h"
#include <vector>

class FastCollinearPoints {

public:

    FastCollinearPoints(const std::vector<Point>& points);

    int numberOfSegments() const { return m_num_segments; }

    const std::vector<LineSegment>& segments() const { return m_segments; }

private:

    void findSegments();

    void copySlopePoints(std::vector<Point>& s_points, std::size_t base_point);

    std::vector<Point>       m_points;

    int                      m_num_segments;
    std::vector<LineSegment> m_segments;

};

#endif // FAST_COLLINEAR_POINTS_H
