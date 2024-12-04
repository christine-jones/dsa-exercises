/**
 * \file    TestRandomQueue.cpp
 * \author  Christine Jones 
 * \brief   Test cases for RandomQueue class.
 * 
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "RandomQueue.h"
#include "Test.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

void testRQBasicOperation();
void testRQExceptions();
void testRQIterators();
void printRQ(const RandomQueue<int>& q);
void printRQ(const RandomQueue<std::string_view>& q);

void testRandomQueue() {

    testRQBasicOperation();
    testRQExceptions();
    testRQIterators();
}

void testRQBasicOperation() {

    Test::reset();
    std::cout << "***** Random Queue Basic *****" << '\n';

    RandomQueue<int> q{};

    Test::ASSERT(q.isEmpty(), "RQ: empty"); // #1
    Test::ASSERT(q.size() == 0, "RQ: size");  // #2
    Test::ASSERT(q.capacity() == 2, "RQ: capacity"); // #3

    q.enqueue(1);
    q.enqueue(2);
    Test::ASSERT(!q.isEmpty(), "RQ: not empty"); // #4
    Test::ASSERT(q.size() == 2, "RQ: size");  // #5
    Test::ASSERT(q.capacity() == 2, "RQ: capacity"); // #6

    q.enqueue(3);
    Test::ASSERT(q.size() == 3, "RQ: size");  // #7
    Test::ASSERT(q.capacity() == 4, "RQ: capacity"); // #8

    q.enqueue(4);
    Test::ASSERT(q.size() == 4, "RQ: size");  // #9
    Test::ASSERT(q.capacity() == 4, "RQ: capacity"); // #10

    q.enqueue(5);
    Test::ASSERT(q.size() == 5, "RQ: size");  // #11
    Test::ASSERT(q.capacity() == 8, "RQ: capacity"); // #12

    q.enqueue(6);
    q.enqueue(7);
    q.enqueue(8);
    Test::ASSERT(q.size() == 8, "RQ: size");  // #13
    Test::ASSERT(q.capacity() == 8, "RQ: capacity"); // #14

    q.enqueue(9);
    Test::ASSERT(q.size() == 9, "RQ: size");  // #15
    Test::ASSERT(q.capacity() == 16, "RQ: capacity"); // #16

    q.enqueue(10);
    q.enqueue(11);
    q.enqueue(12);
    q.enqueue(13);
    q.enqueue(14);
    q.enqueue(15);
    q.enqueue(16);
    Test::ASSERT(q.size() == 16, "RQ: size");  // #17
    Test::ASSERT(q.capacity() == 16, "RQ: capacity"); // #18

    q.enqueue(17);
    Test::ASSERT(q.size() == 17, "RQ: size");  // #19
    Test::ASSERT(q.capacity() == 32, "RQ: capacity"); // #20

    printRQ(q);
    q.sample() = 100;
    q.sample() = 200;
    q.sample() = 300;
    printRQ(q);

    q.dequeue();
    Test::ASSERT(q.size() == 16, "RQ: size");  // #21
    Test::ASSERT(q.capacity() == 32, "RQ: capacity"); // #22

    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    Test::ASSERT(q.size() == 9, "RQ: size");  // #23
    Test::ASSERT(q.capacity() == 32, "RQ: capacity"); // #24

    q.dequeue();
    Test::ASSERT(q.size() == 8, "RQ: size");  // #25
    Test::ASSERT(q.capacity() == 16, "RQ: capacity"); // #26

    q.dequeue();
    q.dequeue();
    q.dequeue();
    Test::ASSERT(q.size() == 5, "RQ: size");  // #27
    Test::ASSERT(q.capacity() == 16, "RQ: capacity"); // #28

    q.dequeue();
    Test::ASSERT(q.size() == 4, "RQ: size");  // #29
    Test::ASSERT(q.capacity() == 8, "RQ: capacity"); // #30
    
    q.dequeue();
    Test::ASSERT(q.size() == 3, "RQ: size");  // #31
    Test::ASSERT(q.capacity() == 8, "RQ: capacity"); // #32

    q.dequeue();
    Test::ASSERT(q.size() == 2, "RQ: size");  // #33
    Test::ASSERT(q.capacity() == 4, "RQ: capacity"); // #34

    q.dequeue();
    Test::ASSERT(!q.isEmpty(), "RQ: not empty"); // #35
    Test::ASSERT(q.size() == 1, "RQ: size");  // #36
    Test::ASSERT(q.capacity() == 2, "RQ: capacity"); // #37

    q.dequeue();
    Test::ASSERT(q.isEmpty(), "RQ: empty"); // #38
    Test::ASSERT(q.size() == 0, "RQ: size");  // #39
    Test::ASSERT(q.capacity() == 2, "RQ: capacity"); // #40

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);
    q.enqueue(6);
    q.enqueue(7);
    q.enqueue(8);
    q.enqueue(9);
    q.enqueue(10);
    Test::ASSERT(!q.isEmpty(), "RQ: not empty"); // #41
    Test::ASSERT(q.size() == 10, "RQ: size");  // #42
    Test::ASSERT(q.capacity() == 16, "RQ: capacity"); // #43

    q.clear();
    Test::ASSERT(q.isEmpty(), "RQ: empty after clear"); // #44

    Test::runReport();
    std::cout << "******************************" << '\n' << '\n';
}

void testRQExceptions() {

    Test::reset();
    std::cout << "***** Random Queue Exceptions *****" << '\n';

    std::stringstream ss{};
    RandomQueue<int> q{};

    q.enqueue(100);
    try {
        q.dequeue();
        ss << "dequeue: 100";

    } catch (const std::out_of_range& e) {

        ss << "SHOULD NOT catch an error: " << e.what();
    }

    std::string valid_message{"dequeue: 100"};
    Test::ASSERT((ss.str() == valid_message), "RQ: no exception"); // #1

    ss.str(std::string{});

    try {

        q.dequeue();
        ss << "dequeue: ???";

    } catch (const std::out_of_range& e) {

        ss << "SHOULD catch an error: " << e.what();
    }

    valid_message = "SHOULD catch an error: queue empty, no such element";
    Test::ASSERT((ss.str() == valid_message), "RQ: exception"); // #2
    
    ss.str(std::string{});

    q.enqueue(200);
    try {

        q.sample();
        ss << "sample: 200";

    } catch (const std::out_of_range& e) {

        ss << "SHOULD NOT catch an error: " << e.what();
    }

    valid_message = "sample: 200";
    Test::ASSERT((ss.str() == valid_message), "RQ: no exception"); // #3

    ss.str(std::string{});
    q.dequeue();

    try {

        q.sample();
        ss << "sample: ???";

    } catch (const std::out_of_range& e) {

        ss << "SHOULD catch an error: " << e.what();
    }

    valid_message = "SHOULD catch an error: queue empty, no such element";
    Test::ASSERT((ss.str() == valid_message), "RQ: exception"); // #4

    Test::runReport();
    std::cout << "***********************************" << '\n' << '\n';
}

void testRQIterators() {

    Test::reset();
    std::cout << "***** Random Queue Iterators *****" << '\n';

    std::stringstream ss{};   
    RandomQueue<int> q{};
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);

    std::cout << "       non-random iterator: ";
    RandomQueue<int>::const_iterator titer{};
    for (titer = q.tbegin(); titer != q.tend(); ++titer)
        std::cout << *titer << ' ';
    std::cout << '\n';

    std::cout << "            const iterator: ";
    RandomQueue<int>::const_iterator citer{};
    for (citer = q.cbegin(); citer != q.cend(); ++citer)
        std::cout << *citer << ' ';
    std::cout << '\n';

    std::cout << "const range-based for loop: ";
    for (const auto& i : q)
        std::cout << i << ' ';
    std::cout << '\n';

    RandomQueue<int>::const_iterator a_iter{q.begin()};
    RandomQueue<int>::const_iterator b_iter{q.begin()};

    Test::ASSERT(a_iter == q.begin(), "RQ: equal begin iter"); // #1
    Test::ASSERT(!(a_iter != q.begin()), "RQ: not equal begin iter"); // #2
    Test::ASSERT(!(a_iter == q.end()), "RQ: equal end iter"); // #3
    Test::ASSERT(a_iter != q.end(), "RQ: not equal end iter"); // #4
    Test::ASSERT(a_iter == b_iter, "RQ: equal iter"); // #5
    Test::ASSERT(!(a_iter != b_iter), "RQ: not equal iter"); // #6

    ++a_iter;
    ++b_iter;
    Test::ASSERT(a_iter == b_iter, "RQ: equal iter"); // #7
    Test::ASSERT(!(a_iter != b_iter), "RQ: not equal iter"); // #8

    ++a_iter;
    Test::ASSERT(!(a_iter == b_iter), "RQ: equal iter"); // #9
    Test::ASSERT(a_iter != b_iter, "RQ: not equal iter"); // #10

    ++a_iter;
    ++a_iter;
    ++a_iter;
    Test::ASSERT(!(a_iter == q.begin()), "RQ: equal begin iter"); // #11
    Test::ASSERT(a_iter != q.begin(), "RQ: not equal begin iter"); // #12
    Test::ASSERT(a_iter == q.end(), "RQ: equal end iter"); // #13
    Test::ASSERT(!(a_iter != q.end()), "RQ: not equal end iter"); // #14

    std::cout << "reference: " << *b_iter << '\n';

    RandomQueue<std::string_view> s_queue{};
    s_queue.enqueue("This");
    s_queue.enqueue("is");
    s_queue.enqueue("a");
    s_queue.enqueue("random");
    s_queue.enqueue("queue");
    s_queue.enqueue("of");
    s_queue.enqueue("strings.");
    printRQ(s_queue);

    RandomQueue<std::string_view>::const_iterator s_citer{s_queue.cbegin()};
    ++s_citer;
    ++s_citer;
    ++s_citer;
    std::cout << "reference: " << *s_citer << '\n';
    std::cout << "size of string via pointer: " << s_citer->size() << '\n';

    Test::runReport();
    std::cout << "**********************************" << '\n';

}

void printRQ(const RandomQueue<int>& q) {

    if (q.isEmpty()) {

        std::cout << "empty" << '\n';
        return;
    }

    std::cout << "not random: ";
    RandomQueue<int>::const_iterator iter;
    for (iter = q.tbegin(); iter != q.end(); ++iter)
        std::cout << std::setw(3) << *iter << ' ';
    std::cout << '\n'; 

    std::cout << "    random: ";
    for (const auto& i : q)
        std::cout << std::setw(3) << i << ' ';
    std::cout << '\n';
}

void printRQ(const RandomQueue<std::string_view>& q) {

    if (q.isEmpty()) {

        std::cout << "empty" << '\n';
        return;
    }

    for (const auto& s : q)
        std::cout << s << ' ';
    std::cout << '\n';
}
