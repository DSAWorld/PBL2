#include "LinkedList.h"
#include "GlobalMethod.cpp"
#include <iostream>

using namespace std;

class Exam{
    protected:
    int BUCKFOI;
    int NGG;
    public:
    // friend bool LinkedList<Exam>::Comp(const Exam& A, const Exam& B, int Exam::*memberPtr, bool asc);
    Exam(int buckfoi, int ngg) : BUCKFOI(buckfoi), NGG(ngg) {}
    friend ostream& operator<<(ostream& os, const Exam &A) {
        os << "\n" << A.BUCKFOI << "   " << A.NGG;
        return os;
    }
};

int main() {
    LinkedList<Exam> A;
    Exam Test(69, 96);
    Exam Test2(59, 95);
    A.Add(Test);
    A.Add(Test2);
    A.display();
    A.SortWrap(&Exam::BUCKFOI);
    A.display();
    int i;
    cin>>i;
    return 0;
}