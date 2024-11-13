/**
 * \file    main.cpp
 * \author  Christine Jones 
 * \brief            
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */ 

#include "KDTree.h"
#include "Point2D.h"
#include "Rectangle.h"
#include <iostream>

int main() {

    KDTree tree{};

    tree.insert(Point2D{0.7, 0.2});
    tree.insert(Point2D{0.5, 0.4});
    tree.insert(Point2D{0.2, 0.4});
    tree.insert(Point2D{0.2, 0.3});
    tree.insert(Point2D{0.4, 0.7});
    tree.insert(Point2D{0.9, 0.6});

    std::cout << tree << '\n';

    std::cout << "Contains " << Point2D{0.2, 0.3} << ": "
              << (tree.contains(Point2D{0.2, 0.3}) ? "TRUE" : "FALSE")
              << '\n';
    std::cout << "Contains " << Point2D{0.2, 0.4} << ": "
              << (tree.contains(Point2D{0.2, 0.4}) ? "TRUE" : "FALSE")
              << '\n';
    std::cout << "Contains " << Point2D{0.2, 0.5} << ": "
              << (tree.contains(Point2D{0.2, 0.5}) ? "TRUE" : "FALSE")
              << '\n';

    return 0;
}
