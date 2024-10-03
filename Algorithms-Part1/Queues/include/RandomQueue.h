/**
 * \file    Deque.h
 * \author  Christine Jones 
 * \brief   Definition of class that implements a randomized queue.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

// XXX 1. Basic queue structure
// XXX 2. Enqueue, increase capacity
// XXX 3. Dequeue, decrease capacity
// XXX 4. Sample
// XXX 5. Iterators

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

template <typename T>
class RandomQueue {

public:

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

        iter(const T* array, int size):
            m_array{array},
            m_index{size - 1},
            m_indices{std::vector<int>(static_cast<std::size_t>(size))}
        {
            std::iota(m_indices.begin(), m_indices.end(), 0);
            randomize();
        }

        static iter end() { return iter{}; }

        reference operator*() const { 
            return m_array[m_indices[static_cast<std::size_t>(m_index)]]; 
        }
        pointer operator->() const  { 
            return &m_array[m_indices[static_cast<std::size_t>(m_index)]]; 
        }

        iter& operator++() { --m_index; return *this; }

        friend bool operator==(const iter& a, const iter& b) {
            return a.m_index == b.m_index;
        }
        friend bool operator!=(const iter& a, const iter& b) {
            return a.m_index != b.m_index;
        }

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

        const T*  m_array{nullptr};
        int m_index{-1};
        std::vector<int> m_indices{};
    };
    typedef iter const_iterator;

    RandomQueue();
    ~RandomQueue();

    bool isEmpty() const  { return m_size == 0; }
    int  size() const     { return m_size; }
    int  capacity() const { return m_capacity; }

    void enqueue(const T& item);
    T    dequeue();

    const T& sample() const;

    void clear();

    const_iterator begin() const  { return const_iterator{m_queue, m_size}; }
    const_iterator cbegin() const { return const_iterator{m_queue, m_size}; }
    const_iterator end() const    { return const_iterator::end(); }
    const_iterator cend() const   { return const_iterator::end(); }

    // copying, assigning, moving a random queue is not currently supported
    RandomQueue(const RandomQueue& queue) = delete;
    RandomQueue(RandomQueue& queue) = delete;
    RandomQueue& operator= (const RandomQueue& queue) = delete;
    RandomQueue& operator= (RandomQueue& queue) = delete;

private:

    static constexpr int s_initial_capacity{2};
    static constexpr int s_resize_rate{2}; // double/halve capacity
    static constexpr int s_shrink_ratio{4}; // shrink at 1/4 capacity

    bool needToGrow() const
        { return m_size == m_capacity; }
    bool needToShrink() const
        { return (m_capacity > s_initial_capacity) && 
                 (m_size == (m_capacity / s_shrink_ratio)); }

    void initQueue();
    void deleteQueue();

    void growQueue();
    void shrinkQueue();
    void resizeQueue(int new_capacity);

    T*  m_queue{nullptr};
    int m_size{0};
    int m_capacity{0};

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

    if (needToGrow())
        try { 
            growQueue();

        } catch (const std::bad_alloc& e) { throw; }

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

    T item{m_queue[m_size - 1]};

    m_queue[m_size - 1] = T{};
    --m_size;

    if (needToShrink())
        try {
            shrinkQueue();

        } catch (const std::bad_alloc& e) { throw; }

    return item;
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

    for (int i{0}; i < m_size; ++i)
        new_queue[i] = m_queue[i];

    delete m_queue;
    m_queue = new_queue;
    m_capacity = new_capacity;
}

#endif // RANDOM_QUEUE_H
