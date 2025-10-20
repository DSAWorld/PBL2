#ifndef DATE_H
#define DATE_H

#include <iostream>
#include "LinkedList.h"

using namespace std;

class Date{
    public:
    int D, M, Y;
    Date():D(0),M(0),Y(0){};
    Date(int d, int m, int y):D(d), M(m), Y(y){};
    Date(int Conv);
    Date(const Date &Temp);
    ~Date(){};
    int NoofDay();
    bool isValid();
    friend istream &operator >> (istream &in, Date &x);
    friend ostream &operator << (ostream &out, const Date &x);
    int operator - (Date &Sub) const; 
    Date operator + (int Add);
    Date operator - (int Sub);
    bool operator < (Date &Sub); 
    bool operator > (Date &Sub);
    };

#endif // DATE_H