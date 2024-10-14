/**
 * \file    Point.h
 * \author  Christine Jones 
 * \brief   Class definitioin that represents an (x, y) point in a plane.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <vector>

class Point {

public:

    Point(int x, int y):
        m_x{x},
        m_y{y}
    {}

    double slope(const Point& p) const;

    static void sortPoints(std::vector<Point>& points);
    static bool duplicatePoint(const std::vector<Point>& points);

    // comparison operators
    friend bool operator==(const Point& p1, const Point& p2);
    friend bool operator!=(const Point& p1, const Point& p2);
    friend bool operator< (const Point& p1, const Point& p2);
    friend bool operator> (const Point& p1, const Point& p2);
    friend bool operator<=(const Point& p1, const Point& p2);
    friend bool operator>=(const Point& p1, const Point& p2);

    friend std::ostream& operator<<(std::ostream& out, const Point& p);

private:

    int m_x;
    int m_y;

};

#endif // POINT_H
