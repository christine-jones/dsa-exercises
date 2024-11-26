/**
 * \file    TestPercolation.cpp
 * \author  Christine Jones 
 * \brief   Test cases for Percolation class.
 * 
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "Percolation.h"
#include "Test.h"
#include <iostream>

void testPercolation() {

    Test::reset();

    std::cout << "***** Percolation *****" << '\n';
    Percolation<WeightedUF> p(10);

    Test::ASSERT((p.numberOfOpenSites() == 0), // #1
                 "Percolation: number of open sites");
    Test::ASSERT(!p.isOpen(5, 5), "Percolation: not open"); // #2

    p.open(5, 5);
    Test::ASSERT(p.isOpen(5, 5), "Percolation: open"); // #3

    p.open(5, 5); // repeat
    p.open(1, 5);
    p.open(10, 5);
    p.open(5, 1);
    p.open(5, 10);
    Test::ASSERT(p.isFull(1, 5), "Percolation: full"); // #4
    Test::ASSERT(!p.isFull(5, 10), "Percolation: not full"); // #5
    Test::ASSERT(!p.percolates(), "Percolation: does not percolate"); // #6 

    p.open(4, 6);
    p.open(5, 7);
    p.open(6, 6);
    p.open(5, 6);
    p.open(5, 6); // repeat
    p.open(2, 5);
    p.open(2, 6);
    p.open(7, 6);
    p.open(8, 6);
    p.open(9, 6);
    p.open(10, 6);
    Test::ASSERT(p.isFull(2, 6), "Percolation: full"); // #7
    Test::ASSERT(!p.isFull(3, 6), "Percolation: not full"); // #8
    Test::ASSERT(!p.percolates(), "Percolation: does not percolate"); // #9 

    p.open(3, 6);
    Test::ASSERT(p.isFull(3, 6), "Percolation: full"); // #10
    Test::ASSERT(p.percolates(), "Percolation: percolates"); // #11 

    Test::runReport();
    std::cout << "***********************" << '\n' << '\n';
}
