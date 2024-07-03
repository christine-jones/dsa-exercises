#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

class UnionFind {

public:

    explicit UnionFind(int n, bool initialize = true):
        m_object_ids{std::vector<int>(static_cast<std::size_t>(n))}
    {
        assert(n > 0);

        if (initialize)
            std::iota(m_object_ids.begin(), m_object_ids.end(), 0);
    }

    UnionFind(int n, int initial_value):
        m_object_ids{
            std::vector<int>(static_cast<std::size_t>(n), initial_value)}
    {
        assert(n > 0);
    }

    virtual ~UnionFind() {}

    virtual bool connected(int p, int q) = 0;
    virtual void join(int p, int q) = 0;

    int getIndex(int p) const {

        assert(isValidIndex(p));
        return m_object_ids[static_cast<std::size_t>(p)];
    }

    virtual void print() const {

        for (int id : m_object_ids)
            std::cout << id << ' ';
        std::cout << '\n';
    }

protected:

    bool isValidIndex(int i) const {
        return i >= 0 && static_cast<std::size_t>(i) < m_object_ids.size();
    }

    std::vector<int> m_object_ids{};

};

class QuickUF : public UnionFind {

public:

    explicit QuickUF(int n):
        UnionFind(n)
    {}

    QuickUF(int n, int initial_value):
        UnionFind{n, initial_value}
    {}

    virtual ~QuickUF() {}

    bool connected(int p, int q) override {

        assert(isValidIndex(p) && isValidIndex(q));

        return m_object_ids[static_cast<std::size_t>(p)] == 
               m_object_ids[static_cast<std::size_t>(q)];
    }

    void join(int p, int q) override {

        assert(isValidIndex(p) && isValidIndex(q));

        int pid = m_object_ids[static_cast<std::size_t>(p)];
        int qid = m_object_ids[static_cast<std::size_t>(q)];

        for (std::size_t i{0}; i < m_object_ids.size(); ++i) {
            if (m_object_ids[i] == pid)
                m_object_ids[i] = qid;
        }
    }

};

class WeightedUF : public UnionFind {

public:

    explicit WeightedUF(int n):
        UnionFind{n},
        m_tree_sizes{
            std::vector<int>(static_cast<std::size_t>(n), initial_tree_size)}
    {}

    WeightedUF(int n, int initial_value):
        UnionFind(n, initial_value),
        m_tree_sizes{
            std::vector<int>(static_cast<std::size_t>(n), initial_tree_size)}
    {}

    virtual ~WeightedUF() {}

    bool connected(int p, int q) override {

        assert(isValidIndex(p) && isValidIndex(q));

        return root(p) == root(q);
    }

    void join(int p, int q) override {

        assert(isValidIndex(p) && isValidIndex(q));

        int i{(root(p))};
        int j{(root(q))};

        std::size_t index_i{static_cast<std::size_t>(i)};
        std::size_t index_j(static_cast<std::size_t>(j));

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

    void print() const override {

        assert(m_object_ids.size() == m_tree_sizes.size());

        for (std::size_t i{0}; i < m_object_ids.size(); ++i) {
            std::cout << m_object_ids[i] << '('
                      << m_tree_sizes[i] << ") ";
        }
        std::cout << '\n';
    }

private:

    int root(int i) {

        while(i != m_object_ids[static_cast<std::size_t>(i)]) {

            // path compression
            m_object_ids[static_cast<std::size_t>(i)] = 
                m_object_ids[static_cast<std::size_t>(
                                    m_object_ids[static_cast<std::size_t>(i)])];

            // follow path to root
            i = m_object_ids[static_cast<std::size_t>(i)];
        }

        return i;
    }

    // initial tree includes initial object only, so size of 1
    static constexpr int initial_tree_size{1};

    std::vector<int> m_tree_sizes{};

};

template <class T>
class OpenUF : public T {

public:

    explicit OpenUF(int n):
        T{n, blocked}
    {}

    bool isOpen(int p) const {

        assert(T::isValidIndex(p));

        return T::m_object_ids[static_cast<std::size_t>(p)] >= 0;
    }

    void open(int p) {

        if (isOpen(p))
            return;

        // open for connections by setting object ID to itself
        T::m_object_ids[static_cast<std::size_t>(p)] = p;
    }

    bool connected(int p, int q) override {

        if (!isOpen(p) || !isOpen(q))
            return false;

        return T::connected(p, q);
    }

    void join(int p, int q) override {

        if (!isOpen(p) || !isOpen(q))
            return;

        return T::join(p, q);
    }

private:

    // value assigned to objects not openly availabe for connections
    static constexpr int blocked{-1};

};

#endif // UNION_FIND_H
