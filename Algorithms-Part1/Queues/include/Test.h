/**
 * \file    Test.h
 * \author  Christine Jones 
 * \brief   Test cases for Deque container class.
 *
 * These test cases are NOT automated. They must be run and verified by hand.
 * This may change in the future.
 * 
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef TEST_H
#define TEST_H

#include "Deque.h"
#include "RandomQueue.h"

namespace Test {

void runTests();

void testDeque();
void testDequeBasicOperation();
void testDequeExceptions();
void testDequeIterators();
void printDeque(const Deque<int>& d);
void printDeque(const Deque<std::string_view>& d);

void testRandomQueue();
void testRQBasicOperation();
void testRQExceptions();
void testRQIterators();
void printRQ(const RandomQueue<int>& q);
void printRQ(const RandomQueue<std::string_view>& q);

} // namespace Test

#endif // TEST_H
