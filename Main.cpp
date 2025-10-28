#include "LinkedList.h"
#include "function.cpp"
#include "Books.h"
#include <iostream>
#include <conio.h>

using namespace std;

/*class Exam {
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
};*/

int main() {
    LinkedList<Books> bookList;
    readFromFile("Library.txt", bookList);
    bookList.display();
    return 0;
}