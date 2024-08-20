#include "Percolation.h"
#include "UnionFind.h"
#include "StopWatch.h"
#include "Test.h"
#include <iostream>
#include <sstream>
#include <string>

void printUsage() {

    std::cout << "Usage: <program name> <n> <T>" << '\n';
    std::cout << "\tn = grid size, n-by-n grid" << '\n';
    std::cout << "\tT = # independent computational experiments" << '\n';
}

int main(int argc, char* argv[]) {

    if (argc != 3) {

        printUsage();
        return 1;        
    }

    std::stringstream ssarg1{argv[1]};
    std::stringstream ssarg2{argv[2]};

    int grid_size{};
    int num_trials{};

    if (!(ssarg1 >> grid_size) || !(ssarg2 >> num_trials)) {

        printUsage();
        return 1;
    }

    // start timer
    StopWatch timer{};

    // run experiments
    PercolationStats p{grid_size, num_trials};
    
    // record elapsed time of experiments
    double elapsed_time{timer.elapsed()};
    
    std::cout << "        mean = " << p.mean() << '\n';
    std::cout << "      stddev = " << p.stddev() << '\n';
    std::cout << "95% interval = ["
              << p.confidenceLow() << ", "
              << p.confidenceHigh() << "]\n";
    std::cout << "elapsed time = " << elapsed_time << " seconds" << '\n';

    return 0;
}
