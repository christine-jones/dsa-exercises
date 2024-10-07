/**
 * \file    RandomQueue.h
 * \author  Christine Jones 
 * \brief   Definition of class that implements a randomized queue.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef RANDOM_QUEUE_H
#define RANDOM_QUEUE_H

#include "Random.h"
#include <algorithm>    // for std::swap
#include <cassert>
#include <cstddef>      // for std::ptrdiff_t
#include <exception>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

/**
 * Class that implements a randomized queue data structure. A randomized queue
 * is similar to a standard queue except that objects removed are chosen
 * uniformly at random among all the objects in the queue.
 * 
 * This randomized queue is implemented as a resizable array. The array doubles
 * in capacity when filled. Its capacity is havled when the array reduces to a 
 * quarter full. Each randomized queue operation (besides creating an iterator)
 * is performed in constant amortized time.
 * 
 * Objects are added and stored to the array in a uniformly random order.
 * Therefore, removing an object at random is simply met by returning the
 * last object on the queue.
 * 
 * This randomized queue holds objects of a templated type. The templated type
 * must be CopyAssignable and CopyConstructible.
 */
template <typename T>
class RandomQueue {

public:

    /**
     * Custom iterator that allows for a single pass over the queue. Each
     * iterator instance returns the elements of the queue in uniformly random
     * order. The order of two or more iterators to the same randomized queue
     * are mutually independent; each iterator maintains its own random order.
     */
    class iter {
    public:

        using iterator_category = std::input_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = const T;
        using pointer           = const T*;
        using reference         = const T&;

        iter():
            m_array{nullptr},
            m_index{-1}
        {}

        iter(const T* array, int size, bool random = true):
            m_array{array},
            m_index{size - 1},
            m_indices{std::vector<int>(static_cast<std::size_t>(size))}
        {
            std::iota(m_indices.begin(), m_indices.end(), 0);
            if (random)
                randomize();
        }

        static iter end() { return iter{}; }

        reference operator*() const
            { return m_array[m_indices[static_cast<std::size_t>(m_index)]]; }
        pointer operator->() const
            { return &m_array[m_indices[static_cast<std::size_t>(m_index)]]; }

        iter& operator++() { --m_index; return *this; }

        friend bool operator==(const iter& a, const iter& b) 
            { return a.m_index == b.m_index; }
        friend bool operator!=(const iter& a, const iter& b)
            { return a.m_index != b.m_index;    }

        ~iter() = default;
        iter(const iter& iter) = default;
        iter& operator= (const iter& iter) = default;

    private:

        void randomize() {

            for (int i{0};
                 static_cast<std::size_t>(i) < m_indices.size();
                 ++i) {

                int r{Random::getRandomNumber(0, i)};
                std::swap(m_indices[static_cast<std::size_t>(r)],
                          m_indices[static_cast<std::size_t>(i)]);
            }
        }

        const T*         m_array{nullptr};
        int              m_index{-1};
        std::vector<int> m_indices{};
    };
    typedef iter const_iterator;

    /**
     * Constructor. Initializes an empty queue. An exception of type
     * std::bad_alloc is thrown in the case that memory fails to be allocated.
     */
    RandomQueue();

    /**
     * Destructor. Releases all memory allocted to the queue.
     */
    ~RandomQueue();

    /**
     * Determine if the queue is empty.
     * 
     * \return bool True if no objects in deque; False otherwise.
     */
    bool isEmpty() const { return m_size == 0; }

    /**
     * Returns the number of objects contained in the queue.
     * 
     * \return int Number of objects in queue.
     */
    int size() const { return m_size; }

    /**
     * Returns the current capacity of the queue. The capacity does grow and
     * shrink with the use of the queue. This accessor is made availble for
     * testing purposes.
     * 
     * \return int Total number of objects that are able to currently be stored
     *             in the queue.
     */
    int capacity() const { return m_capacity; }

    /**
     * Adds an object to the queue. An exception of type std::bad_alloc is
     * thrown in the case that memory fails to be allocated.
     *
     * \param T Object of templated type to be added to the queue.
     */
    void enqueue(const T& item);

    /**
     * Removes a random object from the queue. An exception of type
     * std::out_of_range is thrown in the case that the queue is empty.
     * 
     * \return T Object of templated type removed from queue.
     */
    T    dequeue();

    /**
     * Methods that return, but do not remove, a random object from the queue.
     * An exception of type std::out_of_range is thrown in the case that the
     * queue is empty.
     * 
     * \return T Random object of templated type from the queue.
     */
    T& sample();
    const T& sample() const;

    /**
     * Clears all items from the queue, releasing allocated memory.
     * Reinitializes to an empty queue. An exception of type
     * std::bad_alloc is thrown in the case that memory fails to be allocated.
     */
    void clear();

    // constant iterators that allow forward passes over the queue
    const_iterator begin() const  { return const_iterator{m_queue, m_size}; }
    const_iterator cbegin() const { return const_iterator{m_queue, m_size}; }
    const_iterator end() const    { return const_iterator::end(); }
    const_iterator cend() const   { return const_iterator::end(); }

