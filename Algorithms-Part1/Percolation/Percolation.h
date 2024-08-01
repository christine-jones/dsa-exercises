#ifndef PERCOLATION_H
#define PERCOLATION_H

#include "UnionFind.h"
#include <cassert>
#include <iomanip>
#include <iostream>
#include <random>

template <typename UF>
class Percolation {

public:

    explicit Percolation(int n):
        m_openUF{(n * n) + 2}, // 2 additional sites for virtual top and bottom
        m_grid_size{n},
        m_top_index{0},
        m_bottom_index{(n * n) + 1},
        m_num_open_sites{0}
    {
        assert(n > 0);

        // open virtual top and bottom for connections
        m_openUF.open(m_top_index);
        m_openUF.open(m_bottom_index);
    }

    bool isOpen(int row, int col) const {

        assert(isValidGridIndex(row, col));
        
        return m_openUF.isOpen(indexIntoUF(row, col));
    }

    bool isFull(int row, int col) {

        // validity of (row, col) checked by isOpen() call

        if (!isOpen(row, col))
            return false;

        return m_openUF.connected(m_top_index, indexIntoUF(row, col));
    }

    int numberOfOpenSites() const { return m_num_open_sites; }

    void open(int row, int col) {

        // validity of (row, col) checked by isOpen() call

        if (isOpen(row, col))
            return;

        m_openUF.open(indexIntoUF(row, col));
        ++m_num_open_sites;

        connectNeighbors(row, col);
    }

    bool percolates() {

        return m_openUF.connected(m_top_index, m_bottom_index);
    }

    void print() const {

        std::cout << "   TOP: " << m_openUF.getIndex(0) << '\n'
                  << "BOTTOM: "
                  << m_openUF.getIndex((m_grid_size * m_grid_size) + 1) << '\n'
                  << "Number of Open Sites: " << m_num_open_sites << '\n';

        for (int i{1}; i <= m_grid_size; ++i) {
            for (int j{1}; j <= m_grid_size; ++j) {

                std::cout << std::setw(5)
                          << m_openUF.getIndex(indexIntoUF(i, j));
            }

            std::cout << '\n';
        }
    }

private:

    bool isValidGridIndex(int i, int j) const {
        
        return (i > 0) && (i <= m_grid_size) &&
               (j > 0) && (j <= m_grid_size);
    }

    int indexIntoUF(int row, int col) const {

        return ((row - 1) * m_grid_size) + col;
    }

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
        if (col == 1)
            return;

        if (isOpen(row, col - 1))
            m_openUF.join(indexIntoUF(row, col - 1), indexIntoUF(row, col));
    }

    void connectLeftNeighbor(int row, int col) {

        // there is no left neighbor
        if (col == m_grid_size)
            return;

        if (isOpen(row, col + 1))
            m_openUF.join(indexIntoUF(row, col + 1), indexIntoUF(row, col));
    }

    OpenUF<UF>  m_openUF;

    const int m_grid_size{};
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
