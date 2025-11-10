#ifndef Resources_H
#define Resources_H

#include <iostream>
#include <string.h>
#include "LinkedList.h"
#include "Date.h"

using namespace std;

enum Category{
    BookTextbook,
    BookJournals,
    BookSTEM,
    BookLaw,
    BookPsychologies,
    BookMisc,
    MagazineResearch,
    MagazineReview,
    MagazineStudies,
    MagazineCommentary,
    CatThesis
};

enum ResourceType{
    ResBook,
    ResMagazine,
    ResThesis
};

enum Resourcesreturntypes{
    ResourcestringID = 1,
    ResourcestringName = 2,
    ResourcestringAuth = 3,
    ResourcestringPubl = 4,
    ResourcesintType = 1,
    ResourcesintAvail = 2,
    ResourcesintGenre = 3
};

class Resources{
    protected: 
    string ID;
    string Name;
    string Author; 
    int Type;
    int Genre;
    int TotalAmount;
    int Available;
    public:
    Resources(string ID, string Name, string Author, int Type, int Available, int Total, int Genre):
    ID(ID), Name(Name), Author(Author), Type(Type), TotalAmount(Total), Available(Available), Genre(Genre){};
    virtual ~Resources();
    static auto getStringPtr(int Types){
        switch (Types){
            case ResourcestringID: return &Resources::ID;
            case ResourcestringName: return &Resources::Name;
            case ResourcestringAuth: return &Resources::Author;
        }
    }

    static auto getIntPtr(int Types){
        switch (Types){ 
            case ResourcesintType: return &Resources::Type;
            case ResourcesintAvail: return &Resources::Available;
            case ResourcesintGenre: return &Resources::Genre;
        }
    }

    string getString(int Types){
        switch (Types){
            case ResourcestringID: return ID;
            case ResourcestringName: return Name;
            case ResourcestringAuth: return Author;
            default: return "";
        }
    }

    int getInt(int Types){
        switch (Types){
            case ResourcesintType: return Type;
            case ResourcesintAvail: return Available;
            case ResourcesintGenre: return Genre;
            default: return -1;
        }
    }

    void LendingBook(int Amount){
        Available -= Amount;
    }
    void ReturningBook(int Amount){
        Available += Amount;
    }
    void AddingStockBook(int Amount){
        Available += Amount;
        TotalAmount += Amount;
    }
    virtual void Display() = 0;
    void genericDisplay();
    friend ostream& operator<<(ostream& os, const Resources &A); 
};

class Books: public Resources{
    string Publisher;
    string ISBN;
    public:
    Books(string ID, string Name, string Author,  int Available, int Total, int Genre, string Publish, string ISBN):
    Resources(ID, Name, Author, ResBook, Available, Total, Genre), Publisher(Publish), ISBN(ISBN){};
    void Display() override;
};

class Magazine: public Resources{
    string IssueNum;
    Date IssueDate;
    public:
    Magazine(string ID, string Name, string Author,  int Available, int Total, int Genre, string Num, Date Time):
    Resources(ID, Name, Author, ResMagazine, Available, Total, Genre), IssueNum(Num), IssueDate(Time){};
    void Display() override;
}; 

class Thesis: public Resources{
    string Uni;
    string Visor;
    public:
    Thesis(string ID, string Name, string Author,  int Available, int Total, string Uni, string Visor):
    Resources(ID, Name, Author, ResThesis, Available, Total, CatThesis), Uni(Uni), Visor(Visor){};
    void Display() override;
};

#endif // Resources_H