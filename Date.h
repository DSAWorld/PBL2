#ifndef DATE_H
#define DATE_H

#include <iostream>
<<<<<<< Updated upstream
=======
#include "LinkedList.h"
>>>>>>> Stashed changes

using namespace std;

class Date{
    int D, M, Y;
<<<<<<< Updated upstream
};
=======
    public:
    Date(int d = 1, int m = 1, int y = 2025):D(d), M(m), Y(y){};
    ~Date(){};
    int NoofDay();
    bool isValid();
    friend istream &operator >> (istream &in, Date &x);
    friend ostream &operator <<(ostream &out, const Date &x);
    int operator - (Date &Sub); 
    Date operator + (int Add);
    Date operator - (int Sub);
    bool operator < (Date &Sub); 
    bool operator > (Date &Sub);
    };
>>>>>>> Stashed changes

#endif // DATE_H