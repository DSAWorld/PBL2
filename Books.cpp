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
<<<<<<< Updated upstream
    string Name;
    string Author;
    string Publisher;
    enum Category genre;
=======
    enum Category genre; 
>>>>>>> Stashed changes
    unsigned int TotalAmount;
    unsigned int Available;
    public:
    
};

#endif // BOOKS_H