    // for testing, iterators that pass queue as is rather than random order
    const_iterator tbegin() const
        { return const_iterator(m_queue, m_size, false); }
    const_iterator tend() const { return const_iterator::end(); }

    // copying, assigning, moving a random queue is not currently supported
    RandomQueue(const RandomQueue& queue) = delete;
    RandomQueue(RandomQueue& queue) = delete;
    RandomQueue& operator= (const RandomQueue& queue) = delete;
    RandomQueue& operator= (RandomQueue& queue) = delete;

private:

    static constexpr int s_initial_capacity{2};
    static constexpr int s_resize_rate{2};  // double/halve capacity
    static constexpr int s_shrink_ratio{4}; // shrink at 1/4 capacity

    // queue needs to grow when capacity is full
    bool needToGrow() const
        { return m_size == m_capacity; }

    // queue needs to shrink when reduced to quarter capacity
    bool needToShrink() const
        { return (m_capacity > s_initial_capacity) && 
                 (m_size == (m_capacity / s_shrink_ratio)); }

    // manage the queue capacity
    void growQueue();
    void shrinkQueue();
    void resizeQueue(int new_capacity);

    // initialize queue; allocate memory to initial capacity
    void initQueue();

    // release all memory allocated to queue
    void deleteQueue();

    T*  m_queue{nullptr};   // pointer to array that contains the queue
    int m_size{0};          // number of objects currently in the queue
    int m_capacity{0};      // number of objects allowed in the queue

};

template <typename T>
RandomQueue<T>::RandomQueue():
        m_queue{nullptr},
        m_size{0},
        m_capacity{0}
{
    try {
        initQueue();

    } catch (const std::bad_alloc& e) { throw; }
}

template <typename T>
RandomQueue<T>::~RandomQueue() {
    
    deleteQueue();
}

template <typename T>
void RandomQueue<T>::enqueue(const T& item) {

    if (needToGrow()) {
        try { 
            growQueue();

        } catch (const std::bad_alloc& e) { throw; }
    }

    // maintain uniform randomness within queue by adding new object to random
    // location within the queue
    int random_index = Random::getRandomNumber(0, m_size);

    m_queue[m_size] = m_queue[random_index];
    m_queue[random_index] = item;
    ++m_size;
}

template <typename T>
T RandomQueue<T>::dequeue() {

    if (m_size == 0) {

        std::cerr << "RandomQueue::dequeue: queue is empty" << '\n';
        throw std::out_of_range("queue empty, no such element");
    }

    // queue maintained in uniform random order so removing object from end of
    // queue results in random object being returned
    T item{m_queue[m_size - 1]};

    m_queue[m_size - 1] = T{};
    --m_size;

    if (needToShrink()) {
        try {
            shrinkQueue();

        } catch (const std::bad_alloc& e) { throw; }
    }

    return item;
}

template <typename T>
T& RandomQueue<T>::sample() {

    if (m_size == 0) {
    
        std::cerr << "RandomQueue::sample: queue is empty" << '\n';
        throw std::out_of_range("queue empty, no such element");
    }

    return m_queue[Random::getRandomNumber(0, m_size - 1)];
}

template <typename T>
const T& RandomQueue<T>::sample() const {

    if (m_size == 0) {
    
        std::cerr << "RandomQueue::sample: queue is empty" << '\n';
        throw std::out_of_range("queue empty, no such element");
    }

    return m_queue[Random::getRandomNumber(0, m_size - 1)];
}

template <typename T>
void RandomQueue<T>::clear() {

    deleteQueue();

    try {
        initQueue();

    } catch (const std::bad_alloc& e) { throw; }
}

template <typename T>
void RandomQueue<T>::initQueue() {

    assert(m_capacity == 0);

    try {

        m_queue = new T[s_initial_capacity]{};

    } catch (const std::bad_alloc& e) {

        std::cerr << "RandomQueue::initQueue: " << e.what() << '\n';
        throw;
    }

    m_size = 0;
    m_capacity = s_initial_capacity;
}

template <typename T>
void RandomQueue<T>::deleteQueue() {

    delete[] m_queue;
    m_queue = nullptr;
    m_size = 0;
    m_capacity = 0;
}

template <typename T>
void RandomQueue<T>::growQueue() {

    try {

        resizeQueue(s_resize_rate * m_capacity);

    } catch (const std::bad_alloc& e) { throw; }
}

template <typename T>
void RandomQueue<T>::shrinkQueue() {

    try {

        resizeQueue(m_capacity / s_resize_rate);

    } catch (const std::bad_alloc& e) { throw; }
}

template <typename T>
void RandomQueue<T>::resizeQueue(int new_capacity) {

    assert(m_size < new_capacity);

    T* new_queue{nullptr};

    try {

        new_queue = new T[new_capacity]{};

    } catch (const std::bad_alloc& e) {

        std::cerr << "RandomQueue::resizeQueue: " << e.what() << '\n';
        throw;
    }

    // copy old queue into newly allocated queue
    for (int i{0}; i < m_size; ++i)
        new_queue[i] = m_queue[i];

    // release all memory allocated to old queue
    delete[] m_queue;
    m_queue = new_queue;
    m_capacity = new_capacity;
}

#endif // RANDOM_QUEUE_H
