# Percolation

C++ implementation of the percolation programming exercise in **Module 2, Union-Find** of the [Princeton University's Algorithms, Part 1](https://www.coursera.org/learn/algorithms-part1) course on [coursera](https://www.coursera.org/).

# Problem Statement

This [specification](https://coursera.cs.princeton.edu/algs4/assignments/percolation/specification.php) describes the percolation problem and assignment requirements. A brief description is excerpted here.

## Percolation

> Given a composite system comprised of randomly distributed insulating and metallic materials: what fraction of the materials need to be metallic so that the composite system is an electrical conductor? Given a porous landscape with water on the surface (or oil below), under what conditions will the water be able to drain through to the bottom (or the oil to gush through to the surface)? Scientists have defined an abstract process known as percolation to model such situations.

## The model

> We model a percolation system using an n-by-n grid of sites. Each site is either open or blocked. A full site is an open site that can be connected to an open site in the top row via a chain of neighboring (left, right, up, down) open sites. We say the system percolates if there is a full site in the bottom row. In other words, a system percolates if we fill all open sites connected to the top row and that process fills some open site on the bottom row. (For the insulating/metallic materials example, the open sites correspond to metallic materials, so that a system that percolates has a metallic path from top to bottom, with full sites conducting. For the porous substance example, the open sites correspond to empty space through which water might flow, so that a system that percolates lets water fill open sites, flowing from top to bottom.)

## The problem

> In a famous scientific problem, researchers are interested in the following question: if sites are independently set to be open with probability p (and therefore blocked with probability 1 − p), what is the probability that the system percolates? When p equals 0, the system does not percolate; when p equals 1, the system percolates.
>
> When n is sufficiently large, there is a threshold value p* such that when p < p* a random n-by-n grid almost never percolates, and when p > p*, a random n-by-n grid almost always percolates. No mathematical solution for determining the percolation threshold p* has yet been derived. Your task is to write a computer program to estimate p*.

# Solution

The Union-Find algorithms presented in the [coursework](https://www.coursera.org/learn/algorithms-part1) form the foundation to implement a percolation system that is then used to estimate the value of the *percolation threshold* via Monte Carlo simulation.

## Percolation System

The `UnionFind` base class is the foundation of multiple variants of the algorithm: `QuickUF`, `OpenUF<QuickUF>`, `WeightedUF`, `OpenUF<WeightedUF>`. Suporting the implementation of multiple variants allows for greater comparison and analysis of the Union-Find algorithms. The `OpenUF` variants form the underlying mechanism of the percolation system.

The `Percolation` class models a percolation system. Given a value $`n`$, a class object instantiates an $`n`$-by-$`n`$ grid, implemented as an `OpenUF` variant, with all sites initially blocked. Each site within the grid is uniquely identified by a row/column index pair, where an index is an integer between 1 and $`n`$. A method is provided to open a given site, and accessors are provided to determine if any given site is open or full. A method is provided to determine if the system percolates or not.

The `Percolation` class constructor takes time proportional to $`n^2`$. However, all methods take constant time plus a constant number of calls to the underlying `UnionFind` algorithm.

## Monte Carlo Simulation

The `PercolationStats` class performs the following Monte Carlo simulation to estimate the percolation threshold.

- Initialize an $`n`$ x $`n`$ `Percolation` system with all sites blocked.
- Repeat the following until the system percolates.
    - Choose a site uniformly at random among all the blocked sites.
    - Open the site.
- Estimate the *percolation threshold* based on the fraction of sites that are opened when the system percolates.

The above algorithm is repeated a given number of times to produce a final set of statistics (mean, standard deviation, and 95% confidence interval) for the *percolation threshold*.

# Building/Running the Code

- Clone the repository with ```git clone https://github.com/christine-jones/dsa-excercises.git```.
- Move to the directory ```dsa-exercises/Algorithms-Part1/Percolation``` and issue the command ```make```. If you wish to use a different compiler, then edit the given ```Makefile``` or import the source files into your favorite IDE.
- Issue the command ```make tests``` to build the test executable, ```percolate-test```.
- Issue the command ```make clean``` to remove all generated build files and the client/test executables.
- To run the client program: ```./percolate <n> <T>```
  ```
   Usage: ./percolate <n> <T>
       n = grid size, n-by-n grid
       T = # independent computational experiments
  ```

# TBD: Future Work

- Update `PercolationStats` class to enable the variant of the underlying UnionFind algorithm to be configurable. Currently, the variant is hardcoded to `WeightedUF`. Allowing the specific algorithm variant to be configurable would provide greater flexibility in running experiments and comparison of Union Find algorithms.

