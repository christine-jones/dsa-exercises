/**
 * \file    Percolation.cpp
 * \author  Christine Jones 
 * \brief   Implementation of the PercolationStats class that runs monte-carlo
 *          simulation to estimate the percolation threshold.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "Percolation.h"
#include <algorithm>
#include <cassert>
#include <cmath>

/**
 * Namespace that contains random number generator.
 */
namespace Random {

std::random_device rd{};
std::mt19937 genMT{rd()};

/**
 * Retruns a random number between the given min and max, inclusive, using a
 * uniform distribution.
 * 
 * \param int Minimum number.
 * \param int Maximum number; must be greater than minimum number.
 * 
 * \return int Number between given min and max, inclusive.
 */
int getRandomNumber(int min, int max) {

    assert(min < max);
    return std::uniform_int_distribution{min, max}(genMT);
}

} // namespace Random


int PercolationStats::percolate() {

    // TBD: configuration of the Union Find algorithm variant
    Percolation<WeightedUF> p{m_grid_size};

    while (!p.percolates()) {

        int row{Random::getRandomNumber(1, m_grid_size)};
        int col{Random::getRandomNumber(1, m_grid_size)};

        if (p.isOpen(row, col))
            continue;

        p.open(row, col);
    }

    return p.numberOfOpenSites();
}

void PercolationStats::run_experiments() {

    for (std::size_t i{0}; i < static_cast<std::size_t>(m_num_trials); ++i) {
            
        m_percolate_thresholds[i] =
            percolate() / static_cast<double>(m_grid_size * m_grid_size);
    }
}

void PercolationStats::calculate_stats() {                

    // calculate mean
    double sum{std::accumulate(m_percolate_thresholds.begin(),
                               m_percolate_thresholds.end(), 0.0)};
    m_mean = sum / static_cast<double>(m_percolate_thresholds.size());

    // calculate standard deviation
    double accum{0.0};
    std::for_each(m_percolate_thresholds.begin(),
                  m_percolate_thresholds.end(),
                  [&accum, this](const double d) {
                        accum += (d - this->m_mean) * (d - this->m_mean);
                  });
    m_stddev =
      std::sqrt(accum / static_cast<double>(m_percolate_thresholds.size() - 1));

    // calculate 95% confidence intervals
    static constexpr double z{1.96};

    double interval{(z * m_stddev) / std::sqrt(m_percolate_thresholds.size())};
    m_confidence_low  = m_mean - interval;
    m_confidence_high = m_mean + interval;
}
