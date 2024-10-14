/**
 * \file    FastCollinearPoints.cpp
 * \author  Christine Jones 
 * \brief
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "FastCollinearPoints.h"
#include <algorithm>    // for std::sort
#include <cassert>

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

    // holds points sorted by slope with respect to a given point
    std::vector<Point> s_points(m_points.size() - 1);

    for (std::size_t i{0}; i < m_points.size(); ++i) {

        copySlopePoints(s_points, i);

        std::sort(s_points.begin(), s_points.end(),
                  [this, i](const auto& p, const auto& q) {
                        return this->m_points[i].slopeOrder(p, q); 
                  });
    }
}

void FastCollinearPoints::copySlopePoints(std::vector<Point>& s_points,
                                          std::size_t base_point) {

    assert(s_points.size() == (m_points.size() - 1));

    for (std::size_t j{0}, k{0}; j < s_points.size(); ) {

            if (k == base_point) {
                ++k;
                continue;
            }

            s_points[j++] = m_points[k++];
    }
}
