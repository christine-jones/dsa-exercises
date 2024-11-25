/**
 * \file    TestMain.cpp
 * \author  Christine Jones 
 * \brief   Main program to run test cases for Percolation project.
 * 
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "Test.h"

#include <iostream>

int main() {

    std::cout << "Running Tests..." << '\n' << '\n';
    testPercolation();
    testQuickUF();
    testOpenQuickUF();
    testWeightedUF();
    testOpenWeightedUF();
    std::cout << '\n' << "COMPLETE" << '\n';

    return 0;
}
