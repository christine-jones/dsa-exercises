/**
 * \file    Deque.h
 * \author  Christine Jones 
 * \brief   Definition of class that implements a randomized queue.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

// 1. Basic queue structure
// 2. Enqueue, increase capacity
// 3. Dequeue, decrease capacity
// 4. Sample
// 5. Iterators

#ifndef RANDOM_QUEUE_H
#define RANDOM_QUEUE_H

#include <cassert>

template <typename T>
class RandomQueue {

public:

    RandomQueue();
    ~RandomQueue();

    bool isEmpty() const { return m_size == 0; }
    int  size() const    { return m_size; }

    void enqueue(const T& item);
    T    dequeue();

    void clear();

    // random sample method

    // iterators

    // copying, assigning, moving a random queue is not currently supported
    RandomQueue(const RandomQueue& queue) = delete;
    RandomQueue(RandomQueue& queue) = delete;
    RandomQueue& operator= (const RandomQueue& queue) = delete;
    RandomQueue& operator= (RandomQueue& queue) = delete;

private:

    static constexpr int s_initial_capacity{1};

    void initQueue();
    void deleteQueue();

    void grow();
    void shrink();

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

}

template <typename T>
T RandomQueue<T>::dequeue() {

    return T{};
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
void RandomQueue<T>::grow() {


}

template <typename T>
void RandomQueue<T>::shrink() {

}

#endif // RANDOM_QUEUE_H
