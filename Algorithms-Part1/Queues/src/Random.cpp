/**
 * \file    Random.cpp
 * \author  Christine Jones 
 * \brief   
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "Random.h"
#include <cassert>
#include <random>

namespace Random {

std::random_device rd{};
std::mt19937 genMT{rd()};

/**
 * Returns a random number between the given min and max, inclusive, using a
 * uniform distribution.
 * 
 * \param int Minimum number.
 * \param int Maximum number; must be greater or equal to minimum number.
 * 
 * \return int Number between given min and max, inclusive.
 */
int getRandomNumber(int min, int max) {

    assert(min <= max);
    return std::uniform_int_distribution{min, max}(genMT);
}

} // namespace Random
