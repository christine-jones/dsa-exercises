/**
 * \file    UnionFind.h
 * \author  Christine Jones 
 * \brief   Definition of classes that implement various UnionFind algorithms.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <cassert>
#include <numeric>  // std::iota
#include <string>
#include <vector>

/**
 * Virtual base class to implement Union-Find algorithm variants.
 */
class UnionFind {

public:
    /**
     * Constructor.
     * 
     * \param int Number of connectivity objects; must be greater than zero.
     */
    explicit UnionFind(int n):
        m_object_ids{std::vector<int>(static_cast<std::size_t>(n))}
    {
        assert(n > 0);
    }

    /**
     * Constructor.
     * 
     * \param int Number of connectivity objects; must be greater than zero.
     * \param int Value used to initialize object IDs; defaults to zero. 
     */
    UnionFind(int n, int initial_value):
        m_object_ids{
            std::vector<int>(static_cast<std::size_t>(n), initial_value)}
    {
        assert(n > 0);
    }

    /**
     *  Destructor.
     */
    virtual ~UnionFind() {}

    /**
     * Determines if two given objects are connected; pure virtual function.
     * 
     * \param int Object index; must be greater or equal to zero and less than
     *            total number of objects.
     * \param int Object index; must be greater or equal to zero and less than
     *            total number of objects.
     * 
     * \return bool True if given objects are connected; False otherwise.
     */
    virtual bool connected(int p, int q) = 0;

    /**
     * Join two given objects (i.e., union); pure virtual function.
     * 
     * \param int Object index; must be greater or equal to zero and less than
     *            total number of objects.
     * \param int Ojbect index; must be greater or equal to zero and less than
     *            total number of objects.
     */
    virtual void join(int p, int q) = 0;

    /**
     * Retrieve object identifier.
     * 
     * \param int Object index; must be greater or equal to zero and less than
     *            total number of objects.
     * 
     * \return int Object identifier.
     */
    int getID(int p) const;

    /**
     * Convert object to string format for testing purposes.
     */
    virtual std::string toStr() const;

protected:

    /**
     * Determines if given object index is valid, i.e., greater than zero and
     * les than total number of objects.
     * 
     * \param int Object index.
     * 
     * \return bool True if valid object index; False otherwise.
     */
    bool isValidIndex(int i) const;

    // object identifiers used in determining connection relationships
    std::vector<int> m_object_ids{};

};

/**
 * Class that implements the Quick UnionFind algorithm.
 */
class QuickUF : public UnionFind {

public:
    /**
     * Constructor.
     * 
     * \param int Number of connectivity objects; must be greater than zero.
     */
    explicit QuickUF(int n):
        UnionFind(n)
    {
        std::iota(m_object_ids.begin(), m_object_ids.end(), 0);
    }

    /**
     * Constructor.
     * 
     * \param int Number of connectivity objects; must be greater than zero.
     * \param int Value used to initialize object IDs; defaults to zero. 
     */
    QuickUF(int n, int initial_value):
        UnionFind(n, initial_value)
    {}

    /**
     * Destructor.
     */
    virtual ~QuickUF() {}

    /**
     * Determines if two given objects are connected.
     * 
     * \param int Object index; must be greater or equal to zero and less than
     *            total number of objects.
     * \param int Object index; must be greater or equal to zero and less than
     *            total number of objects.
     * 
     * \return bool True if given objects are connected; False otherwise.
     */
    bool connected(int p, int q) override;

    /**
     * Join two given objects (i.e., union).
     * 
     * \param int Object index; must be greater or equal to zero and less than
     *            total number of objects.
     * \param int Ojbect index; must be greater or equal to zero and less than
     *            total number of objects.
     */
    void join(int p, int q) override;

};

/**
 * Class that implements the Weighted UnionFind algorithm with path
 * compression.
 */
class WeightedUF : public UnionFind {

public:

