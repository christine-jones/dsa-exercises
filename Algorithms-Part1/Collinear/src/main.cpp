/**
 * \file    main.cpp
 * \author  Christine Jones 
 * \brief   Client program that compares the performance of two algorithms that
 *          identify line segments within a given set of points.         
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */ 

#include "CollinearPoints.h"
#include "Point.h"
#include "StopWatch.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

void printUsage() {

    std::cout << "Usage: <program name> <input-file>" << '\n';
    std::cout << "\tinput_file = file that contains input data" << '\n';
}

/**
 * Client program.
 * 
 * Reads a set of points from a given input file. The points are processed by
 * two different algorithms, BruteCollinearPoints and FastCollinearPoints, both
 * of which find every line segment that connects a subset of 4 or more of the
 * points.
 * 
 * The results are printed to standard output, including the elapsed time of
 * each algorithm for performance comparison.
 * 
 * The input file is expected to be in the following format:
 * 
 *  1> # number of points
 *  2> x y
 *  3> x y
 *     .
 *     .
 *     .
 *  #> x y
 * 
 * For example:
 * 
 *  1> 6
 *  2> 19000 10000
 *  3> 18000 10000
 *  4> 32000 10000
 *  5> 21000 10000
 *  6> 1234  5678
 *  7> 14000 10000
 * 
 * Usage: <program name> <input_file>
 *      input_file = file that contains input data
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

    std::string first_line{};
    if (!std::getline(input_file, first_line)) {
        std::cerr << "Failed to read first line from input file." << '\n';
        return 1;
    }

    std::istringstream first_iss{first_line};
    int num_points{};
    if (!(first_iss >> num_points)) {
        std::cerr << "Failed to read number of points from input file." << '\n';
        return 1;
    }

    if (num_points <= 0) {
        std::cerr << "Invalid number of points: " << num_points << '\n';
        return 1;
    }

    std::vector<Point> brute_points(static_cast<std::size_t>(num_points));

    for (std::size_t i{0}; i < static_cast<std::size_t>(num_points); ++i) {

        std::string line{};
        if (!std::getline(input_file, line)) {
            std::cerr << "Failed to read line from input file." << '\n';
            return 1;
        }

        std::istringstream iss{line};
        int x{}, y{};
        if (!(iss >> x >> y)) {
            std::cerr << "Failed to read point data from input file." << '\n';
            return 1;
        }

        brute_points[i] = Point(x, y);
    }

    input_file.close();

    // clean copy for each algorithm
    std::vector<Point> fast_points{brute_points};

    StopWatch timer{};
    BruteCollinearPoints brute{brute_points};
    double brute_elapsed{timer.elapsed()};

    timer.reset();
    FastCollinearPoints fast(fast_points);
    double fast_elapsed{timer.elapsed()};

    std::cout << "Brute: segments = " << brute.numberOfSegments() << '\t'
              << "elapsed time =  " << brute_elapsed << '\n';

    std::cout << " Fast: segments = " << fast.numberOfSegments() << '\t'
              << "elapsed time =  " << fast_elapsed << '\n';

    return 0;
}
