#ifndef LINKEDLIST_H
#define LINKEDLIST_H

using namespace std;

#include <iostream>
#include <string.h>

template <typename Class>
class Node{
public:
    Class data;
    Node* next;
    Node(Class value) : data(value), next(nullptr) {}
};

template <typename Class>
class LinkedList{
private:
    Node<Class>* head;
    Node<Class>* tail;
    static int Indexing;
public:
    int Size=0;
    LinkedList():head(nullptr), tail(nullptr){};
    LinkedList(const LinkedList<Class> &other);
    ~LinkedList();
    bool isEmpty(){ return head == nullptr; }
    void Add(Class Data);
    void Pushback(Class Data);
    void display() const;
    void deleteIndex(int index);
    void Swap(Node<Class> *A, Node<Class> *B);
    Class *searchIndex(int index);
    // template <typename Member> deleteData(Member Class::*memberPtr, Member Data, bool autoDel = 0);
    template <typename Member> Class *SearchItem(Member Class::*memberPtr, Member Data);
    template <typename Member> LinkedList<Class> SearchMethod(Member Class::*memberPtr, Member Data) const;
    // template <typename Member> bool Comp(const Class &A, const Class &B, Member Class::*memberPtr, bool asc);
    template <typename Member> Node<Class>* Partition(Node<Class>* low, Node<Class>* high, Member Class::*memberPtr, bool &Asc);
    template <typename Member> void Sort(Node<Class>* low, Node<Class>* high, Member Class::*memberPtr, bool &Asc);
    template <typename Member> void SortWrap(Member Class::*memberPtr,bool autoSort=0);
};  

#endif // LINKEDLIST_H