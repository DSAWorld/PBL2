#include "myInclude.h"

using namespace std;

int main() {
    LinkedList<Books> bookList;
    readFromFile("Sach.txt", bookList);
    bookList.display();
    getch();
    return 0;
}