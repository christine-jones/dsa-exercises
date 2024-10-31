/**
 * \file    main.cpp
 * \author  Christine Jones 
 * \brief   Client program that solves a generalized n-by-n slider puzzle
 *          using an A* search algorithm.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "Board.h"
#include "BoardSolver.h"
#include <fstream>
#include <iostream>
#include <sstream>

void printUsage() {

    std::cout << "Usage: <program name> <input-file>" << '\n';
    std::cout << "\tinput_file = file that contains n-by-n slider puzzle"
              << '\n';
}

/**
 * Client program.
 * 
 * Reads an n-by-n slider puzzle game board from a given input file. The game
 * board is solved using an A* search algorithm. If the puzzle is solvable, the
 * sequence of game board steps to reach the solved game board is printed to
 * standard output. 
 * 
 * The input file should contain the grid dimension, n, of the n-by-n game 
 * board on the first line, followed by the game board on subsequent lines.
 * The blank tile of a game board should be represented by a 0.
 * For example:
 * 
 *  1> 3
 *  2> 0 1 3
 *  3> 4 2 5
 *  4> 7 8 6
 * 
 * Usage: <program name> <input_file>
 *      input_file = file that contains n-by-n slider puzzle
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
    int grid_size{};
    if (!(first_iss >> grid_size)) {
        std::cerr << "Failed to read grid size from input file." << '\n';
        return 1;
    }

    if (grid_size < 2 || grid_size >= 128) {
        std::cerr << "Invalid grid size: " << grid_size << '\n';
        return 1;
    }

    Board::board binput{
        Board::board(static_cast<std::size_t>(grid_size),
                     std::vector<int>(static_cast<std::size_t>(grid_size)))};

    for (std::size_t i{0}; i < static_cast<std::size_t>(grid_size); ++i) {

        std::string line{};
        if (!std::getline(input_file, line)) {
            std::cerr << "Failed to read line from input file." << '\n';
            return 1;
        }

        std::istringstream iss{line};
        for (std::size_t j{0}; j < static_cast<std::size_t>(grid_size); ++j) {
            if (!(iss >> binput[i][j])) {
                std::cerr << "Failed to read data from input file." << '\n';
                return 1;
            }
        }
    }

    input_file.close();

    Board b{binput};
    if (!b.isValid()) {
        std::cerr << "Invalid board game." << '\n';
        return 1;
    }

    BoardSolver solver{b};

    std::cout << "SOLVED = " << (solver.isSolvable() ? "true" : "false") << " "
              << "MOVES = " << solver.moves() << '\n';
    for (auto& move : solver.solution())
        std::cout << move << '\n';

    return 0;
}
