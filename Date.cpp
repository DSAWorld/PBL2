#include "Date.h"

Date::Date(int ConvVal){
    int TimeVal = (ConvVal+25200) / 86400;
    Date UnitTime(1,1,1970);
    *this = UnitTime + TimeVal;
}

Date::Date(const Date &A):D(A.D), M(A.M), Y(A.Y){}

int Date::NoofDay(){
    const int Mon[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (M == 2 && ((Y % 4 == 0 && Y % 100 !=0) || Y % 400 == 0)) return 29;
    else return Mon[M-1];
}

bool Date::isValid(){
    return !( D < 1 || M < 1 || M > 12 || D > NoofDay() );
}
Date Date::operator + (int Add) {
    D += Add;
    int Temp = NoofDay();
    while (D>Temp){
        M++;
        D -= Temp;
        if(M == 13){
            Y++;
            M=1;
        }
        Temp = NoofDay();
    }
    return *this;
};
Date Date::operator - (int Sub){
    D -= Sub;
    while (D<1){
        M--;
        if(M == 0){
            Y--;
            M=12;
        }
        D += NoofDay();
    }
    return *this;
};

int Date::operator - (Date &Sub) const {
    const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int days1 = Y * 365 + D;
    for (int i = 0; i < M - 1; i++){
        days1 += monthDays[i];
    };
    days1 += (Y / 4) - (Y / 100) + (Y / 400);
    int days2 = Sub.Y * 365 + Sub.D;
    for (int i = 0; i < Sub.M - 1; i++){
        days2 += monthDays[i];
    };
    days2 += (Sub.Y / 4) - (Sub.Y / 100) + (Sub.Y / 400);
    return days1 - days2;
}

bool Date::operator < (Date &Sub){
    return *this-Sub<=0;
}

bool Date::operator > (Date &Sub){
    return !(*this < Sub);
}

istream &operator >> (istream &in, Date &x){
    if(!x.isValid()) {
        x.D = x.M = 1;
        x.Y = 2025;
    }
    return in;
}

ostream &operator <<(ostream &out, const Date &x){
    out<<x.D<<"/"<<x.M<<"/"<<x.Y;
    return out;
};