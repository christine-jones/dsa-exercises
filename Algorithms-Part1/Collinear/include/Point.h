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

    Point();
    Point(int x, int y);

    double slope(const Point& p) const;
    bool   slopeOrder(const Point& p, const Point& q) const;

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

    int m_x{0};
    int m_y{0};

};

#endif // POINT_H
