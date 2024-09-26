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
#include <exception>
#include <iostream>

namespace Test {

void runTests() {

    std::cout << "running tests..." << '\n';

    testDeque();
    testExceptions();
    testIterators();
}

void testDeque() {

    Deque<int> d{};

    printDeque(d);

    d.addFirst(1);
    printDeque(d);
    std::cout << "removed: " << d.removeFirst() << '\n';
    printDeque(d);

    d.addLast(2);
    printDeque(d);
    std::cout << "removed: " << d.removeLast() << '\n';
    printDeque(d);

    d.addFirst(5);
    d.addFirst(4);
    d.addFirst(3);
    d.addFirst(2);
    d.addFirst(1);
    printDeque(d);

    d.clear();
    printDeque(d);

    d.addLast(1);
    d.addLast(2);
    d.addLast(3);
    d.addLast(4);
    d.addLast(5);
    printDeque(d);

    d.clear();
    printDeque(d);

    d.addFirst(3);
    d.addFirst(2);
    d.addFirst(1);
    printDeque(d);
    std::cout << "removed: " << d.removeLast() << '\n';
    std::cout << "removed: " << d.removeLast() << '\n';
    std::cout << "removed: " << d.removeLast() << '\n';
    printDeque(d);
    d.addLast(1);
    d.addLast(2);
    d.addLast(3);
    printDeque(d);
    std::cout << "removed: " << d.removeFirst() << '\n';
    std::cout << "removed: " << d.removeFirst() << '\n';
    std::cout << "removed: " << d.removeFirst() << '\n';
    printDeque(d);

    d.addFirst(3);
    d.addLast(4);
    d.addFirst(2);
    d.addLast(5);
    d.addFirst(1);
    d.addLast(6);
    printDeque(d);
    std::cout << "removed: " << d.removeFirst() << '\n';
    std::cout << "removed: " << d.removeLast() << '\n';
    std::cout << "removed: " << d.removeFirst() << '\n';
    std::cout << "removed: " << d.removeLast() << '\n';
    std::cout << "removed: " << d.removeFirst() << '\n';
    std::cout << "removed: " << d.removeLast() << '\n';
    printDeque(d);

    d.addLast(4);
    d.addFirst(3);
    d.addLast(5);
    d.addFirst(2);
    d.addLast(6);
    d.addFirst(1);
    printDeque(d);
    std::cout << "Size: " << d.size() << "  "
              << "isEmpty? " << ((d.isEmpty()) ? "true" : "false") << '\n';
    std::cout << "removed: " << d.removeFirst() << '\n';
    std::cout << "removed: " << d.removeLast() << '\n';
    std::cout << "removed: " << d.removeFirst() << '\n';
    std::cout << "removed: " << d.removeLast() << '\n';
    std::cout << "removed: " << d.removeFirst() << '\n';
    std::cout << "removed: " << d.removeLast() << '\n';
    printDeque(d);
    std::cout << "Size: " << d.size() << "  "
              << "isEmpty? " << ((d.isEmpty()) ? "true" : "false") << '\n';

}

void testExceptions() {

    Deque<int> d{};
    
    d.addFirst(100);
    try {

        std::cout << "removed: " << d.removeFirst() << '\n';

    } catch (const std::out_of_range& e) {

        std::cerr << "SHOULD NOT catch an error: " << e.what() << '\n';
    }
    try {

        std::cout << "removed: " << d.removeFirst() << '\n';

    } catch (const std::out_of_range& e) {

        std::cerr << "SHOULD catch an error: " << e.what() << '\n';
    }

    d.addLast(200);
    try {

        std::cout << "removed: " << d.removeLast() << '\n';

    } catch (const std::out_of_range& e) {

        std::cerr << "SHOULD NOT catch an error: " << e.what() << '\n';
    }
    try {

        std::cout << "removed: " << d.removeLast() << '\n';

    } catch (const std::out_of_range& e) {

        std::cerr << "SHOULD catch an error: " << e.what() << '\n';
    }
}

void testIterators() {

    Deque<int> d{};
    d.addFirst(5);
    d.addFirst(4);
    d.addFirst(3);
    d.addFirst(2);
    d.addFirst(1);

    std::cout << "non-const iterator: ";
    Deque<int>::iterator iter;
    for (iter = d.begin(); iter != d.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';

    std::cout << "const iterator: ";
    Deque<int>::const_iterator citer;
    for (citer = d.cbegin(); citer != d.cend(); ++citer)
        std::cout << *citer << ' ';
    std::cout << '\n';

    std::cout << "non-const range-based for loop: ";
    for (auto& i : d)
        std::cout << i << ' ';
    std::cout << '\n';

    std::cout << "const range-based for loop: ";
    for (const auto& i : d)
        std::cout << i << ' ';
    std::cout << '\n';
}

void testWithStrings() {


}

void printDeque(const Deque<int>& d) {

    if (d.isEmpty()) {

        std::cout << "empty" << '\n';
        return;
    }

    for (const auto& i : d)
        std::cout << i << ' ';
    std::cout << '\n';
}

} // namespace Test
