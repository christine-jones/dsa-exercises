/**
 * \file    PointSet.h
 * \author  Christine Jones 
 * \brief   Class that represents a set of points in the unit square using a
 *          red-black BST.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef POINT_SET_H
#define POINT_SET_H

#include "Point2D.h"
#include "Rectangle.h"
#include <set>
#include <vector>

class PointSET {

public:

    /**
     * Constructor. Instantiates an empty set of points.
     */
    PointSET();

    /**
     * Determines if the set of points is empty.
     * 
     * \return True if the set is empty; false if not.
     */
    bool isEmpty() const { return m_pset.empty(); }

    /**
     * Determines the size of the point set.
     * 
     * \returns Number of points in the set.
     */
    int size() const { return static_cast<int>(m_pset.size()); }

    /**
     * Inserts the given point into the set. Must be unique, no duplicates
     * allowed. The point to be inserted must be within the unit square, i.e.,
     * x and y coordinates between 0 and 1, inclusive; if it is not in the unit
     * square, the point is not inserted into the set.
     * 
     * \param Point2D Point to be inserted into the set.
     */
    void insert(const Point2D& p);

    /**
     * Determines if the given point is contained within the set.
     * 
     * \param Point2D Point to query the set.
     * 
     * \return True if the point is contained in the set; false if not.
     */
    bool contains(const Point2D& p) const;


    /**
     * Determines the range of points contained within the given rectangle,
     * including the boundary. The rectangle must be within the unit sqaure;
     * if not an empty set is returned.
     * 
     * \param Rectangle Rectangle to query point set.
     * 
     * \return Vector of points contained within the given rectangle. Empty
     *         vector if no points within the rectangle.
     */
    std::vector<Point2D> range(const Rectangle& r) const;

    /**
     * Determines the nearest point in the set to the given point. The given
     * point must be within the unit square; if not, an exception is thrown.
     * An exception is thrown if the point set is empty.
     * 
     * \param Point2D Point to query the set.
     * 
     * \return Point nearest to the given point.
     */
    Point2D nearest(const Point2D& p) const;

    // output operator
    friend std::ostream& operator<<(std::ostream& out, const PointSET& ps);

    // copying, assigning, moving a PointSET is not supported
    PointSET(const PointSET& ps) = delete;
    PointSET(PointSET& ps) = delete;
    PointSET& operator=(const PointSET& ps) = delete;
    PointSET& operator=(PointSET& ps) = delete;

private:

    std::set<Point2D> m_pset{};

};

#endif // POINT_SET_H
