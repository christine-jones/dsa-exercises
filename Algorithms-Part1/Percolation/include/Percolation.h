/**
 * \file    Percolation.h
 * \author  Christine Jones 
 * \brief   Definition of the Percolation class that models a percolation
 *          system and the PercolationStats class that runs Monte-Carlo
 *          simulation to estimate the percolation threshold.
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
#include <sstream>
#include <string>

/**
 * Class that performs Monte-Carlo style experiments using the model
 * percolation system imlemented by the Percolation class to compute an
 * estimate of the percolation threshold.
 * 
 * A given number of independent trails is run. For each trial, a fully  
 * blocked percolation system of the given grid size is created. Sites are
 * opened uniformily at random until the system percolates. At which point,
 * the fraction of opened vs blocked sites is used to determine the
 * percolation threshold for that trial run.
 * 
 * A more accurate estimate of the percolation threshold is calculated by
 * averaging the results over all the trials. 
 * 
 * The Weighted Union Find algorithm implements the underlying connection
 * process of the percolation system. Future work should allow the Union Find
 * algorithm variant to be a configurable option. This would allow greater
 * flexibilty in running experiments and comparison of Union Find algorithms.
 */
class PercolationStats {

public:

    /**
     * Constructor. The given number of independent trials is run, and
     * statistics calculated.
     * 
     * \param int n-by-n grid size; must be greater than zero.
     * \param int Number of independent trials; must be greater than zero.
     */
    PercolationStats(int n, int trials);

    /**
     * Methods for accessing percolation threshold statistics: mean, standard
     * deviation, 95% confidence interval.
     */
    double mean() const           { return m_mean; }
    double stddev() const         { return m_stddev; }
    double confidenceLow() const  { return m_confidence_low; }
    double confidenceHigh() const { return m_confidence_high; }

private:

    /**
     * Run single trial. Instantiates a percolation system and opens sites
     * uniformily at random until system percolates. Returns the number of
     * sites opened.
     */
    int  percolate();

    /**
     * Run all trials; record the percolation threshold for each trial.
     */
    void run_experiments();

    /**
     * Given recorded percolation thresholds for all trials, calculate
     * statistics: mean, standard deviation, 95% confidence interval.
     */
    void calculate_stats();

    const int m_grid_size{};
    const int m_num_trials{};

    // single percolation threshold recorded for each trial run
    std::vector<double> m_percolate_thresholds{};

    double m_mean{};
    double m_stddev{};
    double m_confidence_low{};
    double m_confidence_high{};

};

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
     * \param int n-by-n grid size; must be greater than zero.
     */
    explicit Percolation(int n);

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
    bool isOpen(int row, int col) const;

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
    bool isFull(int row, int col);

    /**
     * Return the total number of open sites within the grid.
     * 
     * \return int Number of open sites within the grid.
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
    void open(int row, int col);

    /**
     * Determine if the system percolates, i.e., a site at the bottom of the
     * grid is open and connected to a site at the top of the grid via a chain
     * of open neighboring grid sites.
     * 
     * \return bool True if the system percolates; False otherwise.
     */
    bool percolates();

    /**
     * Print n-by-n grid and additional class data to stdout for testing
     * purposes.
     */
    std::string toStr() const;

private:

    /**
     * Verify that the row/column grid index is valid.
     */
    bool isValidGridIndex(int i, int j) const;

    /**
     * Convert row/column grid index into vector index for UnionFind algorithm.
     */
    int indexIntoUF(int row, int col) const;

    /**
     * Connect the given grid site to any open grid neighbors.
     */
    void connectNeighbors(int row, int col);
    void connectTopNeighbor(int row, int col);
    void connectBottomNeighbor(int row, int col);
    void connectRightNeighbor(int row, int col);
    void connectLeftNeighbor(int row, int col);

    // UnionFind algorithm used to manage open connections within the grid.
    //
    // The n-by-n grid is stored as a flat vector. In addition there is a
    // "top" and "bottom" included. Therefore, the size of the UnionFind vector
    // is ((n*n) + 2).
    //
    // Sites in the top row of the grid connect to the "top", and sites in the
    // bottom row of the grid connect to the "bottom". The system percolates
    // when the virtual "top" and "bottom" are connected via a path of open
    // grid sites.
    OpenUF<UF>  m_openUF;

    const int m_grid_size{};

    // virtual top and bottom; system percolates when top and bottom connect
    const int m_top_index{};
    const int m_bottom_index{};

    int m_num_open_sites{};

};

