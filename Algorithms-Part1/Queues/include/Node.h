/**
 * \file    Node.h
 * \author  Christine Jones 
 * \brief   Class that implements a linked list node.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {

public:

    explicit Node(const T& item):
        m_item{item},
        m_next{nullptr},
        m_prev{nullptr}
    {}

    Node(const T& item, const Node* next, const Node* prev):
        m_item{item},
        m_next{next},
        m_prev{prev}
    {}

    T item() const { return m_item; } 

    Node* next() const { return m_next; }
    Node* prev() const { return m_prev; }

    void setNext(const Node* next) { m_next = next; }
    void setPrev(const Node* prev) { m_prev = prev; }

private:

    T        m_item{};
    Node<T>* m_next{nullptr};
    Node<T>* m_prev{nullptr};

};

#endif // NODE_H
