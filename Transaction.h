#ifndef TRANSAC_H
#define TRANSAC_H

#include <iostream>
#include <string.h>
#include "LinkedList.h"
#include "Date.h"
#include "Member.h"
#include "Books.h"

using namespace std;

struct Items{
    string BookID;
    unsigned int Amount = 0;
};

Member ReturningMember;

enum returnTypes{
    stringID = 1,
    stringOwner = 2,
    intItemCount = 1,
    intState = 2,
    DateBorrowing = 1,
    DateDue = 2,
    DateReturn = 3,
}

enum Status{
    Active,
    Reserved,
    Ready,
    Returned,
    Overdue
};

class Transaction{
    string ID; //TransactNum-TotalAmount;
    string OwnerID;
    Items *List;
    int ItemCount;
    Date Borrowing;
    Date Due;
    Date ReturnDate;
    unsigned int Fee = 0;
    int State;
    public:
    Transaction(string Owner, int state);

    string IDHelper(long);
    ~Transaction();
    void Reserve();
    void BorrowDate(int Days);
    void CalculateFee(Member &ReturningMember);
    void Return(Member &ReturningMember);
    void Search(const LinkedList<Member>& allMembers);
    Items CreateBookList();
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
    };;
    friend bool LinkedList<Transaction>::Comp(const Transaction& A, const Transaction& B, Date Transaction::*memberPtr, bool asc);
    friend bool LinkedList<Transaction>::Comp(const Transaction& A, const Transaction& B, string Transaction::*memberPtr, bool asc);
    friend ostream& operator<<(ostream& os, const Transaction &A); 
};

#endif // TRANSAC_H