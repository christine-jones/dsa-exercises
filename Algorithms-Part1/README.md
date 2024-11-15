# Algorithms-Part1

C++ implementation of the data structures and algorithms taught in [Princeton University's Algorithms, Part 1](https://www.coursera.org/learn/algorithms-part1) course found on [coursera](https://www.coursera.org/).

## Why C++?

The [Algorithms, Part 1](https://www.coursera.org/learn/algorithms-part1) course uses the Java programming language to teach and analyze data structures and algorithms. All programming assignments are expected to be coded in Java as well. My exposure to the Java programming language, however, is not extenstive. I really want to focus on the DSA content and not my coding skills, or lack thereof. Thus my use of C++.

The bulk of my coding experience has centered around C/C++, and it is definitely my language of strength. Using C++ for the programming exercises allows me to fully focus on the performance, intracacies, and analysis of the data structures and algorithms specifically, rather than the learning and mastering of a particular coding language.

In the event that I decide to really learn and strengthen my Java coding skills, reimplementing these programming exercises in Java would be a good task.

## Focus and Intent

The priority, for me, of these programming exercises is personal education and improvement with respect to the DSA content specifically. Therefore, this code lacks features and robustness that deployed software would certainly include.

Errors are largely handled via assertion. At this time, I am the sole creator and user of this code, and in addition, the code is small in scale and not too complex. Assertions allow me to quickly identify and fix issues. More robust error and exception handling and some form of logging would be necessary if this code widens in scope and developers/users.

There is no automated test infrastructure. Again, this deficiency would need to be addressed if the scope of this code expands beyond my personal usage. 

## Content

- HelloWorld/
  
  Just making sure we got the basics covered!

- Percolation/
  
  Program that estimates the value of the *percolation threshold* via Monnte Carlo simulation.

- Queues/
  
  Generic data types for deque and randomized queue using linked list and array, respectively.

- Collinear/
  
  Program that recognizes line patterns in a given set of points.

- SliderPuzzle/

  Program that solves a generalized $`n`$-by-$`n`$ slider puzzle using an A* search algorithm.

- KDTree/

  Program that stores points in a unit square using a 2d-tree to support efficient range and nearest neighbor searches.
