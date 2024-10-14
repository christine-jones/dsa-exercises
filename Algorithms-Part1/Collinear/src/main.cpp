/**
 * \file    main.cpp
 * \author  Christine Jones 
 * \brief   
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */ 

#include "BruteCollinearPoints.h"
#include "FastCollinearPoints.h"
#include "Point.h"
#include <exception>
#include <iostream>
#include <vector>

int main() {

    std::vector<Point> p1{Point{10000,     0},
                          Point{    0, 10000},
                          Point{ 3000,  7000},
                          Point{ 7000,  3000},
                          Point{20000, 21000},
                          Point{ 3000,  4000},
                          Point{14000, 15000},
                          Point{ 6000,  7000}};

    for (const auto& i : p1)
        std::cout << i << " ";
    std::cout << '\n';

    BruteCollinearPoints brute{p1};
    std::cout << "Brute: # segments = " << brute.numberOfSegments() << '\n';
    for (const auto& segment : brute.segments())
        std::cout << segment << '\n';

    std::vector<Point> p2{Point{10000,     0},
                          Point{    0, 10000},
                          Point{ 3000,  7000},
                          Point{ 7000,  3000},
                          Point{20000, 21000},
                          Point{ 3000,  4000},
                          Point{14000, 15000},
                          Point{ 6000,  7000}};

    for (const auto& i : p2)
        std::cout << i << " ";
    std::cout << '\n';

    FastCollinearPoints fast1(p2);
    std::cout << "Fast: # segments = " << fast1.numberOfSegments() << '\n';
    for (const auto& segment : fast1.segments())
        std::cout << segment << '\n';

    std::vector<Point> p3{Point{19000, 10000},
                          Point{18000, 10000},
                          Point{32000, 10000},
                          Point{21000, 10000},
                          Point{ 1234,  5678},
                          Point{14000, 10000}};

    for (const auto& i : p3)
        std::cout << i << " ";
    std::cout << '\n';

    FastCollinearPoints fast2(p3);
    std::cout << "Fast: # segments = " << fast2.numberOfSegments() << '\n';
    for (const auto& segment : fast2.segments())
        std::cout << segment << '\n';

    return 0;
}
