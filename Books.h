#ifndef BOOKS_H
#define BOOKS_H

#include <iostream>
#include <string.h>
#include "LinkedList.h"

using namespace std;

enum Category{
    Textbook,
    Journals,
    Research,
    STEM,
    Med,
    Law,
    Business,
    Psychologies,
    OldThesis,
    Misc
};

class Books{
    private: 
    string ID; //ISBN-[Edition]
    string Name; //50 before truncate
    string Author; //30 before truncate
    string Publisher; //30 before truncate
    enum Category genre;
    unsigned int TotalAmount;
    unsigned int Available;
    public:
    
    static auto getID() { return &Books::ID;};
    static auto getName() { return &Books::Name;};
    static auto getAuthor() { return &Books::Author;};
    static auto getPublisher() { return &Books::Publisher;};
    static auto getAvailable() { return &Books::Available;};
    friend bool LinkedList<Books>::Comp(const Books& A, const Books& B, int Books::*memberPtr, bool asc);
    friend bool LinkedList<Books>::Comp(const Books& A, const Books& B, string Books::*memberPtr, bool asc);
    friend ostream& operator<<(ostream& os, const Books &A); 
};

#endif // BOOKS_H