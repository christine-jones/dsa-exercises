/**
 * \file    TestMain.cpp
 * \author  Christine Jones 
 * \brief   Test namespace; utilities to facilitate unit testing.
 * 
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef TEST_H
#define TEST_H

#include <string_view>

void testPercolation();
void testQuickUF();
void testOpenQuickUF();
void testWeightedUF();
void testOpenWeightedUF();

namespace Test {

void reset();
void runReport();

void ASSERT(bool condition, std::string_view message);

}

#endif // TEST_H
