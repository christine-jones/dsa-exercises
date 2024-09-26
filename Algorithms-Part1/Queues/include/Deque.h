/**
 * \file    Deque.h
 * \author  Christine Jones 
 * \brief   Definition of class that implements a deque data structure.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef DEQUE_H
#define DEQUE_H

#include "Node.h"
#include <cassert>
#include <cstddef>      // for std::ptrdiff_t
#include <exception>
#include <iostream>
#include <iterator>

template <typename T>
class Deque {

public:

    template <typename U>
    class iter {
    public:

        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = U;
        using pointer           = U*;
        using reference         = U&;

        iter(): m_ptr(nullptr) {}
        iter(Node<T>* ptr): m_ptr(ptr) {}

        reference operator*() const { return m_ptr->item(); }
        pointer operator->() const  { return m_ptr->itemPtr(); }

        iter& operator++() { m_ptr = m_ptr->next(); return *this; }
        iter operator++(int) { iter tmp = *this; ++(*this); return tmp;}

        friend bool operator==(const iter& a, const iter& b) {
            return a.m_ptr == b.m_ptr;
        }
        friend bool operator!=(const iter& a, const iter& b) {
            return a.m_ptr != b.m_ptr;
        }

    private:

        Node<T>* m_ptr{nullptr};
    };
    typedef iter<T>       iterator;
    typedef iter<const T> const_iterator;

    Deque():
        m_first{nullptr},
        m_last{nullptr},
        m_size{0}
    {}

    ~Deque() {

        clear();
    }

    bool isEmpty() const { return m_size == 0; }
    int  size() const    { return m_size; }

    void addFirst(const T& item);
    void addLast(const T& item);

    T removeFirst();
    T removeLast();

    void clear();

    iterator begin() { return iterator(m_first); }
    iterator end()   { return iterator(nullptr); }

    const_iterator begin() const  { return const_iterator{m_first}; }
    const_iterator cbegin() const { return const_iterator{m_first}; }
    const_iterator end() const    { return const_iterator{nullptr}; }
    const_iterator cend() const   { return const_iterator{nullptr}; }

    // copying, assigning, moving a deque is not currently supported
    Deque(const Deque& deque) = delete;
    Deque(Deque& deque) = delete;
    Deque& operator= (const Deque& deque) = delete;
    Deque& operator= (Deque& deque) = delete;

private:

    Node<T>* m_first{nullptr};
    Node<T>* m_last{nullptr};
    int      m_size{0};

};

template <typename T>
void Deque<T>::addFirst(const T& item) {

    Node<T>* new_node{nullptr};

    try {

        new_node = new Node<T>(item, m_first, nullptr);

    } catch (const std::bad_alloc& e) {

        std::cerr << "Deque::addFirst: " << e.what() << '\n';
        throw;
    }

    if (m_size > 0) {

        assert(m_first != nullptr);
        m_first->setPrev(new_node);

    } else  { // m_size == 0, very first node in queue

        assert(m_last == nullptr);
        m_last = new_node;
    }

    m_first = new_node;
    ++m_size;
}

template <typename T>
void Deque<T>::addLast(const T& item) {

    Node<T>* new_node{nullptr};

    try {

        new_node = new Node<T>(item, nullptr, m_last);

    } catch (const std::bad_alloc& e) {

        std::cerr << "Deque::addLast: " << e.what() << '\n';
        throw;
    }

    if (m_size > 0) {

        assert(m_last != nullptr);
        m_last->setNext(new_node);

    } else { // m_size == 0, very first node in queue

        assert(m_first == nullptr);
        m_first = new_node;
    }

    m_last = new_node;
    ++m_size;
}

template <typename T>
T Deque<T>::removeFirst() {
 
    if (m_size == 0) {

        std::cerr << "Deque::removeFirst: deque is empty" << '\n';
        throw std::out_of_range("deque empty, no such element");
    }

    assert(m_first != nullptr && m_last != nullptr);

    Node<T>* old_node{m_first};

    m_first = old_node->next();
    --m_size;

    if (m_size > 0) {

        assert(m_first != nullptr);
        m_first->setPrev(nullptr);

    } else { // m_size == 0, no nodes remain in queue

        assert(m_first == nullptr);
        m_last = nullptr;
    }

    T item = old_node->item();
    delete old_node;

    return item;
}

template <typename T>
T Deque<T>::removeLast() {

    if (m_size == 0) {

        std::cerr << "Deque::removeLast: deque is empty" << '\n';
        throw std::out_of_range("deque empty, no such element");
    }

    assert(m_first != nullptr && m_last != nullptr);

    Node<T>* old_node{m_last};

    m_last = old_node->prev();
    --m_size;

    if (m_size > 0) {

        assert(m_last != nullptr);
        m_last->setNext(nullptr);

    } else { // m_size == 0, no nodes remain in queue

        assert(m_last == nullptr);
        m_first = nullptr;
    }

    T item = old_node->item();
    delete old_node;

    return item;
}

template <typename T>
void Deque<T>::clear() {

    while (m_first != nullptr) {

        Node<T>* node{m_first};
        m_first = node->next();
        delete node;
    }

    m_last = nullptr;
    m_size = 0;
}

#endif // DEQUE_H
