/**
 * \file    Node.h
 * \author  Christine Jones 
 * \brief   Class that implements a single linked-list node.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef NODE_H
#define NODE_H

/**
 * Linked-list node that contains an object of templated type. The templated
 * type must be CopyAssignable and CopyConstructible.
 */
template <typename T>
class Node {

public:

    /**
     * Constructor. Node linked to no other nodes.
     * 
     * \param T Object of templated type to be contained within the node. 
     */
    explicit Node(const T& item):
        m_item{item},
        m_next{nullptr},
        m_prev{nullptr}
    {}

    /**
     * Constructor. Node with assigned links.
     * 
     * \param T Object of templated type to be contained within the node.
     * \param Node<T>* pointer to next node in linked list
     * \param Node<T>* pointer to prev node in linked list
     */
    Node(const T& item, Node<T>* next, Node<T>* prev):
        m_item{item},
        m_next{next},
        m_prev{prev}
    {}

    /**
     * Methods for accessing item contained within the node. 
     */
    T&       item()       { return m_item; }
    const T& item() const { return m_item; }

    /**
     * Methods for accessing pointer to item contained within the node.
     */
    T*       itemPtr()       { return &m_item; }
    const T* itemPtr() const { return &m_item; }

    /**
     * Methods for accessing the prev/next pointers of the node.
     */
    Node<T>* next() { return m_next; }
    Node<T>* prev() { return m_prev; }
    const Node<T>* next() const { return m_next; }
    const Node<T>* prev() const { return m_prev; }

    /**
     * Methods for setting the prev/next pointers of the node.
     */
    void setNext(Node<T>* next) { m_next = next; }
    void setPrev(Node<T>* prev) { m_prev = prev; }

private:

    T        m_item{};
    Node<T>* m_next{nullptr};
    Node<T>* m_prev{nullptr};

};

#endif // NODE_H
