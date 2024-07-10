#include "Percolation.h"
#include "UnionFind.h"
#include "Test.h"
#include <iostream>

int main() {

    PercolationStats p{200, 100};

    std::cout << "mean = " << p.mean() << '\n';
    std::cout << "stddev = " << p.stddev() << '\n';
    std::cout << "95% confidence interval = "
              << '[' << p.confidenceLow() << ", "
              << p.confidenceHigh() << "]\n";

    return 0;
}
