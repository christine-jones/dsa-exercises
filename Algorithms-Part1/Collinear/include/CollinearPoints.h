/**
 * \file    BruteCollinearPoints.h
 * \author  Christine Jones 
 * \brief   Classes that inspect points for line segments.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef COLLINEAR_POINTS_H
#define COLLINEAR_POINTS_H

#include "LineSegment.h"
#include "Point.h"
#include <vector>

/**
 * Base class to implement algorithms that inspect points in a plane for
 * line segments.
 */
class CollinearPoints {

public:

    /**
     * Constructor. Identifies line segments within the given vector of points.
     */
    explicit CollinearPoints(const std::vector<Point>& points);

    /**
     * Destructor.
     */
    virtual ~CollinearPoints() {}

    /**
     * Determines if duplicates exist in the instantiating vector of points.
     * 
     * \return True if duplicates exist; False if not.
     */
    bool duplicatePoints() const { return m_duplicate_points; }

    /**
     * Returns the number of line segments identified in the instantiating
     * vector of points.
     * 
     * \return Number of line segments.
     */
    int numberOfSegments() const { return m_num_segments; }

    /**
     * Returns a vector of the line segments identified in the instantiating
     * vector of points.
     * 
     * \return Constant vector of line segments.
     */
    const std::vector<LineSegment>& segments() const { return m_segments; }

protected:

    // minimum number of points required to form line segment
    static constexpr int min_segment_length{4};

    /**
     * Adds line segment to class vector of line segments.
     *
     * NOTE: Points must not be the same point.
     *  
     * \param Point Point forming line segment.
     * \param Point Point forming line segment.
     */
    void addSegment(const Point& p, const Point& q);

    /**
     * Virtual method for derived classes to implement an algorithm for
     * identifying line segments within the given vector of points.
     */
    virtual void findCollinearPoints() = 0;

    // points to inspect for line segments
    std::vector<Point>       m_points{};

private:

    bool                     m_duplicate_points{};
    int                      m_num_segments{};
    std::vector<LineSegment> m_segments{};

};

/**
 * Class that implements an algorithm that inspects points in a plane for
 * line segments.
 * 
 * The brute force algorithm inspects each combination of 4 points and checks
 * whether they all lie on the same line segment. Points p, q, r, and s are
 * collinear if the slopes between p and q, p and r, and p and s are all equal.
 * 
 * Each line segment is included exactly once. For example, a line segment
 * p -> q -> r -> s is inlcuded as line segment p -> s or s -> p, but not both,
 * and subsegments, e.g., q -> r, are not inlcuded.
 * 
 * For simplicity, this brute force algorithm does not consider line segments
 * greater than 4 points in length. Therefore, depending on the data input,
 * multiple overlapping line segments may be identified.
 * 
 * This brute force algorithm is provided for performance comparison with more
 * sophisticated algorithms. Therefore, time was not taken to better optimize
 * this algorithm.
 */
class BruteCollinearPoints : public CollinearPoints {

public:

    /**
     * Constructor. Identifies line segments within the given vector of points
     * using a brute force algorithm, O(n^4).
     */
    explicit BruteCollinearPoints(const std::vector<Point>& points);

protected:

    /**
     * Implements the algorithm for identifying line segments within the given
     * vector of points.
     */
    void findCollinearPoints() override;

};

/**
 * Class that implements an algorithm that inspects points in a plane for
 * line segments.
 * 
 * This algorithm uses a much faster, sorting-based solution. Given a base
 * point p, the following determines if p participates in a set of collinear
 * points.
 *  
 *  * For each other point q, determine the slope it makes with p.
 *  * Sort all points according to the slopes they make with p.
 *  * Check if any adjacent points in the sorted order have equal slopes with
 *    respect to p. If so, these point, together with p, form a line segment.
 * 
 * The above algorithm is applied to all n points in the data set to determine
 * all line segments formed by the points.
 * 
 * Each maximal line segment containing the configured minimum (e.g., 4) or
 * more points is included exactly once. For example, if 5 points form a line
 * segment in the order p -> q -> r -> s -> t, then p -> t or t -> p is
 * included, but not both, and subsegments, e.g.,  p -> s or q -> t, are not
 * included.
 */
class FastCollinearPoints : public CollinearPoints {

public:

    /**
     * Constructor. Identifies line segments within the given vector of points
     * using a faster, sorting-based algorithm, O(n^2log(n)).
     */
    explicit FastCollinearPoints(const std::vector<Point>& points);

protected:

    /**
     * Implements the algorithm for identifying line segments within the given
     * vector of points.
     */
    void findCollinearPoints() override;

private:

    void copySlopePoints(std::vector<Point>& s_points, std::size_t base_point);
    void processSegments(std::vector<Point>& s_points, std::size_t base_point);

};

#endif // COLLINEAR_POINTS_H
