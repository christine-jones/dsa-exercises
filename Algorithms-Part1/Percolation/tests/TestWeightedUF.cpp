/**
 * \file    TestWeightedUF.cpp
 * \author  Christine Jones 
 * \brief   Test cases for WeightedUF class.
 * 
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "UnionFind.h"
#include "Test.h"
#include <iostream>

void testWeightedUF() {

    Test::reset();

    std::cout << "***** Weighted Union Find *****" << '\n';
    WeightedUF uf{10};

    uf.join(4, 3);
    uf.join(3, 8);
    uf.join(8, 3); // repeat/reverse
    uf.join(6, 5);
    uf.join(9, 4);
    uf.join(2, 1);

    Test::ASSERT(uf.connected(8, 9), "WeightedUF: connected"); // #1
    Test::ASSERT(uf.connected(8, 9), "WeightedUF: connected reverse "); // #2
    Test::ASSERT(!uf.connected(5, 0), "WeightedUF: not connected"); // #3
    Test::ASSERT(!uf.connected(0, 5),
                 "WeightedUF: not connected reverse"); // #4

    uf.join(5, 0);
    Test::ASSERT(uf.connected(5, 0), "WeightedUF: connected"); // #5

    uf.join(7, 2);
    uf.join(6, 1);
    uf.join(7, 3);

    std::string validUF{"6(1) 2(1) 6(3) 4(1) 6(4) 6(1) 6(10) 6(1) 4(1) 4(1) "};
    Test::ASSERT((uf.toStr() == validUF),
                  "WeightedUF: string compare"); // #6

    Test::runReport();
    std::cout << "*******************************" << '\n' << '\n';
}

void testOpenWeightedUF() {

    Test::reset();

    std::cout << "***** Open Weighted Union Find *****" << '\n';
    OpenUF<WeightedUF> uf{10};

    Test::ASSERT(!uf.isOpen(4), "OpenWeightedUF: not open"); // #1
    uf.open(4);
    Test::ASSERT(uf.isOpen(4), "OpenWeightedUF: open"); // #2

    uf.open(4); // repeat
    uf.join(4, 3);
    uf.open(3);
    uf.join(4, 3);
    uf.open(8);
    uf.join(3, 8);
    uf.open(6);
    uf.open(5);
    uf.join(6, 5);
    uf.open(9);
    uf.join(9, 4);
    uf.open(2);
    uf.open(1);
    uf.join(2, 1);

    Test::ASSERT(uf.connected(8, 9), "OpenWeightedUF: connected"); // #3
    Test::ASSERT(!uf.connected(5, 0), "OpenWeightedUF: not connected"); // #4
    uf.open(0);
    Test::ASSERT(!uf.connected(5, 0), "OpenWeightedUF: not connected"); // #5
    Test::ASSERT(!uf.connected(0, 5),
                 "OpenWeightedUF: not connected reverse"); // #6
    uf.join(5, 0);
    Test::ASSERT(uf.connected(5, 0), "OpenWeightedUF: connected"); // #7
    Test::ASSERT(uf.connected(5, 0),
                 "OpenWeightedUF: connected reverse"); // #8

    uf.open(7);
    uf.join(7, 2);
    uf.join(6, 1);
    uf.join(7, 3);

    std::string validUF{"6(1) 2(1) 6(3) 4(1) 6(4) 6(1) 6(10) 6(1) 4(1) 4(1) "};
    Test::ASSERT((uf.toStr() == validUF),
                  "OpenWeightedUF: string compare"); // #9

    Test::runReport();
    std::cout << "************************************" << '\n' << '\n';
}
