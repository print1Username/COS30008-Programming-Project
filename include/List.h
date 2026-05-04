#pragma once
#include <iostream>
#include "Node.h"
#include "NodeIter.h"
using namespace std;

template <class T>
class List {
private:
    Node<T> * head;
    Node<T> * last;
    int count;

public:
    List() :
        head(&(Node<T>::NIL)), last(&(Node<T>::NIL)), count(0) {}

    List(Node<T> * value) :
        head(value), last(value), count(1) {}

    ~List() {
        clear();
    }

    bool isEmpty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }

    void clear() {
        Node<T> * curr = head;
        while ( curr != &Node<T>::NIL ) {
            Node<T> * next = curr->getNext();
            delete curr;
            curr = next;
        }
        head = last = &Node<T>::NIL;
        count = 0;
    }

    void add(const T & value) {
        Node<T> * newNode = new Node<T>(value);

        if ( isEmpty() ) {
            head = last = newNode;
            count++;
            return;
        }

        last->append(newNode);
        last = newNode;
        count++;
    }

    void remove(int v) {
        if ( v < 0 || v >= count )
            throw out_of_range("Error: Index is out of range.");

        Node<T> * current = head;

        // Traverse to the target node
        for ( int i = 0; i < v; i++ )
            current = current->getNext();

        // Save prev and next
        Node<T> * p = current->getPrev();
        Node<T> * n = current->getNext();

        bool isHead = (current == head);
        bool isLast = (current == last);

        // Adjust neighbor links (using setter)
        if ( p != &Node<T>::NIL )
            p->setNext(n);

        if ( n != &Node<T>::NIL )
            n->setPrev(p);

        // Update head and last
        if ( isHead )
            head = n;

        if ( isLast )
            last = p;

        // If removing the only element
        if ( count == 1 )
            head = last = &Node<T>::NIL;

        delete current;
        count--;
    }
    
    NodeIter<T> getIter() const {
        return NodeIter<T>(head);
    }

    void print() {
        for ( NodeIter<T> it = getIter(); it != it.end(); it++ ) {
            cout << *it << endl;
        }
    }

    friend ostream & operator<<(ostream & os, const List<T> & list) {
        os << "[ ";
        Node<T> * current = list.head;
        for ( int i = 0; i < list.count; ++i ) {
            os << current->getData();
            if ( i < list.count - 1 ) os << ", ";
            current = current->getNext();
        }
        os << " ]";
        return os;
    }

    T & operator[](int index) {
        if ( index < 0 || index >= count )
            throw out_of_range("Index out of range!");

        Node<T> * current = head;
        for ( int i = 0; i < index; ++i )
            current = current->getNext();

        return current->getData();
    }

    const T & operator[](int index) const {
        if ( index < 0 || index >= count )
            throw out_of_range("Index out of range!");

        Node<T> * current = head;
        for ( int i = 0; i < index; ++i )
            current = current->getNext();

        return current->getData();
    }
};
