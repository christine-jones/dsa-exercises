/**
 * \file    BruteCollinearPoints.cpp
 * \author  Christine Jones 
 * \brief   Classes that inspect points for line segments.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "CollinearPoints.h"
#include <algorithm>    // for std::sort, std::equal_range
#include <cassert>
#include <iterator>     // for std::distance, std::prev

CollinearPoints::CollinearPoints(const std::vector<Point>& points):
    m_points{points},
    m_duplicate_points{false},
    m_num_segments{0},
    m_segments{}
{

    Point::sortPoints(m_points);
    
    if (Point::duplicatePoint(m_points))
        m_duplicate_points = true;
}

void CollinearPoints::addSegment(const Point& p, const Point& q) {

    assert(p != q);

    m_segments.emplace_back(p, q);
    ++m_num_segments;
}

BruteCollinearPoints::BruteCollinearPoints(const std::vector<Point>& points):
    CollinearPoints{points}
{
    if (!duplicatePoints())
        findCollinearPoints();
}

void BruteCollinearPoints::findCollinearPoints() {

    // vector of points already sorted with no duplicates

    for (std::size_t i{0}; i < m_points.size(); ++i)
        for (std::size_t j{i + 1}; j < m_points.size(); ++j)
            for (std::size_t k{j + 1}; k < m_points.size(); ++k)
                for (std::size_t m{k + 1}; m < m_points.size(); ++m) {

        if (m_points[i].slope(m_points[j]) == m_points[i].slope(m_points[k]) &&
            m_points[i].slope(m_points[k]) == m_points[i].slope(m_points[m])) {

            addSegment(m_points[i], m_points[m]);
        }
    }
}

FastCollinearPoints::FastCollinearPoints(const std::vector<Point>& points):
    CollinearPoints{points}
{
    if (!duplicatePoints())
        findCollinearPoints();
}

void FastCollinearPoints::findCollinearPoints() {

    // vector of points already sorted with no duplicates

    // points sorted by slope with respect to a given base point
    std::vector<Point> s_points(m_points.size() - 1);

    for (std::size_t bp{0}; bp < m_points.size(); ++bp) {

        // bp is the index to the base point

        copySlopePoints(s_points, bp);

        std::sort(s_points.begin(), s_points.end(),
                  [this, bp](const auto& p, const auto& q) {
                        return this->m_points[bp].slopeOrder(p, q); 
                  });

        processSegments(s_points, bp);        
    }
}

void FastCollinearPoints::copySlopePoints(std::vector<Point>& s_points,
                                          std::size_t base_point) {

    assert(s_points.size() == (m_points.size() - 1));

    for (std::size_t j{0}, k{0}; j < s_points.size(); ) {

            // don't copy the base point
            if (k == base_point) {
                ++k;
                continue;
            }

            s_points[j++] = m_points[k++];
    }
}

void FastCollinearPoints::processSegments(std::vector<Point>& s_points,
                                          std::size_t base_point) {

    // comparator for heterogenous comparison of points by slope
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

        // line segments must be >= in length to configured minimum segment
        // length; use (min_segment_length - 1) because base point not included
        // in the point range
        if (std::distance(segment.first,
                          segment.second) >= (min_segment_length - 1)) {

            // to prevent duplicate line segments, only include line segments 
            // in which the base point forms the lower endpoint
            if (m_points[base_point] < *it) {

                addSegment(m_points[base_point], *std::prev(segment.second));
            }
        }

        it = segment.second;
    }
}
