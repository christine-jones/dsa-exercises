/**
 * \file    main.cpp
 * \author  Christine Jones 
 * \brief
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "Random.h"
#include "RandomQueue.h"
#include <iostream>
#include <sstream>
#include <string>

void printUsage() {

    std::cout << "Usage: <program name> <k>" << '\n';
    std::cout << "\tk = number of strings to print to standard output,\n"
              << "\t    where 0 <= k <= n, and n is the number of strings\n"
              << "\t    read from standard input\n";
}

/**
 * Main program.
 * 
 * Usage: <program name> <k>
 *      k = number of strings to print to standard output, where 0 <= k <= n,
 *          and n is the number of strings read from standard input
 * 
 */
int main(int argc, char* argv[]) {

    if (argc != 2) {

        printUsage();
        return 1;        
    }

    int k{};
    std::stringstream ssarg1{argv[1]};

    if (!(ssarg1 >> k)) {

        printUsage();
        return 1;
    }

    if (k < 0) {

        std::cout << "Given value of k is invalid, must be >= 0: "
                  << k << '\n';
        printUsage();
        return 1;
    }

    RandomQueue<std::string> random_words{};

    // number of words read thus far
    int num_words{0};

    // read entire line of words
    std::string words{};
    std::getline(std::cin, words);

    // handle each word individually
    std::istringstream iss{words};
    std::string word{};
    while (iss >> word) {

        if (num_words < k)

            random_words.enqueue(word);
        
        else if (Random::getRandomNumber(0, num_words) < k) {

            random_words.sample() = word;

        }

        ++num_words;        
    }

    if (k > random_words.size()) {

        std::cout << "The given value of k is invalid, must be <= than the "
                  << "number of given words: " << k << '\n';
        return 0;
    }
    
    assert(random_words.size() == k);

    RandomQueue<std::string>::const_iterator iter{random_words.cbegin()};
    for (int i{0}; i < k; ++i, ++iter) {
        std::cout << *iter << '\n';
    }

    return 0;
}
