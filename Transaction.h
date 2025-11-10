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
    unsigned int Amount;
};


class TranState;

enum TransreturnTypes{
    TransstringID = 1,
    TransstringOwner = 2,
    TransstringBookID = 3,
    TransDateBorrowing = 1,
    TransDateDue = 2,
    TransDateReturn = 3,
};

enum TransStatus{
    Actived,
    Reserved,
    Returned,
    Overdue, //sub-Status of Actived
    Cancelled
};

class Transaction{
    string ID; //TransactNum-TotalAmount;
    string OwnerID;
    Items *List;
    unsigned int NumberofItems = 0;
    unsigned int ItemCount = 0;
    Date Borrowing;
    Date Due;
    Date ReturnDate;
    TranState *State;
    int Status;
    public:
    Transaction(string Owner, int state, int borrowingdays, Items *ItemList, int Number, LinkedList<Resources>& BooksList);
    string IDHelper(long);
    static string StringHelper(int Value){
        if (Value < 10) return "0" + to_string(Value);
        else return to_string(Value);
    };
    void BorrowDate(int Days);
    void Search(const LinkedList<Transaction>& TransactionList);
    void CreateBookList(LinkedList<Resources>& BooksList);
    void ReturnBooks(LinkedList<Resources>& BooksList);
    void Revalidate();
    void HandlingStates(Node<Transaction> *Nodeprev);
    void setState(TranState* newState);

    static auto getDatePtr(int Types){
        switch (Types){
        case TransDateBorrowing: return &Transaction::Borrowing; 
        case TransDateDue: return &Transaction::Due;
        case TransDateReturn: return &Transaction::ReturnDate;
        }
    };

    static auto getStringPtr(int Types){
        switch(Types){
            case TransstringID: return &Transaction::ID;
            case TransstringOwner: return &Transaction::OwnerID;
        }
    };

    // friend bool LinkedList<Transaction>::Comp(const Transaction& A, const Transaction& B, Date Transaction::*memberPtr, bool asc);
    // friend bool LinkedList<Transaction>::Comp(const Transaction& A, const Transaction& B, string Transaction::*memberPtr, bool asc);
    friend ostream& operator<<(ostream& os, const Transaction &A); 
};

class TranState{
    public:
        virtual ~TranState(){};
        virtual void handle(Transaction *Trans){};
        virtual void handleAlt(Transaction *Trans){
            cout<<"\nLoi: Chi co the huy The o trang thai giu cho";
        }
        virtual int getState() = 0;
};


class ActiveState: public TranState{
    public:
        int getState() override{
            return Actived;
        }
        void handle(Transaction *Trans) override;
};

class ReserveState: public TranState{
    public:
        int getState() override{
            return Reserved;
        }
        void handle(Transaction *Trans) override;
        void handleAlt(Transaction *Trans) override;
};

class ReturnState: public TranState{
    public:
        int getState() override{
            return Returned;
        }
        void handle(Transaction *Trans) override {};
};

class CancelState: public TranState{
    public:
        int getState() override{
            return Cancelled;
        }
        void handle(Transaction *Trans) override {};
};

#endif // TRANSAC_H