# KDTrees

C++ implementation of the programming exercise in **Module 11, Geometric Applications of BSTs** of the [Princeton University's Algorithms, Part 1](https://www.coursera.org/learn/algorithms-part1) course on [coursera](https://www.coursera.org/).

# Problem Statement

This [specification](https://coursera.cs.princeton.edu/algs4/assignments/kdtree/specification.php) describes the programming assignment and requirements. A brief description is excerpted here.

> Write a data type to represent a set of points in the unit square (all points have x- and y-coordinates between 0 and 1) using a 2d-tree to support efficient range search (find all of the points contained in a query rectangle) and nearest-neighbor search (find a closest point to a query point).

## Point2D

> The immutable data type Point2D represents points in the plane. Here is the subset of its API that you may use:
```
public class Point2D implements Comparable<Point2D> {
   public Point2D(double x, double y)              // construct the point (x, y)
   public  double x()                              // x-coordinate 
   public  double y()                              // y-coordinate 
   public  double distanceTo(Point2D that)         // Euclidean distance between two points 
   public  double distanceSquaredTo(Point2D that)  // square of Euclidean distance between two points 
   public     int compareTo(Point2D that)          // for use in an ordered symbol table 
   public boolean equals(Object that)              // does this point equal that object? 
   public    void draw()                           // draw to standard draw 
   public  String toString()                       // string representation 
}
```

## Rectangle

> The immutable data type RectHV (part of algs4.jar) represents axis-aligned rectangles. Here is the subset of its API that you may use:
```
public class RectHV {
   public    RectHV(double xmin, double ymin,      // construct the rectangle [xmin, xmax] x [ymin, ymax] 
                    double xmax, double ymax)      // throw an IllegalArgumentException if (xmin > xmax) or (ymin > ymax)
   public  double xmin()                           // minimum x-coordinate of rectangle 
   public  double ymin()                           // minimum y-coordinate of rectangle 
   public  double xmax()                           // maximum x-coordinate of rectangle 
   public  double ymax()                           // maximum y-coordinate of rectangle 
   public boolean contains(Point2D p)              // does this rectangle contain the point p (either inside or on boundary)? 
   public boolean intersects(RectHV that)          // does this rectangle intersect that rectangle (at one or more points)? 
   public  double distanceTo(Point2D p)            // Euclidean distance from point p to closest point in rectangle 
   public  double distanceSquaredTo(Point2D p)     // square of Euclidean distance from point p to closest point in rectangle 
   public boolean equals(Object that)              // does this rectangle equal that object? 
   public    void draw()                           // draw to standard draw 
   public  String toString()                       // string representation 
}
```

## Brute-force Implementation

> Write a mutable data type PointSET that represents a set of points in the unit square. Implement the following API by using a red–black BST:
```
public class PointSET {
   public         PointSET()                               // construct an empty set of points 
   public           boolean isEmpty()                      // is the set empty? 
   public               int size()                         // number of points in the set 
   public              void insert(Point2D p)              // add the point to the set (if it is not already in the set)
   public           boolean contains(Point2D p)            // does the set contain point p? 
   public              void draw()                         // draw all points to standard draw 
   public Iterable<Point2D> range(RectHV rect)             // all points that are inside the rectangle (or on the boundary) 
   public           Point2D nearest(Point2D p)             // a nearest neighbor in the set to point p; null if the set is empty 

   public static void main(String[] args)                  // unit testing of the methods (optional) 
}
```

> Do not implement your own red–black BST.

> Your implementation should support insert() and contains() in time proportional to the logarithm of the number of points in the set in the worst case; it should support nearest() and range() in time proportional to the number of points in the set.

## 2d-tree Implementation

> Write a mutable data type KdTree that uses a 2d-tree to implement the same API (but replace PointSET with KdTree). A 2d-tree is a generalization of a BST to two-dimensional keys. The idea is to build a BST with points in the nodes, using the x- and y-coordinates of the points as keys in strictly alternating sequence.
> 
> *Search and insert*. The algorithms for search and insert are similar to those for BSTs, but at the root we use the x-coordinate (if the point to be inserted has a smaller x-coordinate than the point at the root, go left; otherwise go right); then at the next level, we use the y-coordinate (if the point to be inserted has a smaller y-coordinate than the point in the node, go left; otherwise go right); then at the next level the x-coordinate, and so forth.

> The prime advantage of a 2d-tree over a BST is that it supports efficient implementation of range search and nearest-neighbor search. Each node corresponds to an axis-aligned rectangle in the unit square, which encloses all of the points in its subtree. The root corresponds to the unit square; the left and right children of the root corresponds to the two rectangles split by the x-coordinate of the point at the root; and so forth.
>
> *Range search*. To find all points contained in a given query rectangle, start at the root and recursively search for points in both subtrees using the following pruning rule: if the query rectangle does not intersect the rectangle corresponding to a node, there is no need to explore that node (or its subtrees). A subtree is searched only if it might contain a point contained in the query rectangle.
>
> *Nearest-neighbor search*. To find a closest point to a given query point, start at the root and recursively search in both subtrees using the following pruning rule: if the closest point discovered so far is closer than the distance between the query point and the rectangle corresponding to a node, there is no need to explore that node (or its subtrees). That is, search a node only only if it might contain a point that is closer than the best one found so far. The effectiveness of the pruning rule depends on quickly finding a nearby point. To do this, organize the recursive method so that when there are two possible subtrees to go down, you always choose the subtree that is on the same side of the splitting line as the query point as the first subtree to explore—the closest point found while exploring the first subtree may enable pruning of the second subtree.

# Solution

The ```Point2D``` and ```Rectangle``` classes meet the API requirements as stated in the problem statement above.

The ```PointSET``` class implements the brute-force implementation requirements as detailed in the problem statement. A std::set from the C++ STL was used as the underlying data structure. Search, removal, and insertion operations of std::set have logarithmic complexity and are usually implemented as red-black trees.

The ```KDTree``` class implements a 2d-tree data structure with an API as detailed in the problem statement above. 

# Building/Running the Code

- Clone the repository with ```git clone https://github.com/christine-jones/dsa-excercises.git```.
- Move to the directory ```dsa-exercises/Algorithms-Part1/KDTrees``` and issue the command ```make```. If you wish to use a different compiler, then edit the given ```Makefile``` or import the source files into your favorite IDE.
- Issue the command ```make tests``` to build the test executable, ```kdtree-test```.
- Issue the command ```make clean``` to remove all generated build files and the client/test executables.
- To run the client program: ```./kdtree <input-file>```
  ```
  Usage: ./kdtree <input-file>
       input_file = file that contains list of points
  ```
