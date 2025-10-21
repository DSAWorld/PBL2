#ifndef TRANSAC_H
#define TRANSAC_H

#include <iostream>
#include <string.h>
#include "LinkedList.h"
#include "Date.h"
#include "Member.h"
#include "Books.h"

using namespace std;

class Items{
    string BookID;
    unsigned int Amount = 0;
    public:
    Items():BookID(""), Amount(0){};
    Items(string ID, unsigned int Amt):BookID(ID), Amount(Amt){};
    Items(const Items &A):BookID(A.BookID), Amount(A.Amount){};
    ~Items(){};
    string toString() const {
        return BookID + "," + to_string(Amount);
    }
};

enum returnTypes{
    stringID = 1,
    stringOwner = 2,
    intItemCount = 1,
    intState = 2,
    DateBorrowing = 1,
    DateDue = 2,
    DateReturn = 3,
};

enum TransStatus{
    Actived,
    Reserved,
    Ready,
    Returned,
    Overdue
};

class Transaction{
    string ID; //TransactNum-TotalAmount;
    string OwnerID;
    LinkedList<Items>* List;
    int ItemCount;
    Date Borrowing;
    Date Due;
    Date ReturnDate;
    unsigned int Fee = 0;
    int State;
    public:
    Transaction() : ID(""), OwnerID(""), List(nullptr), ItemCount(0), Borrowing(), Due(), ReturnDate(), Fee(0), State(Actived) {};
    Transaction(string Owner, int state, int borrowingdays, Items *ItemList);
    Transaction(const Transaction &A):ID(A.ID), OwnerID(A.OwnerID), List(A.List), ItemCount(A.ItemCount), Borrowing(A.Borrowing), Due(A.Due), ReturnDate(A.ReturnDate), Fee(A.Fee), State(A.State){};
    Transaction(const string& str);
    string IDHelper(long);
    static string StringHelper(int Value){
        if (Value < 10) return "0" + to_string(Value);
        else return to_string(Value);
    };
    ~Transaction();
    void Reserve();
    void BorrowDate(int Days);
    void CalculateFee(Member &ReturningMember);
    void Return(Member &ReturningMember);
    void Search(const LinkedList<Transaction>& List);
    void CreateBookList(LinkedList<Books>& AllBooks);
    static auto getDatePtr(int Types){
        if (Types == DateBorrowing) return &Transaction::Borrowing; 
        if (Types == DateDue) return &Transaction::Due;
        if (Types == DateReturn) return &Transaction::ReturnDate;
    };
    static auto getStringPtr(int Types){
        if (Types == stringID) return &Transaction::ID; 
        if (Types == stringOwner) return &Transaction::OwnerID;
    };
    static auto getIntPtr(int Types){
        if (Types == intItemCount) return &Transaction::ItemCount; 
        if (Types == intState) return &Transaction::State;
    };
    string toString() const;
    string toString(LinkedList<Items>* ItemList) const;
    friend bool LinkedList<Transaction>::Comp(const Transaction& A, const Transaction& B, Date Transaction::*memberPtr, bool asc);
    friend bool LinkedList<Transaction>::Comp(const Transaction& A, const Transaction& B, string Transaction::*memberPtr, bool asc);
    friend ostream& operator<<(ostream& os, const Transaction &A); 
};

#endif // TRANSAC_H