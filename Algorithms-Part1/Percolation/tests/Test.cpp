/**
 * \file    TestMain.cpp
 * \author  Christine Jones 
 * \brief   Test namespace; utilities to facilitate unit testing.
 * 
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "Test.h"
#include <iomanip>
#include <iostream>
#include <string_view>

namespace Test {

int test_case{0};
int num_failed_tests{0};
int num_passed_tests{0};

void reset() {

    test_case = 0;
    num_failed_tests = 0;
    num_passed_tests = 0;
}

void runReport() {

    std::cout << "REPORT: ";
    std::cout << test_case << " TOTAL tests: ";
    std::cout << num_passed_tests << " PASSED, ";
    std::cout << num_failed_tests << " FAILED" << '\n';
}

void ASSERT(bool condition, std::string_view message) {

    if (condition) {

        std::cout << std::setw(4) << ++test_case << ": "
                  << message << ": PASSED" << '\n';
        ++num_passed_tests;

    } else {

        std::cout << std::setw(4) << ++test_case << ": "
                  << message << ": FAILED" << '\n';
        ++num_failed_tests;
    }
}

}
