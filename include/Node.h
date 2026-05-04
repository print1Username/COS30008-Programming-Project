#pragma once

template<class T>
class Node {
public:
    static Node<T> NIL;

private:
    T data;
    Node<T> * prev;
    Node<T> * next;

public:
    Node() :
        data(T()), prev(&NIL), next(&NIL) {}

    Node(const T & data) :
        data(data), prev(&NIL), next(&NIL) {}

    // Add the value after the current node
    void append(Node<T> * newNode) {
        newNode->prev = this;

        if ( this->next != &NIL ) {
            newNode->next = this->next;
            this->next->prev = newNode;
        }
        this->next = newNode;
    }

    // Remove current node from list (DO NOT delete this inside)
    void detach() {
        if ( prev != &NIL )
            prev->next = next;

        if ( next != &NIL )
            next->prev = prev;

        prev = &NIL;
        next = &NIL;
        // ! Do NOT delete here — deletion must be done by List::remove()
    }

    // Getters
    T & getData() { return data; }
    const T & getData() const { return data; }

    Node<T> * getPrev() const { return prev; }
    Node<T> * getNext() const { return next; }

    // ---- Added setters for List ----
    void setPrev(Node<T> * p) { prev = p; }
    void setNext(Node<T> * n) { next = n; }

};

template<class T>
Node<T> Node<T>::NIL = Node<T>();
