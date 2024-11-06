/**
 * \file    PointSet.h
 * \author  Christine Jones 
 * \brief
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

    PointSET();

    bool isEmpty() const { return m_pset.empty(); }
    int size() const { return m_pset.size(); }

    void insert(const Point2D& p);
    bool contains(const Point2D& p) const;

    std::vector<Point2D> range(const Rectangle& r);

    Point2D nearest(const Point2D p);

    // output operator
    friend std::ostream& operator<<(std::ostream& out, const PointSET& ps);

private:

    std::set<Point2D> m_pset{};

};

#endif // POINT_SET_H