template <typename UF>
Percolation<UF>::Percolation(int n):
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

template <typename UF>
bool Percolation<UF>::isOpen(int row, int col) const {
        
    return m_openUF.isOpen(indexIntoUF(row, col));
}

template <typename UF>
bool Percolation<UF>::isFull(int row, int col) {

    if (!isOpen(row, col))
        return false;

    return m_openUF.connected(m_top_index, indexIntoUF(row, col));
}

template <typename UF>
void Percolation<UF>::open(int row, int col) {

    if (isOpen(row, col))
        return;

    m_openUF.open(indexIntoUF(row, col));
    ++m_num_open_sites;

    connectNeighbors(row, col);
}

template <typename UF>
bool Percolation<UF>::percolates() {

    return m_openUF.connected(m_top_index, m_bottom_index);
}

template <typename UF>
std::string Percolation<UF>::toStr() const {

    std::stringstream ss;
    ss << "   TOP: " << m_openUF.getID(0) << '\n'
        << "BOTTOM: "
        << m_openUF.getID((m_grid_size * m_grid_size) + 1) << '\n'
        << "Number of Open Sites: " << m_num_open_sites << '\n';

    for (int i{1}; i <= m_grid_size; ++i) {
        for (int j{1}; j <= m_grid_size; ++j) {

            ss << std::setw(5)
                << m_openUF.getID(indexIntoUF(i, j));
        }
        ss << '\n';
    }

    return ss.str();
}

template <typename UF>
bool Percolation<UF>::isValidGridIndex(int i, int j) const {
        
    return (i > 0) && (i <= m_grid_size) &&
           (j > 0) && (j <= m_grid_size);
}

template <typename UF>
int Percolation<UF>::indexIntoUF(int row, int col) const {

    assert(isValidGridIndex(row, col));
    return ((row - 1) * m_grid_size) + col;
}

template <typename UF>
void Percolation<UF>::connectNeighbors(int row, int col) {

    connectTopNeighbor(row, col);
    connectBottomNeighbor(row, col);
    connectRightNeighbor(row, col);
    connectLeftNeighbor(row, col);
}

template <typename UF>
void Percolation<UF>::connectTopNeighbor(int row, int col) {

    // if top row, connect to virtual top
    if (row == 1) {
        m_openUF.join(m_top_index, indexIntoUF(row, col));
        return;
    }

    if (isOpen(row - 1, col))
        m_openUF.join(indexIntoUF(row - 1, col), indexIntoUF(row, col));
}

template <typename UF>
void Percolation<UF>::connectBottomNeighbor(int row, int col) {

    // if bottom row, connect to virtural bottom
    if (row == m_grid_size) {
        m_openUF.join(m_bottom_index, indexIntoUF(row, col));
        return;
    }

    if (isOpen(row + 1, col))
        m_openUF.join(indexIntoUF(row + 1, col), indexIntoUF(row, col));
}

template <typename UF>
void Percolation<UF>::connectRightNeighbor(int row, int col) {

    // there is no right neighbor
    if (col == m_grid_size)
        return;

    if (isOpen(row, col + 1))
        m_openUF.join(indexIntoUF(row, col + 1), indexIntoUF(row, col));
}

template <typename UF>
void Percolation<UF>::connectLeftNeighbor(int row, int col) {

    // there is no left neighbor
    if (col == 1)
        return;

    if (isOpen(row, col - 1))
        m_openUF.join(indexIntoUF(row, col - 1), indexIntoUF(row, col));
}

#endif // PERCOLATION_H
