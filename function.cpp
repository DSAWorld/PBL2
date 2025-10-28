#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include"function.h"
#include"Transaction.h"
using namespace std;

template <typename Class>
void readFromFile(const string& filename, LinkedList<Class>& list) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file " << filename << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        Class item(line);
        list.Add(item);
    }
    file.close();
}

template <typename Class>
void writeToFile(const string& filename, const LinkedList<Class>& list) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file " << filename << " for writing." << endl;
        return;
    }
    Node<T>* current = list.head;
    while (current != nullptr) {
        file << current->data.toString() << endl;
        current = current->next;
    }
    file.close();
}