#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>

using namespace std;

enum Status{
    Active,
    Expired,
    Suspended
};

class Member{
    string ID;
    string Name;
    string Contact;
    enum Status state;
    string *Hist;
    string *CurrentLoan;
};

#endif // MEMBER_H