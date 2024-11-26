/**
 * \file    UnionFind.cpp
 * \author  Christine Jones 
 * \brief   Class implemenation of various UnionFind algorithms.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#include "UnionFind.h"
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>

int UnionFind::getID(int p) const {

    assert(isValidIndex(p));
    return m_object_ids[static_cast<std::size_t>(p)];
}

std::string UnionFind::toStr() const {

    std::stringstream ss;
    for (int id : m_object_ids)
        ss << id << ' ';

    return ss.str();
}

bool UnionFind::isValidIndex(int i) const {

    return i >= 0 && static_cast<std::size_t>(i) < m_object_ids.size();
}

bool QuickUF::connected(int p, int q) {

    assert(isValidIndex(p) && isValidIndex(q));

    // objects connected if IDs match
    return m_object_ids[static_cast<std::size_t>(p)] == 
           m_object_ids[static_cast<std::size_t>(q)];
}

void QuickUF::join(int p, int q) {

    assert(isValidIndex(p) && isValidIndex(q));

    int pid = m_object_ids[static_cast<std::size_t>(p)];
    int qid = m_object_ids[static_cast<std::size_t>(q)];

    // joining object p, and all other connected objects, to object q
    for (std::size_t i{0}; i < m_object_ids.size(); ++i) {
        if (m_object_ids[i] == pid)
            m_object_ids[i] = qid;
    }
}

bool WeightedUF::connected(int p, int q) {

    assert(isValidIndex(p) && isValidIndex(q));

    // objects connected if roots match
    return root(p) == root(q);
}

void WeightedUF::join(int p, int q) {

    assert(isValidIndex(p) && isValidIndex(q));

    // retrieve object roots
    int i{(root(p))};
    int j{(root(q))};

    std::size_t index_i{static_cast<std::size_t>(i)};
    std::size_t index_j(static_cast<std::size_t>(j));

    // same root, objects already joined
    if (i == j)
        return;

    // root smaller tree to larger tree
    if (m_tree_sizes[index_i] < m_tree_sizes[index_j]) {

        m_object_ids[index_i] = j;
        m_tree_sizes[index_j] += m_tree_sizes[index_i];

    } else {

        m_object_ids[index_j] = i;
        m_tree_sizes[index_i] += m_tree_sizes[index_j];
    }
}

std::string WeightedUF::toStr() const {

    assert(m_object_ids.size() == m_tree_sizes.size());

    std::stringstream ss;
    for (std::size_t i{0}; i < m_object_ids.size(); ++i) {
        ss << m_object_ids[i] << '('
           << m_tree_sizes[i] << ") ";
    }

    return ss.str();
}

int WeightedUF::root(int i) {

    // root of obejct tree is when object index and ID match
    while (i != m_object_ids[static_cast<std::size_t>(i)]) {

        // path compression
        m_object_ids[static_cast<std::size_t>(i)] = 
            m_object_ids[static_cast<std::size_t>(
                                m_object_ids[static_cast<std::size_t>(i)])];

        // follow path to root
        i = m_object_ids[static_cast<std::size_t>(i)];
    }

    return i;
}
