/**
 * \file    Test.cpp
 * \author  Christine Jones 
 * \brief   Implementation of test cases.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "Percolation.h"
#include "Test.h"
#include "UnionFind.H"
#include <iostream>

void testPercolation() {

    Percolation<WeightedUF> p{10};

    std::cout << "***** Percolation *****" << '\n';
    p.print();
    std::cout << "Number of Open Sites: " << p.numberOfOpenSites() << '\n';
    std::cout << "isOpen(5, 5)? "
              << (p.isOpen(5, 5) ? "true" : "false") << '\n';
    std::cout << "open(5, 5)" << '\n'; p.open(5, 5);
    std::cout << "isOpen(5, 5)? "
              << (p.isOpen(5, 5) ? "true" : "false") << '\n';
    std::cout << "open(5, 5), repeat" << '\n'; p.open(5, 5);
    std::cout << "open(1, 5)" << '\n'; p.open(1, 5);
    std::cout << "open(10, 5)" << '\n'; p.open(10, 5);
    std::cout << "open(5, 1)" << '\n'; p.open(5, 1);
    std::cout << "open(5, 10)" << '\n'; p.open(5, 10);
    std::cout << "isFull(1, 5)? "
              << (p.isFull(1, 5) ? "true" : "false") << '\n';
    std::cout << "isFull(5, 10)? "
              << (p.isFull(5, 10) ? "true" : "false") << '\n';
    std::cout << "Percolates? "
              << (p.percolates() ? "true" : "false") << '\n';
    std::cout << "open(4, 6)" << '\n'; p.open(4, 6);
    std::cout << "open(5, 7)" << '\n'; p.open(5, 7);
    std::cout << "open(6, 6)" << '\n'; p.open(6, 6);
    std::cout << "open(5, 6)" << '\n'; p.open(5, 6);
    std::cout << "open(5, 6), repeat" << '\n'; p.open(5, 6);
    std::cout << "open(2, 5)" << '\n'; p.open(2, 5);
    std::cout << "open(2, 6)" << '\n'; p.open(2, 6);
    std::cout << "open(7, 6)" << '\n'; p.open(7, 6);
    std::cout << "open(8, 6)" << '\n'; p.open(8, 6);
    std::cout << "open(9, 6)" << '\n'; p.open(9, 6);
    std::cout << "open(10, 6)" << '\n'; p.open(10, 6);
    std::cout << "isFull(2, 6)? "
          << (p.isFull(2, 6) ? "true" : "false") << '\n';
    std::cout << "isFull(3, 6)? "
              << (p.isFull(3, 6) ? "true" : "false") << '\n';
    std::cout << "Percolates? "
              << (p.percolates() ? "true" : "false") << '\n';
    std::cout << "open(3, 6)" << '\n'; p.open(3, 6);
    std::cout << "isFull(3, 6)? "
              << (p.isFull(3, 6) ? "true" : "false") << '\n';
    std::cout << "Percolates? "
              << (p.percolates() ? "true" : "false") << '\n';
    p.print();
}

void testQuickUF() {

    QuickUF uf{10};

    std::cout << "***** Quick Union Find *****" << '\n';
    uf.print();
    std::cout << "join(4, 3)" << '\n'; uf.join(4, 3);
    std::cout << "join(3, 8)" << '\n'; uf.join(3, 8);
    uf.print();
    std::cout << "join(8, 3), repeat/reverse" << '\n'; uf.join(8, 3);
    uf.print();
    std::cout << "join(6, 5)" << '\n'; uf.join(6, 5);
    std::cout << "join(9, 4)" << '\n'; uf.join(9, 4);
    std::cout << "join(2, 1)" << '\n'; uf.join(2, 1);
    std::cout << "connected(8, 9)? "
              << (uf.connected(8, 9) ? "true" : "false") << '\n';
    std::cout << "connected(9, 8), reverse? "
              << (uf.connected(9, 8) ? "true" : "false") << '\n';
    std::cout << "connected(5, 0)? "
              << (uf.connected(5, 0) ? "true" : "false") << '\n';
    std::cout << "connected(0, 5), reverse? "
              << (uf.connected(0, 5) ? "true" : "false") << '\n';
    std::cout << "join(5, 0)" << '\n'; uf.join(5, 0);
    std::cout << "connected(5, 0)? "
              << (uf.connected(5, 0) ? "true" : "false") << '\n';
    std::cout << "join(7, 2)" << '\n'; uf.join(7, 2);
    std::cout << "join(6, 1)" << '\n'; uf.join(6, 1);
    uf.print();
}

void testOpenQuickUF() {

    OpenUF<QuickUF> uf{10};

    std::cout << "***** Open Quick Union Find *****" << '\n';
    uf.print();
    std::cout << "isOpen(4)? "
              << (uf.isOpen(4) ? "true" : "false") << '\n';
    std::cout << "open(4)" << '\n'; uf.open(4);
    std::cout << "isOpen(4)? "
              << (uf.isOpen(4) ? "true" : "false") << '\n';
    uf.print();
    std::cout << "open(4), repeat" << '\n'; uf.open(4);
    std::cout << "join(4, 3)" << '\n'; uf.join(4, 3);
    uf.print();
    std::cout << "open(3)" << '\n'; uf.open(3);
    std::cout << "join(4, 3)" << '\n'; uf.join(4, 3);
    uf.print();
    std::cout << "open(8)" << '\n'; uf.open(8);
    std::cout << "join(3, 8)" << '\n'; uf.join(3, 8);
    std::cout << "open(6)" << '\n'; uf.open(6);
    std::cout << "open(5)" << '\n'; uf.open(5);
    std::cout << "join(6, 5)" << '\n'; uf.join(6, 5);
    std::cout << "open(9)" << '\n'; uf.open(9);
    std::cout << "join(9, 4)" << '\n'; uf.join(9, 4);
    std::cout << "open(2)" << '\n'; uf.open(2);
    std::cout << "open(1)" << '\n'; uf.open(1);
    std::cout << "join(2, 1)" << '\n'; uf.join(2, 1);
    uf.print();
    std::cout << "connected(8, 9)? "
              << (uf.connected(8, 9) ? "true" : "false") << '\n';
    std::cout << "connected(5, 0)? "
              << (uf.connected(5, 0) ? "true" : "false") << '\n';
    std::cout << "open(0)" << '\n'; uf.open(0);
    std::cout << "connected(5, 0)? "
              << (uf.connected(5, 0) ? "true" : "false") << '\n';
    std::cout << "join(5, 0)" << '\n'; uf.join(5, 0);
    std::cout << "connected(5, 0)? "
              << (uf.connected(5, 0) ? "true" : "false") << '\n';
    uf.print();
    std::cout << "open(7)" << '\n'; uf.open(7);
    std::cout << "join(7, 2)" << '\n'; uf.join(7, 2);
    std::cout << "join(6, 1)" << '\n'; uf.join(6, 1);
    uf.print();
}

void testWeightedUF() {

    WeightedUF uf{10};

    std::cout << "***** Weighted Union Find *****" << '\n';
    uf.print();
    std::cout << "join(4, 3)" << '\n'; uf.join(4, 3);
    std::cout << "join(3, 8)" << '\n'; uf.join(3, 8);
    uf.print();
    std::cout << "join(8, 3), repeat/reverse" << '\n'; uf.join(8, 3);
    uf.print();
    std::cout << "join(6, 5)" << '\n'; uf.join(6, 5);
    std::cout << "join(9, 4)" << '\n'; uf.join(9, 4);
    std::cout << "join(2, 1)" << '\n'; uf.join(2, 1);
    std::cout << "connected(8, 9)? "
              << (uf.connected(8, 9) ? "true" : "false") << '\n';
    std::cout << "connected(9, 8), reverse? "
              << (uf.connected(9, 8) ? "true" : "false") << '\n';
    std::cout << "connected(5, 0)? "
              << (uf.connected(5, 0) ? "true" : "false") << '\n';
    std::cout << "connected(0, 5), reverse? "
              << (uf.connected(0, 5) ? "true" : "false") << '\n';
    std::cout << "join(5, 0)" << '\n'; uf.join(5, 0);
    std::cout << "connected(5, 0)? "
              << (uf.connected(5, 0) ? "true" : "false") << '\n';
    std::cout << "join(7, 2)" << '\n'; uf.join(7, 2);
    std::cout << "join(6, 1)" << '\n'; uf.join(6, 1);
    std::cout << "join(7, 3)" << '\n'; uf.join(7, 3);
    uf.print();
}

void testOpenWeightedUF() {

    OpenUF<WeightedUF> uf{10};

    std::cout << "***** Open Weighted Union Find *****" << '\n';
    uf.print();
    std::cout << "isOpen(4)? "
              << (uf.isOpen(4) ? "true" : "false") << '\n';
    std::cout << "open(4)" << '\n'; uf.open(4);
    std::cout << "isOpen(4)? "
              << (uf.isOpen(4) ? "true" : "false") << '\n';
    uf.print();
    std::cout << "open(4), repeat" << '\n'; uf.open(4);
    std::cout << "join(4, 3)" << '\n'; uf.join(4, 3);
    uf.print();
    std::cout << "open(3)" << '\n'; uf.open(3);
    std::cout << "join(4, 3)" << '\n'; uf.join(4, 3);
    uf.print();
    std::cout << "open(8)" << '\n'; uf.open(8);
    std::cout << "join(3, 8)" << '\n'; uf.join(3, 8);
    std::cout << "open(6)" << '\n'; uf.open(6);
    std::cout << "open(5)" << '\n'; uf.open(5);
    std::cout << "join(6, 5)" << '\n'; uf.join(6, 5);
    std::cout << "open(9)" << '\n'; uf.open(9);
    std::cout << "join(9, 4)" << '\n'; uf.join(9, 4);
    std::cout << "open(2)" << '\n'; uf.open(2);
    std::cout << "open(1)" << '\n'; uf.open(1);
    std::cout << "join(2, 1)" << '\n'; uf.join(2, 1);
    uf.print();
    std::cout << "connected(8, 9)? "
              << (uf.connected(8, 9) ? "true" : "false") << '\n';
    std::cout << "connected(5, 0)? "
              << (uf.connected(5, 0) ? "true" : "false") << '\n';
    std::cout << "open(0)" << '\n'; uf.open(0);
    std::cout << "connected(5, 0)? "
              << (uf.connected(5, 0) ? "true" : "false") << '\n';
    std::cout << "join(5, 0)" << '\n'; uf.join(5, 0);
    std::cout << "connected(5, 0)? "
              << (uf.connected(5, 0) ? "true" : "false") << '\n';
    uf.print();
    std::cout << "open(7)" << '\n'; uf.open(7);
    std::cout << "join(7, 2)" << '\n'; uf.join(7, 2);
    std::cout << "join(6, 1)" << '\n'; uf.join(6, 1);
    std::cout << "join(7, 3)" << '\n'; uf.join(7, 3);
    uf.print();
}
