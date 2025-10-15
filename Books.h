#ifndef BOOKS_H
#define BOOKS_H

#include <iostream>
#include <string.h>
<<<<<<< Updated upstream
=======
#include "LinkedList.h"
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
=======
    OldThesis,
>>>>>>> Stashed changes
    Misc
};

class Books{
    private: 
<<<<<<< Updated upstream
    string ID;
    string Name;
    string Author;
    string Publisher;
=======
    string ID; //ISBN-[Edition]
    string Name; //50
    string Author; //30
    string Publisher; //30
>>>>>>> Stashed changes
    enum Category genre;
    unsigned int TotalAmount;
    unsigned int Available;
    public:
    
<<<<<<< Updated upstream
=======
    friend bool LinkedList<Books>::Comp(const Books& A, const Books& B, int Books::*memberPtr, bool asc);
    friend bool LinkedList<Books>::Comp(const Books& A, const Books& B, string Books::*memberPtr, bool asc);
>>>>>>> Stashed changes
};

#endif // BOOKS_H