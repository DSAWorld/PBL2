#include <iostream>
#include "LinkedList.h"

using namespace std;

template <typename Class> LinkedList<Class>::LinkedList(const LinkedList<Class> &other):head(nullptr), tail(nullptr){
        if (!other.head)
            return;
        Node<Class> *currentOther = other.head;
        while (currentOther)
        {
            this->Add(currentOther->data);
            currentOther = currentOther->next;
        }
    };

template <typename Class>
void LinkedList<Class>::Add(Class Data){
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
void LinkedList<Class>::Pushback(Class Data){
    Node<Class> *newNode = new Node<Class>(Data);
    if (head == nullptr){
        head = newNode;
        tail = head;
    } else {
        newNode -> next = head;
        head = newNode;
    }
}

template <typename Class>
LinkedList<Class>::~LinkedList(){
    Node<Class> *temp = head;
    while (temp != nullptr){
        Node<Class> *next = temp->next;
        delete temp;
        temp = next;
    }
    head = nullptr;
    tail = nullptr;
}

template <typename Class> 
void LinkedList<Class>::deleteIndex(int index) {
    if (head == nullptr) {
        cout << "DSLK rong" << endl;
        return;
    }
    if (index < 1) {
        cout << "Gia tri khong hop le" << endl;
        return;
    }
    Node<Class> *current = head;
    Node<Class> *prev = nullptr;
    if (index == 1) {
        head = head->next;
        if (head == nullptr) tail = nullptr;
        delete current;
        return;
    }
    int count = 1;
    while (current != nullptr && count < index) {
        prev = current;
        current = current->next;
        count++;
    }
    if (current == nullptr) {
        cout << "Index out of range" << endl;
        return;
    }
    prev->next = current->next;
    if (current == tail) tail = prev;
    delete current;
}

template <typename Class> void LinkedList<Class>::display() const {
    cout << "______________________________" << endl;
    Node<Class> *temp = head;
    while (temp)
    {
        cout << temp->data << endl;
        temp = temp->next;
    }
    cout << "______________________________" << endl;
};

template <typename Class>
template <typename Member> 
LinkedList<Class> LinkedList<Class>::SearchMethod(Member Class::*memberPtr, Member Data) const {
    LinkedList<Class> Result;
    Node<Class> *Curr = head;
    while (Curr != nullptr){
        if(Curr->data.*memberPtr == Data){
        Result.Add(Curr->data);
        }
        Curr = Curr->next;
    }
    return Result;
};

template <typename Class>
template <typename Member>
bool LinkedList<Class>::Comp(const Class &A, const Class &B, Member Class::*memberPtr, bool asc) {
    return asc ? (A.*memberPtr < B.*memberPtr) : (A.*memberPtr > B.*memberPtr);
}

template <typename Class>
void LinkedList<Class>::Swap(Node<Class>* A, Node<Class>* B) {
    Class Temp = A->data;
    A->data = B->data;
    B->data = Temp;
}

template <typename Class>
template <typename Member>
Node<Class>* LinkedList<Class>::Partition(Node<Class>* low, Node<Class>* high, Member Class::*memberPtr, bool &Asc) {
    Class pivot = high->data;
    Node<Class>* i = low; 
    Node<Class>* j = low; 
    
    while (j != high) {
        if (Asc ? (j->data.*memberPtr < pivot.*memberPtr) : (j->data.*memberPtr > pivot.*memberPtr)) {
            Swap(i, j);
            i = i->next;
        }
        j = j->next;
    }
    Swap(i, high);
    return i;
}

template <typename Class>
template <typename Member>
void LinkedList<Class>::Sort(Node<Class>* low, Node<Class>* high, Member Class::*memberPtr, bool &Asc){
    if (low != high->next || low != high){
        Node<Class> *Point = Partition(low, high, memberPtr, Asc);
        Sort(low, Point, memberPtr, Asc);
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
        if (Choice == 0) return;
        if (Choice == 1 || Choice == 2) {
            if (Choice == 1) Asc = 1;
            else Asc = 0;
            break;
        };
    }
    Sort(head, tail, memberPtr, Asc);
}

template <typename ClassAlt> ostream &operator <<(ostream &out, const LinkedList<ClassAlt> &list){
    if (list.head == nullptr){
        cout<<"\nDanh sach rong";
        return out;
    }
    Node<ClassAlt> *Curr = list.head;
    ClassAlt::header(out);
    while (Curr != nullptr){
    out<<"\n"<<Curr->data;
    Curr=Curr->next;
    }
    return out;
}

void LinkedList<Class>::Search(){
    
}