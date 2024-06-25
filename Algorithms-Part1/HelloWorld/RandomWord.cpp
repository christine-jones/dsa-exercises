#include <iostream>
#include <random>
#include <sstream>
#include <string>

int main() {

    int num_words{0};
    std::string champion_word{};

    // set up random number generator
    std::random_device rd;
    std::mt19937 gen{rd()};

    // read entire line of words
    std::string words{};
    std::getline(std::cin, words);

    // handle each word individually
    std::istringstream iss{words};
    std::string word{};
    while (iss >> word) {

        ++num_words;

        // set up bernoulli distribution; give "true" 1/num_words of the time
        std::bernoulli_distribution d{1.0 / num_words};

        if (d(gen)) {

            // bernoulli returned "true", new champion word
            champion_word = word;
        }
    }

    std::cout << champion_word << '\n';
}
