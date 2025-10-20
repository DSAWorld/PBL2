#ifndef BOOKS_H
#define BOOKS_H

#include <iostream>
#include <string.h>

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
    Misc
};

class Books{
    private: 
    string ID;
    enum Category genre; 
    unsigned int TotalAmount;
    unsigned int Available;
    public:
    
};

#endif // BOOKS_H