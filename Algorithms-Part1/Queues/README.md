# Queues

C++ implementation of the programming exercise in **Module 4, Stacks and Queues** of the [Princeton University's Algorithms, Part 1](https://www.coursera.org/learn/algorithms-part1) course on [coursera](https://www.coursera.org/).

# Problem Statement

This [specification](https://coursera.cs.princeton.edu/algs4/assignments/queues/specification.php) describes the programming assignment and requirements. A brief description is excerpted here.

> Write a generic data type for a deque and a randomized queue. The goal of this assignment is to implement elementary data structures using arrays and linked lists, and to introduce you to generics and iterators.

## Deque

>  A double-ended queue or deque (pronounced “deck”) is a generalization of a stack and a queue that supports adding and removing items from either the front or the back of the data structure. Create a generic data type Deque that implements the following API:

```
public class Deque<Item> implements Iterable<Item> {

    // construct an empty deque
    public Deque()

    // is the deque empty?
    public boolean isEmpty()

    // return the number of items on the deque
    public int size()

    // add the item to the front
    public void addFirst(Item item)

    // add the item to the back
    public void addLast(Item item)

    // remove and return the item from the front
    public Item removeFirst()

    // remove and return the item from the back
    public Item removeLast()

    // return an iterator over items in order from front to back
    public Iterator<Item> iterator()

    // unit testing (required)
    public static void main(String[] args)

}
```

> Your deque implementation must support each deque operation (including construction) in constant worst-case time. A deque containing n items must use at most 48n + 192 bytes of memory. Additionally, your iterator implementation must support each operation (including construction) in constant worst-case time.

## Randomized Queue

> A randomized queue is similar to a stack or queue, except that the item removed is chosen uniformly at random among items in the data structure. Create a generic data type RandomizedQueue that implements the following API:

```
public class RandomizedQueue<Item> implements Iterable<Item> {

    // construct an empty randomized queue
    public RandomizedQueue()

    // is the randomized queue empty?
    public boolean isEmpty()

    // return the number of items on the randomized queue
    public int size()

    // add the item
    public void enqueue(Item item)

    // remove and return a random item
    public Item dequeue()

    // return a random item (but do not remove it)
    public Item sample()

    // return an independent iterator over items in random order
    public Iterator<Item> iterator()

    // unit testing (required)
    public static void main(String[] args)

}
```

> Your randomized queue implementation must support each randomized queue operation (besides creating an iterator) in constant amortized time. That is, any intermixed sequence of m randomized queue operations (starting from an empty queue) must take at most cm steps in the worst case, for some constant c. A randomized queue containing n items must use at most 48n + 192 bytes of memory. Additionally, your iterator implementation must support operations next() and hasNext() in constant worst-case time; and construction in linear time; you may (and will need to) use a linear amount of extra memory per iterator.

## Client

> Write a client program Permutation.java that takes an integer k as a command-line argument; reads a sequence of strings from standard input using StdIn.readString(); and prints exactly k of them, uniformly at random. Print each item from the sequence at most once.

> You may assume that 0 ≤ k ≤ n, where n is the number of string on standard input. Note that you are not given n.

> The running time of Permutation must be linear in the size of the input. You may use only a constant amount of memory plus either one Deque or RandomizedQueue object of maximum size at most n. (For an extra challenge and a small amount of extra credit, use only one Deque or RandomizedQueue object of maximum size at most k.)

# Solution

The `Deque` and `RandomQueue` classes implement the class definitions specified above. The underlying implementation of these classes do not utilize the STL, such as `std::vector`, `std::list`, etc. This allows for more low-level control of the algorithm logic in order to fully maximize the educational understanding intended by these exercises.

## Deque

The `Deque` class is implemented using a doubly linked list. It holds objects of templated type that must be CopyAssignable and CopyConstructible. A custom iterator is provided that allows for forward passes over a `Deque`.

## Randomized Queue

The `RandomQueue` class is implemented as a resizable C-style array. The array doubles in capacity when filled. Its capacity is halved when the array reduces to a quarter full.  

Objects are added and stored to the array in a uniformly random order. Thereofore, removing an object at random is simply met by returning the last object in the queue.

A custom iterator is provided that allows for a single pass over a `RandomQueue`. Each iterator instance returns the objects of the queue in uniformly random order. The order of two or more iterators to the same `RandomQueue` is mutually independent; each iterator maintains its own random order.

The `RandomQueue` class holds objects of templated type that must be CopyAssignable and CopyConstructible.

## Client Program

The `permutation` client program reads a sequence of $n$ strings from the standard input and prints to standard output exactly $k$, where $0 <= k <= n$, of those strings uniformly at random. Each string from the given sequence is printed at most once.

The number of strings, $n$, to be input is unkown ahead of time. However, a `RandomQueue` of only size $k$, rather than size $n$, is required to store the strings eventually printed to standard output. The first $k$ strings are simply added to the `RandomQueue`. For all subsequent strings, a uniformly random number between $0$ and the number of strings input thus far is generated. If that random number is less than $k$, the string is added to the `RandomQueue`, randomly replacing another string already in the `RandomQueue`. If the generated random number is greater or equal to $k$, then no actions are taken to store that string. This results in a uniformly random size $k$ subset of the $n$ input strings being output.

# Building/Running the Code

- Clone the repository with ```git clone https://github.com/christine-jones/dsa-excercises.git```.
- Move to the directory ```dsa-exercises/Algorithms-Part1/Queues``` and issue the command ```make```. If you wish to use a different compiler, then edit the given ```Makefile``` or import the source files into your favorite IDE.
- Issue the command ```make clean``` to remove all generated build files and the client executable.
- To run the client program: ```./permutation k```
  ```
  Usage: ./permutation <k>
       k = number of strings to print to standard output, where 0 <= k <= n,
           and n is the number of strings read from standard input
  ```
  