    /**
     * Constructor.
     * 
     * \param int Number of connectivity objects; must be greater than zero.
     */
    explicit WeightedUF(int n):
        UnionFind{n},
        m_tree_sizes{
            std::vector<int>(static_cast<std::size_t>(n), initial_tree_size)}
    {
        std::iota(m_object_ids.begin(), m_object_ids.end(), 0);
    }

    /**
     * Constructor.
     * 
     * \param int Number of connectivity objects; must be greater than zero.
     * \param int Value used to initialize object IDs; defaults to zero. 
     */
    WeightedUF(int n, int initial_value):
        UnionFind{n, initial_value},
        m_tree_sizes{
            std::vector<int>(static_cast<std::size_t>(n), initial_tree_size)}
    {}

    /**
     * Destructor.
     */
    virtual ~WeightedUF() {}

    /**
     * Determines if two given objects are connected.
     * 
     * \param int Object index; must be greater or equal to zero and less than
     *            total number of objects.
     * \param int Object index; must be greater or equal to zero and less than
     *            total number of objects.
     * 
     * \return bool True if given objects are connected; False otherwise.
     */
    bool connected(int p, int q) override;

    /**
     * Join two given objects (i.e., union).
     * 
     * \param int Object index; must be greater or equal to zero and less than
     *            total number of objects.
     * \param int Ojbect index; must be greater or equal to zero and less than
     *            total number of objects.
     */
    void join(int p, int q) override;

    /**
     * Convert object to string format for testing purposes.
     */
    std::string toStr() const override;

private:

    /**
     * Find and return root of given object's tree.
     */
    int root(int i);

    // initial tree includes object self only, so size of 1
    static constexpr int initial_tree_size{1};

    // tree size corresponding to each object
    std::vector<int> m_tree_sizes{};

};

/**
 * Implementation of open-enabled UnionFind algorithms. Requires a base
 * UnionFind algorithm, e.g., QuickUF and WeightedUF, as template parameter.
 * 
 * The open-enabled variant initially blocks, i.e., disables, all connection
 * objects. Objects must be opened via the provided class method to be enabled
 * for joins.
 */
template <class T>
class OpenUF : public T {

public:

    /**
     * Constructor.
     * 
     * \param int Number of connectivity objects; must be greater than zero. 
     */
    explicit OpenUF(int n):
        T{n, blocked}
    {}

    /**
     * Determines if given object is open for join.
     * 
     * \param int Object index; must be greater or equal to zero and less than
     *            total number of objects.
     * 
     * \return bool True if given object open for join; False otherwise.
     */
    bool isOpen(int p) const {

        assert(T::isValidIndex(p));

        // object is open for join if not blocked
        return T::m_object_ids[static_cast<std::size_t>(p)] != blocked;
    }

    /**
     * Opens given object for join.
     * 
     * \param int Object index; must be greater or equal to zero and less than
     *            total number of objects.
     */
    void open(int p) {

        if (isOpen(p))
            return;

        // open for join by setting object ID to itself
        T::m_object_ids[static_cast<std::size_t>(p)] = p;
    }

    /**
     * Determines if two given objects are connected.
     * 
     * \param int Object index; must be greater or equal to zero and less than
     *            total number of objects.
     * \param int Object index; must be greater or equal to zero and less than
     *            total number of objects.
     * 
     * \return bool True if given objects are connected; false otherwise.
     */
    bool connected(int p, int q) override {
    
        if (!isOpen(p) || !isOpen(q))
            return false;

        return T::connected(p, q);
    }

    /**
     * Join two given objects (i.e., union).
     * 
     * \param int Object index; must be greater or equal to zero and less than
     *            total number of objects.
     * \param int Ojbect index; must be greater or equal to zero and less than
     *            total number of objects.
     */
    void join(int p, int q) override {
    
        if (!isOpen(p) || !isOpen(q))
            return;

        return T::join(p, q);
    }
    
private:

    // value assigned to objects not open for join
    static constexpr int blocked{-1};

};

#endif // UNION_FIND_H
