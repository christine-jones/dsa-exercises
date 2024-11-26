/**
 * \file    TestQuickUF.cpp
 * \author  Christine Jones 
 * \brief   Test cases for QuickUF class.
 * 
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "UnionFind.h"
#include "Test.h"
#include <iostream>

void testQuickUF() {

    Test::reset();

    std::cout << "***** Quick Union Find *****" << '\n';
    QuickUF uf{10};

    uf.join(4, 3);
    uf.join(3, 8);
    uf.join(8, 3); // repeat/reverse
    uf.join(6, 5);
    uf.join(9, 4);
    uf.join(2, 1);

    Test::ASSERT(uf.connected(8, 9), "QuickUF: connected"); // #1
    Test::ASSERT(uf.connected(9, 8), "QuickUF: connected, reverse"); // #2
    Test::ASSERT(!uf.connected(5, 0), "QuickUF: not connected"); // #3
    Test::ASSERT(!uf.connected(0, 5), "QuickUF: not connected, reverse"); // #4

    uf.join(5, 0);
    Test::ASSERT(uf.connected(5, 0), "QuickUF: connected"); // #5

    uf.join(7, 2);
    uf.join(6, 1);

    Test::runReport();
    std::cout << "****************************" << '\n' << '\n';
}

void testOpenQuickUF() {

    Test::reset();

    std::cout << "***** Open Quick Union Find *****" << '\n';
    OpenUF<QuickUF> uf{10};

    Test::ASSERT(!uf.isOpen(4), "OpenQuickUF: not open"); // #1
    uf.open(4);
    Test::ASSERT(uf.isOpen(4), "OpenQuickUF: open"); // #2

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

    Test::ASSERT(uf.connected(8, 9), "OpenQuickUF: connected"); // #3
    Test::ASSERT(!uf.connected(5, 0), "OpenQuickUF: not connected"); // #4
    uf.open(0);
    Test::ASSERT(!uf.connected(5, 0), "OpenQuickUF: not connected"); // #5
    Test::ASSERT(!uf.connected(0, 5),
                 "OpenQuickUF: not connected reverse"); // #6
    uf.join(5, 0);
    Test::ASSERT(uf.connected(5, 0), "OpenQuickUF: connected"); // #7
    Test::ASSERT(uf.connected(0, 5),
                 "OpenQuickUF: connected reverse"); // #8

    uf.open(7);
    uf.join(7, 2);
    uf.join(6, 1);

    Test::runReport();
    std::cout << "*********************************" << '\n' << '\n';
}
