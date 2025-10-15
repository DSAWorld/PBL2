#ifndef TRANSAC_H
#define TRANSAC_H

#include <iostream>
<<<<<<< Updated upstream
=======
#include <string.h>
#include "LinkedList.h"
>>>>>>> Stashed changes
#include "Date.h"

using namespace std;

struct Items{
    string BookID;
    unsigned int Amount = 0;
};

enum Status{
    Active,
    Returned,
    Overdue,
    Reserved,
    Ready
};

class Transaction{
    string ID;
    Items *Amount;
    Date Borrowing;
    Date Due;
    Date Return;
    enum Status stat;
<<<<<<< Updated upstream
=======
    public:
    friend bool LinkedList<Transaction>::Comp(const Transaction& A, const Transaction& B, Date Transaction::*memberPtr, bool asc);
    friend bool LinkedList<Transaction>::Comp(const Transaction& A, const Transaction& B, string Transaction::*memberPtr, bool asc);
>>>>>>> Stashed changes
};

#endif // TRANSAC_H