/**
 * \file    Percolation.h
 * \author  Christine Jones 
 * \brief   
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef PERCOLATION_H
#define PERCOLATION_H

#include "UnionFind.h"
#include <cassert>
#include <iomanip>
#include <iostream>
#include <random>

/**
 * Class that models a percolation system.
 * 
 * Creates an n-by-n grid, with all sites intially blocked. A method is
 * provided to open a given grid site and connect that newly open grid site
 * to any open neighboring grid sites. The system percolates when a grid site
 * in the bottom row is connected to a grid site in the top row via a chain
 * of open neighboring grid sites.
 * 
 * An open-enabled UnionFind algorithm is required as class input via template
 * parameter. The UnionFind algorithm manages connections within the grid.
 */
template <typename UF>
class Percolation {

public:

    /**
     * Constructor. Initializes a completely blocked n-by-n grid
     * 
     * \param int Grid size; must be greater than zero.
     */
    explicit Percolation(int n):
        m_openUF{(n * n) + 2}, // 2 additional sites for virtual top and bottom
        m_grid_size{n},
        m_top_index{0},
        m_bottom_index{(n * n) + 1},
        m_num_open_sites{0}
    {
        assert(n > 0);

        // open virtual top and bottom
        m_openUF.open(m_top_index);
        m_openUF.open(m_bottom_index);
    }

    /**
     * Determine if the given grid site is open.
     * 
     * \param int Row index; must be greater than zero and less than or equal
     *            to grid size.
     * \param int Column index; must be greater than zero and less than or
     *            equal to grid size.
     * 
     * \return bool True if grid site is open; False otherwise.
     */
    bool isOpen(int row, int col) const {
        
        return m_openUF.isOpen(indexIntoUF(row, col));
    }
    /**
     * Determine if the given grid site is full, i.e., connected to top row of
     * grid via a chain of open neighboring grid sites.
     * 
     * \param int Row index; must be greater than zero and less than or equal
     *            to grid size.
     * \param int Column index; must be greater than zero and less than or
     *            equal to grid size.
     * 
     * \return bool True if grid site is full; False otherwise.
     */
    bool isFull(int row, int col) {

        if (!isOpen(row, col))
            return false;

        return m_openUF.connected(m_top_index, indexIntoUF(row, col));
    }

    /**
     * Return the total number of open sites within the grid.
     * 
     * \param int Row index; must be greater than zero and less than or equal
     *            to grid size.
     * \param int Column index; must be greater than zero and less than or
     *            equal to grid size.
     * 
     * \return int Total number of open sites within the grid.
     */
    int numberOfOpenSites() const { return m_num_open_sites; }

    /**
     * Open the given grid site and connect to any open neighbors.
     * 
     * \param int Row index; must be greater than zero and less than or equal
     *            to grid size.
     * \param int Column index; must be greater than zero and less than or
     *            equal to grid size.
     */
    void open(int row, int col) {

        if (isOpen(row, col))
            return;

        m_openUF.open(indexIntoUF(row, col));
        ++m_num_open_sites;

        connectNeighbors(row, col);
    }

    /**
     * Determine if the system percolates, i.e., a site at the bottom of the
     * grid is open and connected to a site at the top of the grid via a chain
     * of open neighboring grid sites.
     * 
     * \return bool True if the system percolates; False otherwise.
     */
    bool percolates() {

        return m_openUF.connected(m_top_index, m_bottom_index);
    }

    /**
     * Print n-by-n grid and additional class data to stdout for testing
     * purposes.
     */
    void print() const {

        std::cout << "   TOP: " << m_openUF.getID(0) << '\n'
                  << "BOTTOM: "
                  << m_openUF.getID((m_grid_size * m_grid_size) + 1) << '\n'
                  << "Number of Open Sites: " << m_num_open_sites << '\n';

        for (int i{1}; i <= m_grid_size; ++i) {
            for (int j{1}; j <= m_grid_size; ++j) {

                std::cout << std::setw(5)
                          << m_openUF.getID(indexIntoUF(i, j));
            }

            std::cout << '\n';
        }
    }

private:

