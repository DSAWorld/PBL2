#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
<<<<<<< Updated upstream
=======
#include <string.h>
#include "LinkedList.h"
>>>>>>> Stashed changes

using namespace std;

enum Status{
    Active,
    Expired,
    Suspended
};

class Member{
<<<<<<< Updated upstream
=======
    protected:
>>>>>>> Stashed changes
    string ID;
    string Name;
    string Contact;
    enum Status state;
    string *Hist;
    string *TransactionID;
<<<<<<< Updated upstream
=======
    public:
    friend bool LinkedList<Member>::Comp(const Member& A, const Member& B, string Member::*memberPtr, bool asc);
>>>>>>> Stashed changes
};

#endif // MEMBER_H