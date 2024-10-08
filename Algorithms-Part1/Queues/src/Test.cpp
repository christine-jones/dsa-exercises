/**
 * \file    Test.cpp
 * \author  Christine Jones 
 * \brief   Implementation of test cases for Deque and RandomQueue container
 *          classes.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "Deque.h"
#include "RandomQueue.h"
#include "Test.h"
#include <exception>
#include <iostream>
#include <string>
#include <string_view>

namespace Test {

void runTests() {

    std::cout << "running tests..." << '\n';

    testDeque();
    testRandomQueue();
}

void testDeque() {

    testDequeBasicOperation();
    testDequeExceptions();
    testDequeIterators();
}

void testRandomQueue() {

    testRQBasicOperation();
    testRQExceptions();
    testRQIterators();
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

void testRQBasicOperation() {

    RandomQueue<int> q{};

    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';
    q.enqueue(1);
    q.enqueue(2);
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';
    q.enqueue(3);
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';
    q.enqueue(4);
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';
    q.enqueue(5);
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';
    q.enqueue(6);
    q.enqueue(7);
    q.enqueue(8);
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';
    q.enqueue(9);
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';
    q.enqueue(10);
    q.enqueue(11);
    q.enqueue(12);
    q.enqueue(13);
    q.enqueue(14);
    q.enqueue(15);
    q.enqueue(16);
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';
    q.enqueue(17);
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';

    std::cout << "sample: " << q.sample() << '\n';
    std::cout << "sample: " << q.sample() << '\n';
    std::cout << "sample: " << q.sample() << '\n';
    std::cout << "sample: " << q.sample() << '\n';
    std::cout << "sample: " << q.sample() << '\n';
    std::cout << "sample: " << q.sample() << '\n';
    std::cout << "sample: " << q.sample() << '\n';
    std::cout << "sample: " << q.sample() << '\n';
    q.sample() = 100;
    q.sample() = 200;
    q.sample() = 300;

    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';
    std::cout << "dequeue: " << q.dequeue() << '\n';
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';
    std::cout << "dequeue: " << q.dequeue() << '\n';
    std::cout << "dequeue: " << q.dequeue() << '\n';
    std::cout << "dequeue: " << q.dequeue() << '\n';
    std::cout << "dequeue: " << q.dequeue() << '\n';
    std::cout << "dequeue: " << q.dequeue() << '\n';
    std::cout << "dequeue: " << q.dequeue() << '\n';
    std::cout << "dequeue: " << q.dequeue() << '\n';
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';
    std::cout << "dequeue: " << q.dequeue() << '\n';
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';
    std::cout << "dequeue: " << q.dequeue() << '\n';
    std::cout << "dequeue: " << q.dequeue() << '\n';
    std::cout << "dequeue: " << q.dequeue() << '\n';
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';
    std::cout << "dequeue: " << q.dequeue() << '\n';
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';
    std::cout << "dequeue: " << q.dequeue() << '\n';
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';
    std::cout << "dequeue: " << q.dequeue() << '\n';
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';
    std::cout << "dequeue: " << q.dequeue() << '\n';
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';
    std::cout << "dequeue: " << q.dequeue() << '\n';
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    std::cout << "dequeue: " << q.dequeue() << '\n';
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';
    q.enqueue(4);
    q.enqueue(5);
    std::cout << "dequeue: " << q.dequeue() << '\n';
    std::cout << "dequeue: " << q.dequeue() << '\n';
    std::cout << "dequeue: " << q.dequeue() << '\n';
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';
    q.enqueue(6);
    q.enqueue(7);
    q.enqueue(8);
    q.enqueue(9);
    q.enqueue(10);
    std::cout << "dequeue: " << q.dequeue() << '\n';
    std::cout << "dequeue: " << q.dequeue() << '\n';
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';

    q.clear();
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    std::cout << "dequeue: " << q.dequeue() << '\n';
    q.enqueue(4);
    q.enqueue(5);
    std::cout << "dequeue: " << q.dequeue() << '\n';
    q.enqueue(6);
    q.enqueue(7);
    q.enqueue(8);
    q.enqueue(9);
    q.enqueue(10);
    std::cout << "dequeue: " << q.dequeue() << '\n';
    printRQ(q);
    std::cout << "isEmpty? " << (q.isEmpty() ? "true" : "false") << ' '
              << "size: " << q.size() << ' '
              << "capacity: " << q.capacity() << '\n';
}

void testRQExceptions() {

    RandomQueue<int> q{};
    
    q.enqueue(100);
    try {

        std::cout << "dequeue: " << q.dequeue() << '\n';

    } catch (const std::out_of_range& e) {

        std::cerr << "SHOULD NOT catch an error: " << e.what() << '\n';
    }
    try {

        std::cout << "dequeue: " << q.dequeue() << '\n';

    } catch (const std::out_of_range& e) {

        std::cerr << "SHOULD catch an error: " << e.what() << '\n';
    }

    q.enqueue(200);
    try {

        std::cout << "sample: " << q.sample() << '\n';

    } catch (const std::out_of_range& e) {

        std::cerr << "SHOULD NOT catch an error: " << e.what() << '\n';
    }

    q.dequeue();

    try {

        std::cout << "sample: " << q.sample() << '\n';

    } catch (const std::out_of_range& e) {

        std::cerr << "SHOULD catch an error: " << e.what() << '\n';
    }
}

void testRQIterators() {

    RandomQueue<int> q{};
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);

    std::cout << "non-random iterator: ";
    RandomQueue<int>::const_iterator titer{};
    for (titer = q.tbegin(); titer != q.tend(); ++titer)
        std::cout << *titer << ' ';
    std::cout << '\n';

    std::cout << "const iterator: ";
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


    std::cout << "iterators equal? [true] "
              << (a_iter == q.begin() ? "true" : "false") << '\n';
    std::cout << "iterators not equal? [false] "
              << (a_iter != q.begin() ? "true" : "false") << '\n';
    std::cout << "iterators equal? [false] "
              << (a_iter == q.end() ? "true" : "false") << '\n';
    std::cout << "iterators not equal? [true] "
              << (a_iter != q.end() ? "true" : "false") << '\n';
    std::cout << "iterators equal? [true] "
              << (a_iter == b_iter ? "true" : "false") << '\n';
    std::cout << "iterators not equal? [false] "
              << (a_iter != b_iter ? "true" : "false") << '\n';
    ++a_iter;
    ++b_iter;
    std::cout << "iterators equal? [true] "
              << (a_iter == b_iter ? "true" : "false") << '\n';
    std::cout << "iterators not equal? [false] "
              << (a_iter != b_iter ? "true" : "false") << '\n';
    ++a_iter;
    std::cout << "iterators equal? [false] "
              << (a_iter == b_iter ? "true" : "false") << '\n';
    std::cout << "iterators not equal? [true] "
              << (a_iter != b_iter ? "true" : "false") << '\n';
    ++a_iter;
    ++a_iter;
    ++a_iter;
    std::cout << "iterators equal? [false] "
              << (a_iter == q.begin() ? "true" : "false") << '\n';
    std::cout << "iterators not equal? [true] "
              << (a_iter != q.begin() ? "true" : "false") << '\n';
    std::cout << "iterators equal? [true] "
              << (a_iter == q.end() ? "true" : "false") << '\n';
    std::cout << "iterators not equal? [false] "
              << (a_iter != q.end() ? "true" : "false") << '\n';

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
}

void printRQ(const RandomQueue<int>& q) {

    if (q.isEmpty()) {

        std::cout << "empty" << '\n';
        return;
    }

    std::cout << "not random ";
    RandomQueue<int>::const_iterator iter;
    for (iter = q.tbegin(); iter != q.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << '\t'; 

    std::cout << "random: ";
    for (const auto& i : q)
        std::cout << i << ' ';
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

} // namespace Test