    /**
     * Verify that the row/column grid index is valid.
     */
    bool isValidGridIndex(int i, int j) const {
        
        return (i > 0) && (i <= m_grid_size) &&
               (j > 0) && (j <= m_grid_size);
    }

    /**
     * Convert row/column grid index into vector index for UnionFind algorithm.
     */
    int indexIntoUF(int row, int col) const {

        assert(isValidGridIndex(row, col));
        return ((row - 1) * m_grid_size) + col;
    }

    /**
     * Connect the given grid site to any open grid neighbors.
     */
    void connectNeighbors(int row, int col) {

        connectTopNeighbor(row, col);
        connectBottomNeighbor(row, col);
        connectRightNeighbor(row, col);
        connectLeftNeighbor(row, col);
    }

    void connectTopNeighbor(int row, int col) {

        // if top row, connect to virtual top
        if (row == 1) {
            m_openUF.join(m_top_index, indexIntoUF(row, col));
            return;
        }

        if (isOpen(row - 1, col))
            m_openUF.join(indexIntoUF(row - 1, col), indexIntoUF(row, col));
    }

    void connectBottomNeighbor(int row, int col) {

        // if bottom row, connect to virtural bottom
        if (row == m_grid_size) {
            m_openUF.join(m_bottom_index, indexIntoUF(row, col));
            return;
        }

        if (isOpen(row + 1, col))
            m_openUF.join(indexIntoUF(row + 1, col), indexIntoUF(row, col));
    }

    void connectRightNeighbor(int row, int col) {

        // there is no right neighbor
        if (col == m_grid_size)
            return;

        if (isOpen(row, col + 1))
            m_openUF.join(indexIntoUF(row, col + 1), indexIntoUF(row, col));
    }

    void connectLeftNeighbor(int row, int col) {

        // there is no left neighbor
        if (col == 1)
            return;

        if (isOpen(row, col - 1))
            m_openUF.join(indexIntoUF(row, col - 1), indexIntoUF(row, col));
    }

    // UnionFind algorithm used to manage open connections within the grid.
    //
    // The n-by-n grid is stored as a flat vector. In addition there is a
    // "top" and "bottom" included. Therefore, the size of the UnionFind vector
    // is ((n*n) + 2).
    //
    // The top row of the grid connects the "top" and bottom row of the grid to
    // the "bottom". The system percolates when the virtual "top" and "bottom"
    // sites are connected via a path of open grid sites.
    OpenUF<UF>  m_openUF;

    const int m_grid_size{};

    // virtual top and bottom; system percolates when top and bottom connect
    const int m_top_index{};
    const int m_bottom_index{};

    int m_num_open_sites{};

};

class PercolationStats {

public:

    PercolationStats(int n, int trials):
        m_grid_size{n},
        m_num_trials{trials},
        m_percolate_thresholds{
            std::vector<double>(static_cast<std::size_t>(trials))},
        m_mean{0.0},
        m_stddev{0.0},
        m_confidence_low{0.0},
        m_confidence_high{0.0}
    {
        assert(m_grid_size > 0);
        assert(m_num_trials > 0);

        run_experiments();
        calculate_stats();  
    }

    double mean() const           { return m_mean; }
    double stddev() const         { return m_stddev; }
    double confidenceLow() const  { return m_confidence_low; }
    double confidenceHigh() const { return m_confidence_high; }

private:

    int  percolate();

    void run_experiments();
    void calculate_stats();

    const int m_grid_size{};
    const int m_num_trials{};

    std::vector<double> m_percolate_thresholds{};

    double m_mean{};
    double m_stddev{};
    double m_confidence_low{};
    double m_confidence_high{};

};

#endif // PERCOLATION_H
