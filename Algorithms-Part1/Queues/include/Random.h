/**
 * \file    Random.h
 * \author  Christine Jones 
 * \brief   
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef RANDOM_H
#define RANDOM_H

namespace Random {

/**
 * Returns a random number between the given min and max, inclusive, using a
 * uniform distribution.
 * 
 * \param int Minimum number.
 * \param int Maximum number; must be greater or equal to minimum number.
 * 
 * \return int Number between given min and max, inclusive.
 */
int getRandomNumber(int min, int max);

} // namespace Random

#endif // RANDOM_H
