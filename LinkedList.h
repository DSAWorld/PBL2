#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
template <typename Class>
class Node{
public:
    Class data;
    Node* next;
    Node(Class value) : data(value), next(nullptr) {}
};

template <typename Class>
class LinkedList {
private:
    Node<Class>* head;
    Node<Class>* tail;
    unsigned int Size;
public:
    LinkedList() : head(nullptr), tail(nullptr){};
    LinkedList(Class Data);
    ~LinkedList();
    void display() const;
    void deleteIndex(int index);
    void Swap(Node<Class> *A, Node<Class> *B);
    template <typename Member> bool CompEqual(const Class &A, const Class &B, Member Class::*memberPtr);
    template <typename Member> bool Comp(const Class &A, const Class &B, Member Class::*memberPtr, bool asc);
    template <typename Member> Node<Class>* Partition(Node<Class>* low, Node<Class>* high, Member Class::*memberPtr, bool &Asc);
    template <typename Member> void Sort(Node<Class>* low, Node<Class>* high, Member Class::*memberPtr, bool &Asc);
    template <typename Member> void SortWrap(Member Class::*memberPtr);
};  

#endif // LINKEDLIST_H