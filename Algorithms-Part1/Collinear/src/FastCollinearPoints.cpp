/**
 * \file    FastCollinearPoints.cpp
 * \author  Christine Jones 
 * \brief
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "FastCollinearPoints.h"
#include <algorithm>    // for std::sort, std::equal_range
#include <cassert>
#include <iterator>     // for std::distance, std::prev

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

    findCollinearPoints();
}

void FastCollinearPoints::findCollinearPoints() {

    // vector of points already sorted with no duplicates

    // holds points sorted by slope with respect to a given base point
    std::vector<Point> s_points(m_points.size() - 1);

    for (std::size_t i{0}; i < m_points.size(); ++i) {

        copySlopePoints(s_points, i);

        std::sort(s_points.begin(), s_points.end(),
                  [this, i](const auto& p, const auto& q) {
                        return this->m_points[i].slopeOrder(p, q); 
                  });

        processSegments(s_points, i);        
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

void FastCollinearPoints::processSegments(std::vector<Point>& s_points,
                                          std::size_t base_point) {

    struct SlopeComp {

        bool operator()(const Point& p, double slope)
            { return m_base_point.slope(p) < slope; }
        bool operator()(double slope, const Point& p)
            { return slope < m_base_point.slope(p); }

        Point m_base_point{};
    };

    auto it = s_points.begin();
    while (it != s_points.end()) {

        auto segment{std::equal_range(it, s_points.end(),
                                      m_points[base_point].slope(*it),
                                      SlopeComp{m_points[base_point]})};

        if (std::distance(segment.first,
                          segment.second) >= (min_segment_length - 1) &&
            m_points[base_point] < *it) {
                            
            m_segments.emplace_back(m_points[base_point],
                                    *std::prev(segment.second));
            ++m_num_segments;
        }

        it = segment.second;
    }
}
