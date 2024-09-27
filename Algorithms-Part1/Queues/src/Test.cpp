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
#include <string>
#include <string_view>

namespace Test {

void runTests() {

    std::cout << "running tests..." << '\n';

    testDeque();
}

void testDeque() {

    testDequeBasicOperation();
    testDequeExceptions();
    testDequeIterators();
}

void testDequeBasicOperation() {

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

void testDequeExceptions() {

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

void testDequeIterators() {

    Deque<int> d{};
    d.addFirst(5);
    d.addFirst(4);
    d.addFirst(3);
    d.addFirst(2);
    d.addFirst(1);

    std::cout << "non-const iterator: ";
    Deque<int>::iterator iter{};
    for (iter = d.begin(); iter != d.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\n';

    std::cout << "const iterator: ";
    Deque<int>::const_iterator citer{};
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

    Deque<int>::iterator a_iter{d.begin()};
    Deque<int>::iterator b_iter{d.begin()};

    std::cout << "iterators equal? "
              << (a_iter == b_iter ? "true" : "false") << '\n';
    std::cout << "iterators not equal? "
              << (a_iter != b_iter ? "true" : "false") << '\n';
    ++a_iter;
    ++b_iter;
    std::cout << "iterators equal? "
              << (a_iter == b_iter ? "true" : "false") << '\n';
    std::cout << "iterators not equal? "
              << (a_iter != b_iter ? "true" : "false") << '\n';
    a_iter++;
    b_iter++;
    std::cout << "iterators equal? "
              << (a_iter == b_iter ? "true" : "false") << '\n';
    std::cout << "iterators not equal? "
              << (a_iter != b_iter ? "true" : "false") << '\n';
    a_iter++;
    std::cout << "iterators equal? "
              << (a_iter == b_iter ? "true" : "false") << '\n';
    std::cout << "iterators not equal? "
              << (a_iter != b_iter ? "true" : "false") << '\n';

    std::cout << "reference: " << *a_iter << ' ' << *b_iter << '\n';

    Deque<std::string_view> s_deque{};
    s_deque.addLast("This");
    s_deque.addLast("is");
    s_deque.addLast("a");
    s_deque.addLast("deque");
    s_deque.addLast("of");
    s_deque.addLast("strings.");
    printDeque(s_deque);

    Deque<std::string_view>::iterator s_iter{s_deque.begin()};
    Deque<std::string_view>::const_iterator s_citer{s_deque.cbegin()};
    ++s_iter; ++s_citer;
    ++s_iter; ++s_citer;
    ++s_iter; ++s_citer;
    std::cout << "reference: " << *s_iter << '\n';
    std::cout << "const reference: " << *s_citer << '\n';
    std::cout << "size of string via pointer: " << s_iter->size() << '\n';
    std::cout << "size of string via const pointer: "
              << s_citer->size() << '\n';
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

void printDeque(const Deque<std::string_view>& d) {

    if (d.isEmpty()) {

        std::cout << "empty" << '\n';
        return;
    }

    for (const auto& s : d)
        std::cout << s << ' ';
    std::cout << '\n';
}

} // namespace Test
