#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
template <typename T>
class Node{
public:
    T data;
    Node* next;

    Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
public:
    LinkedList() : head(nullptr) {}
    ~LinkedList() {}
    void insert(T value) {}
    void display() const {}
    void deleteValue(int index) {}
};

#endif // LINKEDLIST_H