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

    std::cout << "***** Percolation *****" << '\n';

    Test::reset();

    Percolation<WeightedUF> p(10);

    Test::ASSERT((p.numberOfOpenSites() == 0), // test case 1
                 "Percolation: number of open sites");
    Test::ASSERT((p.isOpen(5, 5) == false), // test case 2
                 "Percolation: not open");

    p.open(5, 5);
    Test::ASSERT((p.isOpen(5, 5) == true), // test case 3
                 "Percolation: open");

    p.open(5, 5); // repeat
    p.open(1, 5);
    p.open(10, 5);
    p.open(5, 1);
    p.open(5, 10);
    Test::ASSERT((p.isFull(1, 5) == true), // test case 4
                 "Percolation: full");
    Test::ASSERT((p.isFull(5, 10) == false), // test case 5
                 "Percolation: not full");
    Test::ASSERT((p.percolates() == false), // test case 6
                 "Percolation: does not percolate"); 

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
    Test::ASSERT((p.isFull(2, 6) == true), // test case 7
                 "Percolation: full");
    Test::ASSERT((p.isFull(3, 6) == false), // test case 8
                 "Percolation: not full");
    Test::ASSERT((p.percolates() == false), // test case 9
                 "Percolation: does not percolate"); 

    p.open(3, 6);
    Test::ASSERT((p.isFull(3, 6) == true), // test case 10
                 "Percolation: full");
    Test::ASSERT((p.percolates() == true), // test case 11
                 "Percolation: percolates"); 

    Test::runReport();
    std::cout << "***********************" << '\n';
}
