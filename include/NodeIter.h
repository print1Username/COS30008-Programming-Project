#pragma once
#include "Node.h"

template<class T>
class NodeIter {
private:
    Node<T> * current;

public:
    NodeIter(Node<T> * start) :
        current(start) {}

    NodeIter(Node<T> & node) :
        current(&node) {}

    NodeIter<T> & operator++() {
        current = current->getNext();
        return *this;
    }

    NodeIter<T> operator++(int) {
        NodeIter<T> temp = *this;
        current = current->getNext();
        return temp;
    }

    NodeIter<T> & operator--() {
        current = current->getPrev();
        return *this;
    }

    NodeIter<T> operator--(int) {
        NodeIter<T> temp = *this;
        current = current->getPrev();
        return temp;
    }

    bool operator==(const NodeIter<T> & other) const {
        return current == other.current;
    }

    bool operator!=(const NodeIter<T> & other) const {
        return current != other.current;
    }

    T & operator*() const {
        return current->getData();
    }

    Node<T> * getCurrent() {
        return current;
    }

    NodeIter begin() {
        return NodeIter<T>(current);
    }

    // Fixed end(): must return iterator pointing to NIL
    NodeIter end() {
        return NodeIter<T>(&Node<T>::NIL);
    }
};
