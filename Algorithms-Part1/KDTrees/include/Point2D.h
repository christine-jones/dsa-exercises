/**
 * \file    Point2D.h
 * \author  Christine Jones 
 * \brief   Class that represents a two-dimensional point with real-value
 *          coordinates.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef POINT_2D_H
#define POINT_2D_H

#include <iostream>

/**
 * Class that represents a two-dimensional point with real-value coordinates.
 */
class Point2D {

public:

    /**
     * Constructor. Instantiates a point at the origin (0, 0).
     */
    Point2D();

    /**
     * Constructor. Instantiates a point at the given (x, y).
     * 
     * \param double x-coordinate
     * \param double y-coordinate
     */
    Point2D(double x, double y);

    // accessors
    double x() const { return m_x; }
    double y() const { return m_y; }

    /**
     * Determine if the point is contained within the unit square, i.e., 
     * x and y coordinate between 0 and 1, inclusive.
     * 
     * \return True if point within unit square; false if not.
     */
    bool unitSquare() const;

    /**
     * Calculates the Euclidean distance between this and the given point.
     * 
     * \param Point2D Point from which to calculate distance.
     * 
     * \return Euclidean distance between points.
     */
    double distanceTo(const Point2D& p) const;

    /**
     * Calculates the square of the Euclidean distance between this and the
     * given point.
     * 
     * \param Point2D Point from which to calculate distance.
     * 
     * \return Square of Euclidean distance between points.
     */
    double distanceSquaredTo(const Point2D& p) const;

    /**
     * By default, points are compared by y coordinate first, followed by the
     * x coordinate. These methods allow for the explicit use of either the 
     * x or y coordinate to have priority in comparison
     * 
     * \param Point2D Point to be compared.
     * \param Point2D Point to be compared.
     * 
     * \return 0 if points equal, less than 0 if p1 is less than p2, and
     *         greater than 0 if p1 is greater than p2
     */
    static int compareByX(const Point2D& p1, const Point2D& p2);
    static int compareByY(const Point2D& p1, const Point2D& p2);

    // comparison operators
    friend bool operator==(const Point2D& p1, const Point2D& p2);
    friend bool operator!=(const Point2D& p1, const Point2D& p2);
    friend bool operator< (const Point2D& p1, const Point2D& p2);
    friend bool operator> (const Point2D& p1, const Point2D& p2);
    friend bool operator<=(const Point2D& p1, const Point2D& p2);
    friend bool operator>=(const Point2D& p1, const Point2D& p2);

    // output operator
    friend std::ostream& operator<<(std::ostream& out, const Point2D& p);

private:

    double m_x{};
    double m_y{};

};

#endif // POINT_2D_H
