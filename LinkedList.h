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
    public:
        LinkedList():head(nullptr), tail(nullptr){};
        LinkedList(const LinkedList<Class> &other);
        ~LinkedList();
        bool isEmpty(){ return head == nullptr; }
        void Add(Class Data);
        void Pushback(Class Data);
        void display() const;
        void deleteIndex(int index);
        void Swap(Node<Class> *A, Node<Class> *B);
        void Search();
        void deleteData();
        template <typename Member> LinkedList<Class> SearchMethod(Member Class::*memberPtr, Member Data) const;
        template <typename Member> bool Comp(const Class &A, const Class &B, Member Class::*memberPtr, bool asc);
        template <typename Member> Node<Class>* Partition(Node<Class>* low, Node<Class>* high, Member Class::*memberPtr, bool &Asc);
        template <typename Member> void Sort(Node<Class>* low, Node<Class>* high, Member Class::*memberPtr, bool &Asc);
        template <typename Member> void SortWrap(Member Class::*memberPtr);
        template <typename ClassAlt> friend ostream& operator<<(ostream& os, const LinkedList<ClassAlt> &list);
    };  

    #endif // LINKEDLIST_H