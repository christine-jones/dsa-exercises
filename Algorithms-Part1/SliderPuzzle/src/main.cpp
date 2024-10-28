/**
 * \file    main.cpp
 * \author  Christine Jones 
 * \brief
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "Board.h"
#include "BoardSolver.h"
#include <iostream>

int main() {

    Board b1{board{{1, 2, 3},
                   {0, 7, 6},
                   {5, 4, 8}}};
    BoardSolver solver{b1};

    std::cout << "SOLVED = " << (solver.isSolvable() ? "true" : "false") << " "
              << "MOVES = " << solver.moves() << '\n';
    for (auto& b : solver.solution())
        std::cout << b << '\n';

    return 0;
}
