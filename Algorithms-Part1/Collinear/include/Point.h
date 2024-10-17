/**
 * \file    Point.h
 * \author  Christine Jones 
 * \brief   Class definition that represents an (x, y) point in a plane.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <vector>

/**
 * Class that represents an (x, y) point in a plane.
 */
class Point {

public:

    /**
     * Constructor. Instantiates a point (0, 0).
     */
    Point();

    /**
     * Constructor. Instantiates a point (x, y).
     * 
     * \param int x value.
     * \param int y value.
     */
    Point(int x, int y);

    /**
     * Calculates the slope between invoking point and the given point.
     * 
     * \param Point Point used to calculate slope.
     * 
     * \return Slope between points. Horizontal slope is 0; vertical slope is
     *         positive infinity; degenerate slope (i.e., between point and
     *         itself) is negative infinity.
     */
    double slope(const Point& p) const;

    /**
     * Compares the two given points with respect to the slope they make with
     * the invoking point. If the slopes are equal, the points are compared
     * using normal comparison operators.
     * 
     * \param Point
     * \param Point
     * 
     * \return True if p < q; False otherwise.
     */
    bool   slopeOrder(const Point& p, const Point& q) const;

    /**
     * Static method that sorts a vector of points.
     * 
     * \param std::vector<Point>& Points will be sorted into ascending order.
     */
    static void sortPoints(std::vector<Point>& points);

    /**
     * Static method that determines if a vector of points contains any
     * duplicate points.
     * 
     * NOTE: Assumes that the vector of points is already sorted.
     * 
     * \param const std::vector<Point>& Points to be insepcted for duplicates;
     *                                  will not be modified.
     * 
     * \return True if duplicate point exists; False if not.
     */
    static bool duplicatePoint(const std::vector<Point>& points);

    // comparison operators
    friend bool operator==(const Point& p1, const Point& p2);
    friend bool operator!=(const Point& p1, const Point& p2);
    friend bool operator< (const Point& p1, const Point& p2);
    friend bool operator> (const Point& p1, const Point& p2);
    friend bool operator<=(const Point& p1, const Point& p2);
    friend bool operator>=(const Point& p1, const Point& p2);

    // output operator
    friend std::ostream& operator<<(std::ostream& out, const Point& p);

private:

    int m_x{0};
    int m_y{0};

};

#endif // POINT_H
