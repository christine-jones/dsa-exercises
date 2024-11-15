/**
 * \file    main.cpp
 * \author  Christine Jones 
 * \brief   Client that stores 2-dimensional point data in a KDTree.           
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */ 

#include "KDTree.h"
#include "Point2D.h"
#include "StopWatch.h"
#include <fstream>
#include <iostream>
#include <sstream>

void printUsage() {

    std::cout << "Usage: <program name> <input-file>" << '\n';
    std::cout << "\tinput_file = file that contains list of points"
              << '\n';
}

/**
 * Client program.
 * 
 * Reads in 2-dimensional coordinate point data from a file. The points must
 * be within the unit square, i.e., x and y coordinates between 0 and 1,
 * inclusive. The points are stored in a KDTree. A test query for nearest
 * point is given, elapse time reported.
 * 
 * The input file is expected to be in the following format:
 * 
 *  1> x y
 *  2> x y
 *     .
 *     .
 *     .
 *  n> x y
 * 
 * For example:
 *
 * 1> 0.372 0.497
 * 2> 0.564 0.413
 * 3> 0.226 0.577
 *      .
 *      .
 *      .
 * n> 0.499 0.208
 * 
 * Usage: <program name> <input_file>
 *      input_file = file that contains a list of points
 */
int main(int argc, char* argv[]) {

    if (argc != 2) {
        printUsage();
        return 1;        
    }

    std::ifstream input_file{argv[1]};
    if (!input_file) {
        std::cerr << "Failed to open input file." << '\n';
        return 1;
    }

    KDTree tree{};

    std::string line{};
    while (std::getline(input_file, line)) {

        std::istringstream iss{line};
        double x{}, y{};
        if (!(iss >> x >> y)) {
            std::cerr << "Failed to read point data from input file." << '\n';
            return 1;
        }

        tree.insert(Point2D{x, y});
    }

    input_file.close();

    std::cout << "Number of Nodes = " << tree.size() << '\n';

    StopWatch timer{};
    Point2D nearest{tree.nearest(Point2D{0.81, 0.30})};
    double elapsed{timer.elapsed()};

    std::cout << "Nearest to " << Point2D{0.81, 0.30} << ": "
              << nearest << " (" << elapsed << ")" << '\n';

    return 0;
}
