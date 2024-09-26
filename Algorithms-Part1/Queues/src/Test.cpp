/**
 * \file    Test.cpp
 * \author  Christine Jones 
 * \brief   Implementation of test cases for Deque container class.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "Deque.h"
#include "Test.h"
#include <iostream>

namespace Test {

void runTests() {

    std::cout << "running tests..." << '\n';

    Deque<int> myDeque{};

    myDeque.addFirst(5);
    myDeque.addFirst(4);
    myDeque.addFirst(3);
    myDeque.addFirst(2);
    myDeque.addFirst(1);

    Test::printDeque(myDeque);
}

void testDeque() {


}

void testExceptions() {


}

void testIterators() {


}

void testWithStrings() {


}

void printDeque(const Deque<int>& d) {

    for (const auto& i : d)
        std::cout << i << ' ';
    std::cout << '\n';
}

} // namespace Test
