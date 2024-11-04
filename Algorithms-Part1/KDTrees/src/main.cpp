/**
 * \file    main.cpp
 * \author  Christine Jones 
 * \brief            
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */ 

#include "Point2D.h"
#include "Rectangle.h"
#include <iostream>

int main() {

    Rectangle r{0, 0, 4, 4};
    std::cout << r << '\n';

    Point2D p1{2, 2};
    std::cout << p1 << '\n';
    std::cout << "Contains? " << (r.contains(p1) ? "YES" : "NO") << " "
              << "Distance = " << r.distanceTo(p1) << '\n';

    Point2D p2{2, -2};
    std::cout << p2 << '\n';
    std::cout << "Contains? " << (r.contains(p2) ? "YES" : "NO") << " "
              << "Distance = " << r.distanceTo(p2) << '\n';

    Point2D p3{2, 7};
    std::cout << p3 << '\n';
    std::cout << "Contains? " << (r.contains(p3) ? "YES" : "NO") << " "
              << "Distance = " << r.distanceTo(p3) << '\n';

    Point2D p4{-3, 2};
    std::cout << p4 << '\n';
    std::cout << "Contains? " << (r.contains(p4) ? "YES" : "NO") << " "
              << "Distance = " << r.distanceTo(p4) << '\n';

    Point2D p5{5, 2};
    std::cout << p5 << '\n';
    std::cout << "Contains? " << (r.contains(p5) ? "YES" : "NO") << " "
              << "Distance = " << r.distanceTo(p5) << '\n';

    Point2D p6{7, 9};
    std::cout << p6 << '\n';
    std::cout << "Contains? " << (r.contains(p6) ? "YES" : "NO") << " "
              << "Distance = " << r.distanceTo(p6) << '\n';

    return 0;
}
