#ifndef TRANSAC_H
#define TRANSAC_H

#include <iostream>
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
};

#endif // TRANSAC_H