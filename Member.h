#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <string.h>
#include "LinkedList.cpp"
#include "Transaction.cpp"
#include "Date.cpp"

using namespace std;

template <typename Class> class LinkedList; 

enum Status{
    Active,
    Warned,
    Suspended
}

class Member{
    protected:
    Date LastVio;
    string ID;
    string Name;
    string Contact;
    string *Hist; //List of Previous Transactions
    string *TransactionID; //List of Current, not turned in Transactions
    int state;
    public:
    Member(string NameInp, string ContactInp, string IDInp){};
    static Member* newMember(const LinkedList<Member>& allMembers);
    ~Member();
    void Edit();
    void Sparing();
    void Punish(bool Hard = false)
    {   
        if (!Hard && state < Suspended) state++;
        else state = Suspended;
    };
    friend bool LinkedList<Member>::Comp(const Member& A, const Member& B, string Member::*memberPtr, bool asc);
    friend ostream& operator<<(ostream& os, const Member &A); 
};
#endif // MEMBER_H