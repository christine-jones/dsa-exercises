# Collinear Points

C++ implementation of the programming exercise in **Module 6, Mergesort** of the [Princeton University's Algorithms, Part 1](https://www.coursera.org/learn/algorithms-part1) course on [coursera](https://www.coursera.org/).

# Problem Statement

This [specification](https://coursera.cs.princeton.edu/algs4/assignments/collinear/specification.php) describes the programming assignment and requirements. A brief description is excerpted here.

> Given a set of n distinct points in the plane, find every (maximal) line segment that connects a subset of 4 or more of the points.

## Brute Force

> Write a program BruteCollinearPoints.java that examines 4 points at a time and checks whether they all lie on the same line segment, returning all such line segments. To check whether the 4 points p, q, r, and s are collinear, check whether the three slopes between p and q, between p and r, and between p and s are all equal.

```
public class BruteCollinearPoints {
   public BruteCollinearPoints(Point[] points)    // finds all line segments containing 4 points
   public           int numberOfSegments()        // the number of line segments
   public LineSegment[] segments()                // the line segments
}
```
> The method segments() should include each line segment containing 4 points exactly once. If 4 points appear on a line segment in the order p→q→r→s, then you should include either the line segment p→s or s→p (but not both) and you should not include subsegments such as p→r or q→r. For simplicity, we will not supply any input to BruteCollinearPoints that has 5 or more collinear points.

> The order of growth of the running time of your program should be n4 in the worst case and it should use space proportional to n plus the number of line segments returned.

## Fast, Sorting-Based Solution

> Remarkably, it is possible to solve the problem much faster than the brute-force solution described above. Given a point p, the following method determines whether p participates in a set of 4 or more collinear points.
> * Think of p as the origin.
> * For each other point q, determine the slope it makes with p.
> * Sort the points according to the slopes they makes with p.
> * Check if any 3 (or more) adjacent points in the sorted order have equal slopes with respect to p. If so, these points, together with p, are collinear.
>
> Applying this method for each of the n points in turn yields an efficient algorithm to the problem. The algorithm solves the problem because points that have equal slopes with respect to p are collinear, and sorting brings such points together. The algorithm is fast because the bottleneck operation is sorting.
>
> Write a program FastCollinearPoints.java that implements this algorithm.

```
public class FastCollinearPoints {
   public FastCollinearPoints(Point[] points)     // finds all line segments containing 4 or more points
   public           int numberOfSegments()        // the number of line segments
   public LineSegment[] segments()                // the line segments
}
```
> The method segments() should include each maximal line segment containing 4 (or more) points exactly once. For example, if 5 points appear on a line segment in the order p→q→r→s→t, then do not include the subsegments p→s or q→t.

> The order of growth of the running time of your program should be n2 log n in the worst case and it should use space proportional to n plus the number of line segments returned. FastCollinearPoints should work properly even if the input has 5 or more collinear points.

## Client Program

> The client program takes the name of an input file as a command-line argument; reads the input file (in the format specified below); prints to standard output the line segments that your program discovers, one per line; and draws to standard draw the line segments.

> We supply several sample input files (suitable for use with the test client above) in the following format: An integer n, followed by n pairs of integers (x, y), each between 0 and 32,767. Below are two examples.

```
% cat input6.txt        % cat input8.txt
6                       8
19000  10000             10000      0
18000  10000                 0  10000
32000  10000              3000   7000
21000  10000              7000   3000
 1234   5678             20000  21000
14000  10000              3000   4000
                         14000  15000
                          6000   7000
```

# Solution

The base class ```CollinearPoints``` defines the common interface used by both the ```BruteCollinearPoints``` and ```FastCollinearPoints``` algorithm class implementations.

For simplicity, the ```BruteCollinearPoints``` algorithm does not consider line segments greater than four points in length. Depending on the input data, multiple overlapping line segments may be identified. The purpose of the ```BruteCollinearPoints``` algorithm is for performance comparison against the more sophisticated ```FastCollinearPoints``` algorithm. As such, time and effort were not taken to better optimize this algorithm.

A challenge with the ```FastCollinearPoints``` algorithm implementation is to *not* report duplicate line segments. This is handled in the sorting and comparison mechanism. The method for comparing points by slope with respect to a base point first orders the points by calculated slope, but in the case of points with equal slope, then needs to compare by normal point comparison operators. As a result, the slope comparator satisfies the requirements for *total order*, and a sort using the comparator produces points grouped by slope in ascending order. To prevent duplicate line segments, a line segment should only be reported in the case that the base point is the least in the line segment.

The client program runs input data through both the ```BruteCollinearPoints``` and ```FastCollinearPoints``` algorithms. Elapsed time is reported for each algorithm for the purposes of performance comparison.

# Building/Running the Code

- Clone the repository with ```git clone https://github.com/christine-jones/dsa-excercises.git```.
- Move to the directory ```dsa-exercises/Algorithms-Part1/Collinear``` and issue the command ```make```. If you wish to use a different compiler, then edit the given ```Makefile``` or import the source files into your favorite IDE.
- Issue the command ```make tests``` to build the test executable, ```collinear-test```.
- Issue the command ```make clean``` to remove all generated build files and the client/test executables.
- To run the client program: ```./collinear input-file```
  ```
  Usage: ./collinear <input_file>
        input_file = file that contains input data
  ```
