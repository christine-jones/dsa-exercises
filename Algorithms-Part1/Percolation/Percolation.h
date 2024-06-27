#ifndef PERCOLATION_H
#define PERCOLATION_H

#include "UnionFind.h"
#include <cassert>

template <typename UF>
class Percolation {

public:

    explicit Percolation(int n):
        m_openUF{(n * n) + 2}, // 2 additional sites for virtual top and bottom
        m_grid_size{n},
        m_num_open_sites{0},
        m_top_index{0},
        m_bottom_index{(n * n) + 1}
    {
        assert(n > 0);

        // open virtual top and bottom for connections
        m_openUF.open(m_top_index);
        m_openUF.open(m_bottom_index);
    }

    bool isOpen(int row, int col) const {

        return m_openUF.isOpen(indexIntoUF(row, col));
    }

    bool isFull(int row, int col) const {

        assert(isOpen(row, col));
        return m_openUF.connected(m_top_index, indexIntoUF(row, col));
    }

    int numberOfOpenSites() const { return m_num_open_sites; }

    void open(int row, int col) {

        if (isOpen(row, col))
            return;

        int index{indexIntoUF(row, col)};

        m_openUF.open(index);
        ++m_num_open_sites;

        // if top row, connect to virtual top
        if (row == 1)
            m_openUF.connect(m_top_index, index);

        // if bottom row, connect to virtural bottom
        if (row == m_grid_size)
            m_openUF.connect(m_bottom_index, index);
    }

    bool percolates() const {

        return m_openUF.connected(m_top_index, m_bottom_index);
    }

private:

    int indexIntoUF(int row, int col) const {

        assert(isValidGridIndex(row) && isValidGridIndex(col));

        return ((row - 1) * m_grid_size) + col;
    }

    bool isValidGridIndex(int i) const {
        
        return (i > 0) && (i <= m_grid_size);
    }

    OpenUF<UF>  m_openUF;

    int m_grid_size{};
    int m_num_open_sites{};

    int m_top_index{};
    int m_bottom_index{};

};

#endif // PERCOLATION_H
