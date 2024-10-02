/**
 * \file    main.cpp
 * \author  Christine Jones 
 * \brief
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "Deque.h"
#include "RandomQueue.h"
#include "Test.h"
#include <iostream>

/**
 * Main program.
 * 
 * Usage: <program name>
 * 
 */
int main() {

    RandomQueue<int> rqueue{};

    std::cout << "Empty? " << (rqueue.isEmpty() ? "true" : "false") << '\n';

    rqueue.enqueue(1);
    rqueue.enqueue(2);
    rqueue.enqueue(3);
    rqueue.enqueue(4);
    rqueue.enqueue(5);

    for (int i{0}; i < 10; ++i) {

        RandomQueue<int>::const_iterator iter{};
        for (iter = rqueue.cbegin(); iter != rqueue.cend(); ++iter)
            std::cout << *iter << ' ';
        std::cout << '\n';
    }

    return 0;
}
