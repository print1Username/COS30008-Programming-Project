#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

/**
 * @brief Generic N-ary tree storing pointers to objects of type T.
 *
 * This avoids copying T (important when T contains complex structures),
 * and prevents shallow copy issues.
 */
template<class T, int N>
class Tree {
private:
    T * key;                       // Pointer to the stored object
    Tree<T, N> * children[N];      // Child pointers
    Tree<T, N> * parent;            // Parent pointers

    /**
     * @brief Private constructor for the NIL sentinel node.
     * NIL has no key and all children point to itself.
     */
    Tree() : key(nullptr), parent(nullptr) {
        for ( int i = 0; i < N; i++ )
            children[i] = this;    // NIL children point to NIL
    }

public:
    static Tree<T, N> NIL_obj;     // The actual NIL object
    static Tree<T, N> * NIL;       // Pointer to the NIL object

    /**
     * @brief Constructor storing a reference to an external object.
     */
    Tree(T & obj) : key(&obj), parent(NIL) {
        for ( int i = 0; i < N; i++ )
            children[i] = NIL;     // Default children = NIL
    }

    /**
     * @brief Destructor deletes child subtrees only.
     * Does NOT delete the stored object.
     */
    ~Tree() {
        for ( int i = 0; i < N; i++ ) {
            if ( children[i] != NIL && children[i] != nullptr )
                delete children[i];
        }
    }

    /**
     * @brief Check if this node is NIL.
     */
    bool isEmpty() const {
        return this == NIL;
    }

    /**
     * @brief Get reference to stored object.
     */
    T & getKey() {
        if ( isEmpty() )
            throw runtime_error("Cannot access key of NIL node.");
        return *key;
    }

    const T & getKey() const {
        if ( isEmpty() )
            throw runtime_error("Cannot access key of NIL node.");
        return *key;
    }

    Tree<T, N> * getParent() const {
        if ( isEmpty() )
            return nullptr;
        return parent;
    }



    /**
     * @brief Access child at index (reference return).
     */
    Tree<T, N> & operator[](int index) {
        if ( isEmpty() )
            throw runtime_error("Cannot index NIL node.");
        if ( index < 0 || index >= N )
            throw out_of_range("Child index out of range.");
        return *children[index];
    }

    int getSize() {
        if ( isEmpty() ) return 0;

        int count = 0;
        for ( int i = 0; i < N; i++ ) {
            if ( children[i] != NIL )
                count++;
        }
        return count;
    }

    /**
     * @brief Get child at index. Returns NIL if invalid.
     */
    Tree<T, N> * getChild(int index) {
        if ( index < 0 || index >= N )
            return NIL;
        return children[index];
    }

    /**
     * @brief Attach a subtree at the given index.
     * Deletes existing tree at that position if not NIL.
     */
    void attachTree(int index, Tree<T, N> * subtree) {
        if ( isEmpty() )
            throw runtime_error("Cannot attach to NIL node.");
        if ( index < 0 || index >= N )
            throw out_of_range("Index out of range.");

        // Remove existing subtree
        if ( children[index] != NIL )
            delete children[index];

        if ( subtree == nullptr )
            children[index] = NIL;
        else {
            children[index] = subtree;
            subtree->parent = this;   // <-- Important
        }
    }

    /**
     * @brief Detach and return a subtree.
     * Caller becomes owner of the returned subtree.
     */
    Tree<T, N> * detachTree(int index) {
        if ( isEmpty() )
            throw runtime_error("Cannot detach from NIL node.");
        if ( index < 0 || index >= N )
            throw out_of_range("Index out of range.");

        Tree<T, N> * ret = children[index];
        children[index] = NIL;

        if ( ret != NIL )
            ret->parent = nullptr;

        return ret;
    }
};

/* Static NIL object & pointer definition */
template<class T, int N>
Tree<T, N> Tree<T, N>::NIL_obj;

template<class T, int N>
Tree<T, N> * Tree<T, N>::NIL = &Tree<T, N>::NIL_obj;
