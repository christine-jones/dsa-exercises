/**
 * \file    main.cpp
 * \author  Christine Jones 
 * \brief   Client program that uses RandomQueue implementation.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "Random.h"
#include "RandomQueue.h"
#include <cassert>
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
 * Client program.
 * 
 * Reads a sequence of strings from standard input and prints to standard
 * output exactly k, where 0 <= k <= # of strings, of those strings uniformly
 * at random. Each string from the given sequence is printed at most once.
 * 
 * The number of strings, n, to be input is unknown ahead of time. For an
 * extra challenge a RandomQueue of k objects, rather than n objects, is used
 * to store the random output strings.
 * 
 * Usage: <program name> <k>
 *      k = number of strings to print to standard output, where 0 <= k <= n,
 *          and n is the number of strings read from standard input
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

    // number of words processed thus far
    int num_words{0};

    // read entire line of words
    std::string words{};
    std::getline(std::cin, words);

    // handle each word individually
    std::istringstream iss{words};
    std::string word{};
    while (iss >> word) {

        // first k words simply add to random queue
        if (num_words < k)

            random_words.enqueue(word);
        

        // for all words greater than k, generate a uniformly random number
        // between 0 and k, if the number is less than k the word is added
        // to the queue, randomly replacing another word
        else if (Random::getRandomNumber(0, num_words) < k) {

            random_words.sample() = word;
        }

        ++num_words;        
    }

    if (k > random_words.size()) {

        std::cout << "The given value of k is invalid, must be <= than the "
                  << "number of given words: " << k << '\n';
        return 1;
    }
    
    assert(random_words.size() == k);

    for (const auto& i : random_words)
        std::cout << i << '\n';

    return 0;
}
