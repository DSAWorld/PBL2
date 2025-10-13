#include <iostream>
#include "LinkedList.h"

using namespace std;

template <typename Class>
LinkedList<Class>::LinkedList(Class Data){
    Node<Class> *newNode = new Node<Class>(Data);
    if (head == nullptr){
        head = newNode;
        tail = head;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
}

template <typename Class>
template <typename Member>
bool LinkedList<Class>::Comp(const Class &A, const Class &B, Member Class::*memberPtr, bool asc){
    if (asc) return A.*memberPtr < B.*memberPtr;
    else return A.*memberPtr > B.*memberPtr;
}

template <typename Class>
void LinkedList<Class>::Swap(Node<Class>* A, Node<Class>* B) {
    Class Temp = A->data;
    A->data = B->data;
    B->data = Temp;
}

template <typename Class>
template <typename Member>
Node<Class>* LinkedList<Class>::Partition(Node<Class>* low, Node<Class>* high, Member Class::*memberPtr, bool &Asc){
    Class piv = high->data;
    Node<Class> *i = low;
    for(Node<Class> *j = low; j != high - 1; j=j->next){
        if(Comp(j->data, piv, memberPtr, Asc)){
            Swap(i, j);
            i=i->next;
        }
    }
    Swap(i, high);
    return i;
}

template <typename Class>
template <typename Member>
void LinkedList<Class>::Sort(Node<Class>* low, Node<Class>* high, Member Class::*memberPtr, bool &Asc){
    if (high != nullptr && low != nullptr && low != high->next){
        Node<Class> *Point = Partition(low, high, memberPtr, Asc);
        Node<Class> *prevPoint = low;
        if (Point != low) {while (prevPoint -> next != Point) {prevPoint = prevPoint->next;}} else prevPoint=nullptr;
        if (prevPoint != nullptr) Sort(low, prevPoint, memberPtr, Asc);
        Sort(Point->next, high, memberPtr, Asc);
    }
}

template <typename Class>
template <typename Member> 
void LinkedList<Class>::SortWrap(Member Class::*memberPtr){
    if(head == nullptr || head->next == nullptr){
        cout<<"\nDanh sach rong hoac chi co 1 phan tu";
        return;
    }
    int Choice = -1;
    bool Asc;
    cout<<"\nNhap lua chon:"
        <<"\n[0] khong sort"
        <<"\n[1] tang dan"
        <<"\n[2] giam dan";
    while(true){
        cin>>Choice;
        switch(Choice){
            case 0: return;
            case 1: {Asc = true; break;}
            case 2: {Asc = false; break;}
            default: {cout<<"\nKhong hop le"; continue;}
        }
    }
    Sort(head, tail, memberPtr, Asc);
}