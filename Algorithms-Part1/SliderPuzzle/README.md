# Slider Puzzle

C++ implementation of the programming exercise in **Module 8, Priority Queues** of the [Princeton University's Algorithms, Part 1](https://www.coursera.org/learn/algorithms-part1) course on [coursera](https://www.coursera.org/).

# Problem Statement

This [specification](https://coursera.cs.princeton.edu/algs4/assignments/8puzzle/specification.php) describes the programming assignment and requirements. A brief description is excerpted here.

> The 8-puzzle is a sliding puzzle that is played on a 3-by-3 grid with 8 square tiles labeled 1 through 8, plus a blank square. The goal is to rearrange the tiles so that they are in row-major order, using as few moves as possible. You are permitted to slide tiles either horizontally or vertically into the blank square.
>
> Write a program to solve the 8-puzzle problem (and its natural generalizations) using the A* search algorithm.

## Game Board

> To begin, create a data type that models an n-by-n board with sliding tiles. Implement an immutable data type Board with the following API:

```
public class Board {

    // create a board from an n-by-n array of tiles,
    // where tiles[row][col] = tile at (row, col)
    public Board(int[][] tiles)
                                           
    // string representation of this board
    public String toString()

    // board dimension n
    public int dimension()

    // number of tiles out of place
    public int hamming()

    // sum of Manhattan distances between tiles and goal
    public int manhattan()

    // is this board the goal board?
    public boolean isGoal()

    // does this board equal y?
    public boolean equals(Object y)

    // all neighboring boards
    public Iterable<Board> neighbors()

    // a board that is obtained by exchanging any pair of tiles
    public Board twin()

    // unit testing (not graded)
    public static void main(String[] args)

}
```

> You may assume that the constructor receives an n-by-n array containing the n^2 integers between 0 and n^2 − 1, where 0 represents the blank square. You may also assume that 2 ≤ n < 128.

> To measure how close a board is to the goal board, we define two notions of distance. The Hamming distance betweeen a board and the goal board is the number of tiles in the wrong position. The Manhattan distance between a board and the goal board is the sum of the Manhattan distances (sum of the vertical and horizontal distance) from the tiles to their goal positions.

> Two boards are equal if they are have the same size and their corresponding tiles are in the same positions.

> The neighbors() method returns an iterable containing the neighbors of the board. Depending on the location of the blank square, a board can have 2, 3, or 4 neighbors.

> Your implementation should support all Board methods in time proportional to n2 (or better) in the worst case.

## A* Search Algorithm
> Now, we describe a solution to the 8-puzzle problem that illustrates a general artificial intelligence methodology known as the A* search algorithm. We define a search node of the game to be a board, the number of moves made to reach the board, and the previous search node. First, insert the initial search node (the initial board, 0 moves, and a null previous search node) into a priority queue. Then, delete from the priority queue the search node with the minimum priority, and insert onto the priority queue all neighboring search nodes (those that can be reached in one move from the dequeued search node). Repeat this procedure until the search node dequeued corresponds to the goal board.
>
> The efficacy of this approach hinges on the choice of priority function for a search node. We consider two priority functions:
>
> The Hamming priority function is the Hamming distance of a board plus the number of moves made so far to get to the search node. Intuitively, a search node with a small number of tiles in the wrong position is close to the goal, and we prefer a search node if has been reached using a small number of moves.
>
> The Manhattan priority function is the Manhattan distance of a board plus the number of moves made so far to get to the search node.
>
> To solve the puzzle from a given search node on the priority queue, the total number of moves we need to make (including those already made) is at least its priority, using either the Hamming or Manhattan priority function. Why? Consequently, when the goal board is dequeued, we have discovered not only a sequence of moves from the initial board to the goal board, but one that makes the fewest moves.
>
> One way to view the computation is as a game tree, where each search node is a node in the game tree and the children of a node correspond to its neighboring search nodes. The root of the game tree is the initial search node; the internal nodes have already been processed; the leaf nodes are maintained in a priority queue; at each step, the A* algorithm removes the node with the smallest priority from the priority queue and processes it (by adding its children to both the game tree and the priority queue).

> Create an immutable data type Solver with the following API:

```
public class Solver {

    // find a solution to the initial board (using the A* algorithm)
    public Solver(Board initial)

    // is the initial board solvable? (see below)
    public boolean isSolvable()

    // min number of moves to solve initial board; -1 if unsolvable
    public int moves()

    // sequence of boards in a shortest solution; null if unsolvable
    public Iterable<Board> solution()

    // test client (see below) 
    public static void main(String[] args)

}
```

## Client Program

> The test client takes the name of an input file as a command-line argument and prints the minimum number of moves to solve the puzzle and a corresponding solution.

>  The input file contains the board size n, followed by the n-by-n grid of tiles, using 0 to designate the blank square.

```
~/Desktop/8puzzle> cat puzzle04.txt
3
 0  1  3
 4  2  5
 7  8  6

~/Desktop/8puzzle> java-algs4 Solver puzzle04.txt
Minimum number of moves = 4

3
 0  1  3 
 4  2  5 
 7  8  6 

3
 1  0  3 
 4  2  5 
 7  8  6 

3
 1  2  3 
 4  0  5 
 7  8  6 

3
 1  2  3 
 4  5  0   
 7  8  6 

3
 1  2  3 
 4  5  6 
 7  8  0
```

# Solution

The ```Board``` class represents a generalized $`n`$-by-$`n`$ slider puzzle game board. It is an $`n`$-by-$`n`$ grid with $`n^2 - 1`$ tiles labeled $`1`$ through $`n^2 - 1`$, plus a blank tile. A blank tile is represented by zero ($`0`$). A ```Board``` is solved if the tiles are arranged in row-major order with the blank tile in the borrom right corner.

The ```BoardSolver``` class implements the search algorithm to solve a given $`n`$-by-$`n`$ slider game board. The initial game ```Board``` used to instantiate the ```BoardSolver``` forms the root node of a ```GameTree```. The ```GameTree``` class initializes its root node with a number of moves of 0. Neighboring boards (i.e., those that can be reached in one move, swapping the blank tile with an adjacent tile) become child nodes of the root node with number of moves set to 1. The game tree continues to be constructed in a similar manner with subsequent neighboring game boards becoming child nodes within the game tree and move count incremented by 1. Eventually, if the game board is solvable, one of the leaf nodes is the solved board, and walking back up the path of the tree from leaf to root provides the sequence of game boards that forms the solution.

To determine the shortest solution to the given game board, the ```BoardSolver``` class utilizes a priority queue. The initial board (which forms the root of the game tree) is inserted into the priority queue. For each iteration of the algorithm, the game board with the minimum priority is removed from the priority queue (which is the initial game board in the first round of the algorithm). All neighobring game boards, except the one that matches the previous board, are then inserted into the priority queue. This process is repeated until the game board removed from the priority queue is the solved game board.

The choice of priority function for determining the minimum priority game board within the priority queue is crucial for the effectiveness of the algorithm. Two priority functions are provided.

- Hamming:

  The Hamming Distance of the game board plus the number of moves made thus far to get to the game board. The Hamming Distance of a game board is the number of tiles in the wrong position with respect to the solved board.
  
- Manhattan:

    The Manhattan Distance of the game board plus the number of moves made thus far to get to the game board. The Manhattan Distance of a game board is the sum of the vertical and horizontal distances of each tile to their solved position. 

Not all game boards are solvable. However, boards are divided into two equivalence classes with respect to solvability. (1) Those that are solvable, and (2) those that can be solved if the board is modified by swapping any pair of tiles, not including the blank tile.

This fact is used to prevent the algorithm from boundlessly running to determine a solution for an unsolvable game board. The A* algorithm described above is actually run on two game boards simultaneously, one with the initial game board and one with the initial game board modified by swapping a pair of tiles. The algorithm is run in lockstep with both boards. Exactly one of the two game boards leads to the solved board.

# Building/Running the Code

- Clone the repository with ```git clone https://github.com/christine-jones/dsa-excercises.git```.
- Move to the directory ```dsa-exercises/Algorithms-Part1/SliderPuzzle``` and issue the command ```make```. If you wish to use a different compiler, then edit the given ```Makefile``` or import the source files into your favorite IDE.
- Issue the command ```make clean``` to remove all generated build files and the client executable.
- To run the client program: ```./solver input-file```
  ```
  Usage: <program name> <input_file>
        input_file = file that contains n-by-n slider puzzle
  ```

# TBD: Optimization

This implementation struggles to solve lareger and/or complex game boards. Optimizations with regard to memory usage would be helpful.
