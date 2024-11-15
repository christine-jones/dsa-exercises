/**
 * \file    Rectangle.h
 * \author  Christine Jones 
 * \brief   Clas that represents a two-dimensional axis-aligned rectangle with
 *          real-value coordinates.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Point2D.h"
#include <iostream>

/**
 * Class that represents a two-dimensional axis-aligned rectangle with
 * real-value coordinates. The rectangle is closed, i.e., it includes the
 * points on the boundary.
 */
class Rectangle {

public:

    /**
     * Constructor. Instantiates a rectangle at [0, 0] X [0, 0].
     */
    Rectangle();

    /**
     * Constructor. Instantiates a rectangle at [xmin, xmax] X [ymin, ymax].
     * 
     * \param double x-coordinate of the lower-left endpoint
     * \param double y-coordinate of the lower-left endpoint
     * \param double x-coordinate of the upper-right endpoint; must be greater
     *               or equal to xmin
     * \param double y-coordinate of the upper-right endpoint; must be greater
     *               or equal to ymin
     */
    Rectangle(double xmin, double ymin, double xmax, double ymax);

    //accessors
    double xmin() const { return m_xmin; }
    double ymin() const { return m_ymin; }
    double xmax() const { return m_xmax; }
    double ymax() const { return m_ymax; }

    /**
     * Determines if the given point is contained within the rectangle,
     * including the boundary of the rectangle.
     * 
     * \param Point2D two-dimensional point
     * 
     * \returns True if the point is contained within the rectangle; false
     *          if not. 
     */
    bool contains(const Point2D& p) const;

    /**
     * Determines if this and the given rectangle intersect. Includes improper
     * intersections (at points on the boundary of each rectangle) and nested
     * intersections (when one rectangle is contained inside the other).
     * 
     * \param Rectangle rectangle
     * 
     * \return True if the rectangles intersect; false if not.
     */
    bool intersects(const Rectangle& r) const;

    /**
     * Determines the Euclidean distance between the given point and the
     * closest point on the rectangle. The distance is 0 if the point is
     * contained within the rectangle.
     * 
     * 
     * \param Point2D two-dimensional point from which to calculate distance
     * 
     * \return Euclidean distance between point and rectangle; 0 if the point
     *         is contained within the rectangle.
     */
    double distanceTo(const Point2D& p) const;

    /**
     * Determines the square of the Euclidean distance between the given point
     * and the closes point on the rectangle. The distance is 0 if the point is
     * contained within the rectangle.
     * 
     * \param Point2D two-dimensional point from which to calculate distance
     * 
     * \return Square of the Euclidean distance between point and rectangle;
     *         0 if the point is contained within the rectangle.
     */
    double distanceSquaredTo(const Point2D& p) const;

    /**
     * Return a unit square; xmin = ymin = 0 and xmax = ymax = 1.
     * 
     * \return Rectangle with unit square coordinates.
     */
    static Rectangle unitSquareRectangle();

    /**
     * Determine if a the rectangle is contained within the unit square,
     * i.e., all x and y coordinates between 0 and 1, inclusive.
     * 
     * \return True if rectangle within unit square; false if not.
     */
    bool unitSquare() const;

    // comparison operators
    friend bool operator==(const Rectangle& r1, const Rectangle& r2);
    friend bool operator!=(const Rectangle& r1, const Rectangle& r2);

    // output operator
    friend std::ostream& operator<<(std::ostream& out, const Rectangle& r);

private:

    double m_xmin{};
    double m_ymin{};
    double m_xmax{};
    double m_ymax{};

};

#endif // RECTANGLE_H
