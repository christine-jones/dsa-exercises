/**
 * \file    BruteCollinearPoints.cpp
 * \author  Christine Jones 
 * \brief
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "BruteCollinearPoints.h"
#include <exception>

BruteCollinearPoints::BruteCollinearPoints(const std::vector<Point>& points):
    m_points{points},
    m_num_segments{0},
    m_segments{}
{

    Point::sortPoints(m_points);
    
    if (Point::duplicatePoint(m_points)) {

        std::cerr << "BruteCollinearPoints::BruteCollinearPoints: "
                  << "duplicate points" << '\n';
        throw std::invalid_argument("duplicate points in vector");
    }

    findSegments();
}

void BruteCollinearPoints::findSegments() {

    // vector of points already sorted with no duplicates

    for (std::size_t i{0}; i < m_points.size(); ++i)
        for (std::size_t j{i + 1}; j < m_points.size(); ++j)
            for (std::size_t k{j + 1}; k < m_points.size(); ++k)
                for (std::size_t m{k + 1}; m < m_points.size(); ++m) {

        if (m_points[i].slope(m_points[j]) == m_points[i].slope(m_points[k]) &&
            m_points[i].slope(m_points[k]) == m_points[i].slope(m_points[m])) {

            m_segments.emplace_back(m_points[i], m_points[m]);
            ++m_num_segments;
        }
    }
}
