/**
 * \file    BruteCollinearPoints.h
 * \author  Christine Jones 
 * \brief
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef COLLINEAR_POINTS_H
#define COLLINEAR_POINTS_H

#include "LineSegment.h"
#include "Point.h"
#include <vector>

class CollinearPoints {

public:

    explicit CollinearPoints(const std::vector<Point>& points);

    virtual ~CollinearPoints() {}

    int numberOfSegments() const { return m_num_segments; }
    bool duplicatePoints() const { return m_duplicate_points; }
    const std::vector<LineSegment>& segments() const { return m_segments; }

protected:

    static constexpr int min_segment_length{4};

    void addSegment(const Point& p, const Point& q);

    virtual void findCollinearPoints() = 0;

    std::vector<Point>       m_points{};

private:

    bool                     m_duplicate_points{};
    int                      m_num_segments{};
    std::vector<LineSegment> m_segments{};

};

class BruteCollinearPoints : public CollinearPoints {

public:

    explicit BruteCollinearPoints(const std::vector<Point>& points);

protected:

    void findCollinearPoints() override;

};

class FastCollinearPoints : public CollinearPoints {

public:

    explicit FastCollinearPoints(const std::vector<Point>& points);

protected:

    void findCollinearPoints() override;

private:

    void copySlopePoints(std::vector<Point>& s_points, std::size_t base_point);
    void processSegments(std::vector<Point>& s_points, std::size_t base_point);

};

#endif // COLLINEAR_POINTS_H
