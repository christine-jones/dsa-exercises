/**
 * \file    main.cpp
 * \author  Christine Jones 
 * \brief
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "Deque.h"
#include <iostream>

/**
 * Main program.
 * 
 * Usage: <program name>
 * 
 */
int main() {

    Deque<int> myDeque{};

    myDeque.addFirst(5);
    myDeque.addFirst(4);
    myDeque.addFirst(3);
    myDeque.addFirst(2);
    myDeque.addFirst(1);

    for (auto i : myDeque)
        std::cout << i << " ";
    std::cout << '\n';

    return 0;
}
