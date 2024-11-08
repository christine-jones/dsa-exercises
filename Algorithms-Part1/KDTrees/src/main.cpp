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
    std::cout << tree << '\n';
    tree.insert(Point2D{0.5, 0.4});
    std::cout << tree << '\n';
    // what happens if tie in x/y coordinate, must look at the other
    //tree.insert(Point2D{0.2, 0.4});
    tree.insert(Point2D{0.2, 0.3});
    std::cout << tree << '\n';
    tree.insert(Point2D{0.4, 0.7});
    std::cout << tree << '\n';
    tree.insert(Point2D{0.9, 0.6});
    std::cout << tree << '\n';

    return 0;
}
