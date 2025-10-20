#include "LinkedList.cpp"
#include <iostream>

using namespace std;

class Exam {
    private:
    int BUCKFOI;
    int NGG;
    public:
    Exam(int buckfoi, int ngg) : BUCKFOI(buckfoi), NGG(ngg) {}
    static auto getBuckfoiPtr() { return &Exam::BUCKFOI; }
    static auto getNggPtr() { return &Exam::NGG; }
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
    A.SortWrap(Exam::getBuckfoiPtr());
    A.display();
    int i;
    cin>>i;
    return 0;
}