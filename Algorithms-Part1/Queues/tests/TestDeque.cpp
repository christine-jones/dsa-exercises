/**
 * \file    TestDeque.cpp
 * \author  Christine Jones 
 * \brief   Test cases for Deque class.
 * 
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "Deque.h"
#include "Test.h"
#include <iostream>
#include <sstream>
#include <string>

void testDequeBasicOperation();
void testDequeExceptions();
void testDequeIterators();
std::string dequeToStr(const Deque<int>& d);
std::string dequeToStr(const Deque<std::string_view>& d);

void testDeque() {

    testDequeBasicOperation();
    testDequeExceptions();
    testDequeIterators();
}

void testDequeBasicOperation() {

    Test::reset();
    std::cout << "***** Deque Basic *****" << '\n';

    Deque<int> d{};

    Test::ASSERT(d.isEmpty(), "Deque: empty"); // #1

    d.addFirst(1);
    Test::ASSERT(!d.isEmpty(), "Deque: not empty"); // #2
    Test::ASSERT((d.size() == 1), "Deque: add first, size 1"); // #3
    d.removeFirst();
    Test::ASSERT(d.isEmpty(), "Deque: remove first, empty again"); // #4

    d.addLast(2);
    Test::ASSERT(!d.isEmpty(), "Deque: not empty"); // #5
    Test::ASSERT((d.size() == 1), "Deque: add last, size 1"); // #6
    d.removeLast();
    Test::ASSERT(d.isEmpty(), "Deque: remove last, empty again"); // #7

    d.addFirst(5);
    d.addFirst(4);
    d.addFirst(3);
    d.addFirst(2);
    d.addFirst(1);
    Test::ASSERT((d.size() == 5), "Deque: add first, size 5"); // #8
    
    std::string valid_deque{"1 2 3 4 5 "};
    Test::ASSERT((dequeToStr(d) == valid_deque), 
                 "Deque: string compare"); // #9

    d.clear();
    Test::ASSERT(d.isEmpty(), "Deque: clear, empty again"); // #10

    d.addLast(1);
    d.addLast(2);
    d.addLast(3);
    d.addLast(4);
    d.addLast(5);
    Test::ASSERT((d.size() == 5), "Deque: add last, size 5"); // #11

    Test::ASSERT((dequeToStr(d) == valid_deque), 
                 "Deque: string compare"); // #12

    d.clear();
    Test::ASSERT(d.isEmpty(), "Deque: clear, empty again"); // #13

    d.addFirst(3);
    d.addFirst(2);
    d.addFirst(1);
    Test::ASSERT((d.size() == 3), "Deque: add first, size 3"); // #14
    d.removeLast();
    d.removeLast();
    d.removeLast();
    Test::ASSERT(d.isEmpty(), "Deque: remove last, empty again"); // #15

    d.addLast(1);
    d.addLast(2);
    d.addLast(3);
    Test::ASSERT((d.size() == 3), "Deque: add last, size 3"); // #16
    d.removeFirst();
    d.removeFirst();
    d.removeFirst();
    Test::ASSERT(d.isEmpty(), "Deque: remove first, empty again"); // #17

    d.addFirst(3);
    d.addLast(4);
    d.addFirst(2);
    d.addLast(5);
    d.addFirst(1);
    d.addLast(6);
    Test::ASSERT((d.size() == 6), "Deque: add mix, size 6"); // #18

    valid_deque = "1 2 3 4 5 6 ";
    Test::ASSERT((dequeToStr(d) == valid_deque), 
                 "Deque: string compare"); // #9

    d.removeFirst();
    d.removeLast();
    d.removeFirst();
    d.removeLast();
    d.removeFirst();
    d.removeLast();
    Test::ASSERT(d.isEmpty(), "Deque: remove mix, empty again"); // #20

    d.addLast(4);
    d.addFirst(3);
    d.addLast(5);
    d.addFirst(2);
    d.addLast(6);
    d.addFirst(1);
    Test::ASSERT((d.size() == 6), "Deque: add mix again, size 6"); // #21

    Test::ASSERT((dequeToStr(d) == valid_deque), 
                 "Deque: string compare"); // #22

    d.removeFirst();
    d.removeLast();
    d.removeFirst();
    d.removeLast();
    d.removeFirst();
    d.removeLast();
    Test::ASSERT(d.isEmpty(), "Deque: remove mix again, empty again"); // #23

    valid_deque = "empty";
    Test::ASSERT((dequeToStr(d) == valid_deque), 
                 "Deque: string compare"); // #24

    Test::runReport();
    std::cout << "***********************" << '\n' << '\n';
}

void testDequeExceptions() {

    Test::reset();
    std::cout << "***** Deque Exceptions *****" << '\n';

    std::stringstream ss{};
    Deque<int> d{};
    
    d.addFirst(100);
    try {
        d.removeFirst();
        ss << "remove first: 100";

    } catch (const std::out_of_range& e) {

        ss << "SHOULD NOT catch an error: " << e.what();
    }

    std::string valid_message{"remove first: 100"};
    Test::ASSERT((ss.str() == valid_message), "Deque: no exception"); // #1

    ss.str(std::string{});

    try {

        d.removeFirst();
        ss << "remove first: ???";

    } catch (const std::out_of_range& e) {

        ss << "SHOULD catch an error: " << e.what();
    }

    valid_message = "SHOULD catch an error: deque empty, no such element";
    Test::ASSERT((ss.str() == valid_message), "Deque: exception"); // #2

    ss.str(std::string{});

    d.addLast(200);
    try {

        d.removeLast();
        ss << "remove last: 200";

    } catch (const std::out_of_range& e) {

        ss << "SHOULD NOT catch an error: " << e.what();
    }

    valid_message = "remove last: 200";
    Test::ASSERT((ss.str() == valid_message), "Deque: no exception"); // #3

    ss.str(std::string{});

    try {

        d.removeLast();
        ss << "remove last: ???";

    } catch (const std::out_of_range& e) {

        ss << "SHOULD catch an error: " << e.what();
    }

    valid_message = "SHOULD catch an error: deque empty, no such element";
    Test::ASSERT((ss.str() == valid_message), "Deque: exception"); // #4

    Test::runReport();
    std::cout << "****************************" << '\n' << '\n';
}

void testDequeIterators() {

    Test::reset();
    std::cout << "***** Deque Iterators *****" << '\n';

    Deque<int> d{};
    d.addFirst(5);
    d.addFirst(4);
    d.addFirst(3);
    d.addFirst(2);
    d.addFirst(1);

    std::stringstream ss{};
    ss << "non-const iterator: ";
    Deque<int>::iterator iter{};
    for (iter = d.begin(); iter != d.end(); ++iter)
        ss << *iter << ' ';

    std::string valid_str{"non-const iterator: 1 2 3 4 5 "};
    Test::ASSERT((ss.str() == valid_str), "Deque: non-const iter"); // #1

    ss.str(std::string{});
    ss << "const iterator: ";
    Deque<int>::const_iterator citer{};
    for (citer = d.cbegin(); citer != d.cend(); ++citer)
        ss << *citer << ' ';

    valid_str = "const iterator: 1 2 3 4 5 ";
    Test::ASSERT((ss.str() == valid_str), "Deque: const iter"); // #2

    ss.str(std::string{});
    ss << "non-const range-based for loop: ";
    for (auto& i : d)
        ss << i << ' ';

    valid_str = "non-const range-based for loop: 1 2 3 4 5 ";
    Test::ASSERT((ss.str() == valid_str), "Deque: non-const range iter"); // #3

    ss.str(std::string{});
    ss << "const range-based for loop: ";
    for (const auto& i : d)
        ss << i << ' ';

    valid_str = "const range-based for loop: 1 2 3 4 5 ";
    Test::ASSERT((ss.str() == valid_str), "Deque: const range iter"); // #4

    Deque<int>::iterator a_iter{d.begin()};
    Deque<int>::iterator b_iter{d.begin()};

    Test::ASSERT(a_iter == b_iter, "Deque: equal iter"); // #5
    Test::ASSERT(!(a_iter != b_iter), "Deque: not equal iter"); // #6

    ++a_iter;
    ++b_iter;
    Test::ASSERT(a_iter == b_iter, "Deque: equal iter"); // #7
    Test::ASSERT(!(a_iter != b_iter), "Deque: not equal iter"); // #8

    a_iter++;
    b_iter++;
    Test::ASSERT(a_iter == b_iter, "Deque: equal iter"); // #9
    Test::ASSERT(!(a_iter != b_iter), "Deque: not equal iter"); // #10

    a_iter++;
    Test::ASSERT(!(a_iter == b_iter), "Deque: equal iter"); // #11
    Test::ASSERT(a_iter != b_iter, "Deque: not equal iter"); // #12

    Test::ASSERT(*a_iter == 4, "Deque: iter reference"); // #13
    Test::ASSERT(*b_iter == 3, "Deque: iter reference"); // #14

    Deque<std::string_view> s_deque{};
    s_deque.addLast("This");
    s_deque.addLast("is");
    s_deque.addLast("a");
    s_deque.addLast("deque");
    s_deque.addLast("of");
    s_deque.addLast("strings.");

    ss.str(std::string{});
    ss << dequeToStr(s_deque);

    valid_str = "This is a deque of strings. ";
    Test::ASSERT((ss.str() == valid_str), "Deque: const range iter"); // #15

    Deque<std::string_view>::iterator s_iter{s_deque.begin()};
    Deque<std::string_view>::const_iterator s_citer{s_deque.cbegin()};
    ++s_iter; ++s_citer;
    ++s_iter; ++s_citer;
    ++s_iter; ++s_citer;

    valid_str = "deque";
    Test::ASSERT(*s_iter == valid_str, "Deque: non-const reference"); // #16
    Test::ASSERT(*s_citer == valid_str,"Deque: const reference"); // #17
    Test::ASSERT(s_iter->size() == 5,"Deque: non-const size"); // #18
    Test::ASSERT(s_citer->size() == 5,"Deque: const size"); // #19

    Test::runReport();
    std::cout << "***************************" << '\n' << '\n';
}

std::string dequeToStr(const Deque<int>& d) {

    std::stringstream ss;

    if (d.isEmpty()) {

        ss << "empty";

    } else {

        for (const auto& s : d)
            ss << s << ' ';
    }

    return ss.str();
}

std::string dequeToStr(const Deque<std::string_view>& d) {

    std::stringstream ss;

    if (d.isEmpty()) {

        ss << "empty";

    } else {

        for (const auto& s : d)
            ss << s << ' ';
    }

    return ss.str();
}
