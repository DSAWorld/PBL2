#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <exception>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <type_traits>

using namespace std;

string truncate(const string& inp, int width){
    if (inp.length() <= width) return inp;
    else return inp.substr(0, width-3) + "...";
}

string StringHelper(int Value){
    if (Value < 10) return "0" + to_string(Value);
    else return to_string(Value);
};

class Date;
class Resources;
class Exceptions;
template<typename Class> class LinkedList;
class Librarian;
class Member;
class Transaction;
class MemberState;
class TranState;

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

enum PtrreturnTypes{
    MemberstringID = 1,
    MemberstringName = 2,
    
    TransstringID = 1,
    TransstringOwner = 2,
    TransstringBookID = 3,
    TransDateBorrowing = 1,
    TransDateDue = 2,
    TransDateReturn = 3,
    
    ResourcestringID = 1,
    ResourcestringName = 2,
    ResourcestringAuth = 3,
    ResourcestringPubl = 4,
    ResourcesintType = 1,
    ResourcesintAvail = 2,
    ResourcesintGenre = 3
};

enum TransStatus{
    Actived,
    Reserved,
    Returned,
    Overdue,
    Cancelled
};

enum MemberStateNum{
    ActiveNum,
    WarnedNum,
    SuspendedNum
};

class Except: public exception{
    protected:
        string MSG;
    public:
        Except(const string &Msg): MSG(Msg){};
        const char* what() const noexcept{
            return MSG.c_str();
        }
};

class ExceptionIDDuplicate: public Except{
    public:ExceptionIDDuplicate(string Type):
        Except("Loi: Da ton tai ID " + Type + " nay trong du lieu, vui long kiem tra lai."){};
};

class ExceptionInvalidUser: public Except{
    public:ExceptionInvalidUser():
        Except("Loi: Thong tin dang nhap khong hop le."){};
};

class ExceptionEmptyList: public Except{
    public:ExceptionEmptyList():
        Except("Loi: Danh sach rong."){};
};

class ExceptionInvalidVal: public Except{
    public:ExceptionInvalidVal(int M):
        Except("Loi: gia tri " + to_string(M) + " khong hop le."){};
};

class ExceptionInvalidHandle: public Except{
    public:ExceptionInvalidHandle():
        Except("Loi: Khong the xu ly yeu cau."){};
};

class ExceptionInvalidRes: public Except{
    public:ExceptionInvalidRes():
        Except("Loi: Loai tai lieu nay khong hop le."){};
};

class ExceptionInvalidChoice: public Except{
    public:ExceptionInvalidChoice():
        Except("Loi: Lua chon khong hop le."){};
};

class ExceptionOutofBound: public Except{
    public:ExceptionOutofBound():
        Except("Loi: Vuot qua pham vi hop le"){};
};

class ExceptionInvalidDate: public Except{
    public:ExceptionInvalidDate():
        Except("Loi: Thoi diem nay khong hop le"){};
};

class ExceptionDontExist: public Except{
    public:ExceptionDontExist():
        Except("Loi: Khong ton tai"){};
};

template<typename Class>
struct BaseType { using type = Class; };

template<typename Class>
struct BaseType<Class*> { using type = Class; };

template <typename Class>
class Node{
public:
    Class data;
    Node* next;
    Node(Class value) : data(value), next(nullptr) {}

    Class* operator ->(){
        if constexpr (is_pointer_v<Class>) return data; else return &data;
    } 
    template <typename Member>
    auto &operator->*(Member (BaseType<Class>::type::*memberPtr)){
        if constexpr (is_pointer_v<Class>) return data->*memberPtr; else return data.*memberPtr;
    }
    void Display(){
        if constexpr (is_pointer_v<Class>) data->Display(); else data.Display();
    }
    // void Header(){
    //     if constexpr (is_pointer_v<Class>) data->Header(); else data.Header();
    // }
    // void Footer(){
    //     if constexpr (is_pointer_v<Class>) data->Footer(); else data.Footer();
    // }
    // void Edit(){
    //     if constexpr (is_pointer_v<Class>) data->Edit(); else data.Edit();
    // }
    void DisplaySingle(){
        if constexpr (is_pointer_v<Class>) data->DisplaySingle(); else data.DisplaySingle();
    }
};

template <typename Class>
class LinkedList{
private:
    Node<Class>* head;
    Node<Class>* tail;
public:
    int Size=0;
    LinkedList():head(nullptr), tail(nullptr){};
    LinkedList(const LinkedList<Class> &other);
    ~LinkedList();
    bool isEmpty(){ return head == nullptr; }
    void Add(Class Data);
    void Pushback(Class Data);
    void display() const;
    void deleteIndex(int index);
    void Swap(Node<Class> *A, Node<Class> *B);
    Node<Class>* operator[](int index);
    template <typename Member> Class *SearchItem(Member (BaseType<Class>::type::*memberPtr), Member Data);
    template <typename Member> LinkedList<Class> SearchMethod(Member (BaseType<Class>::type::*memberPtr), Member Data) const;
    template <typename Member> Node<Class>* Partition(Node<Class>* low, Node<Class>* high, Member (BaseType<Class>::type::*memberPtr), bool &Asc);
    template <typename Member> void Sort(Node<Class>* low, Node<Class>* high, Member (BaseType<Class>::type::*memberPtr), bool &Asc);
    template <typename Member> void SortWrap(Member (BaseType<Class>::type::*memberPtr), int autoSort=0);
};  

class Date{
    public:
    int D, M, Y;
    Date():D(0),M(0),Y(0){};
    Date(int d, int m, int y):D(d), M(m), Y(y){};
    Date(int Conv);
    Date(const Date &Temp);
    ~Date(){};
    int NoofDay();
    bool isValid();
    friend istream &operator >> (istream &in, Date &x);
    friend ostream &operator << (ostream &out, const Date &x);
    int operator - (Date &Sub) const; 
    Date operator + (int Add);
    Date operator - (int Sub);
    bool operator < (Date &Sub); 
    bool operator > (Date &Sub);
    bool operator == (Date &Sub);
    bool emptyDate(){ return (D==0 && M==0 && Y==0); }
    };

extern Date CurrentDate;

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
    Resources(){};
    Resources(string ID, string Name, string Author, int Type, int Available, int Total, int Genre);
    Resources(const Resources &A);
    virtual ~Resources(){};

    static auto getStringPtr(int Types){
        switch (Types){
            case ResourcestringID: return &Resources::ID;
            case ResourcestringName: return &Resources::Name;
            case ResourcestringAuth: return &Resources::Author;
            default: return &Resources::ID; 
        }
    }

    static auto getIntPtr(int Types){
        switch (Types){ 
            case ResourcesintType: return &Resources::Type;
            case ResourcesintAvail: return &Resources::Available;
            case ResourcesintGenre: return &Resources::Genre;
        }
        return &Resources::Type;
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
        if (TotalAmount < Available) TotalAmount = Available;
    }
    void AddingStockBook(int Amount){
        Available += Amount;
        TotalAmount += Amount;
    }
    virtual void DisplaySingle() = 0;
    virtual string toFileString() const = 0;
    void Display();
    static void Header();
    static void Footer();
    virtual int IDExist(string &id, string &isbn){ return (ID == id);}
};

class Books: public Resources{
    string Publisher;
    string ISBN;
    public:
    Books(string ID, string Name, string Author,  int Available, int Total, int Genre, string Publish, string ISBN):
    Resources(ID, Name, Author, ResBook, Available, Total, Genre), Publisher(Publish), ISBN(ISBN){};
    Books(const Books &A);
    void DisplaySingle() override;
    int IDExist(string &id, string &isbn) override{
        if (ISBN == isbn) return 2;
        return (ID == id);
    }
    static void newItem(LinkedList<Resources*>* BooksList = nullptr);
    string toFileString() const override;
    friend string Quoting(const string &inp);
};

class Magazine: public Resources{
    string IssueNum;
    Date IssueDate;
    public:
    Magazine(string ID, string Name, string Author, int Available, int Total, int Genre, string Num, Date Time):
    Resources(ID, Name, Author, ResMagazine, Available, Total, Genre), IssueNum(Num), IssueDate(Time){};
    Magazine(const Magazine &A);
    void DisplaySingle() override;
    static void newItem(LinkedList<Resources*>* BooksList = nullptr);
    string toFileString() const override;
}; 

class Thesis: public Resources{
    string Uni;
    string Visor;
    public:
    Thesis(string ID, string Name, string Author, int Available, int Total, int Genre, string Uni, string Visor):
    Resources(ID, Name, Author, ResThesis, Available, Total, CatThesis), Uni(Uni), Visor(Visor){};
    Thesis(const Thesis &A);
    void DisplaySingle() override;
    static void newItem(LinkedList<Resources*>* BooksList = nullptr);
    string toFileString() const override;
};

class Librarian {
private:
    string Name;
    string ID;
    string Contact;
    string Password;
public:
    Librarian(string NameInp, string IDInp, string ContactInp, string PasswordInp = "admin");
    Librarian(const Librarian &A);
    Librarian();
    Librarian(const string& str);
    ~Librarian();
    bool verifyPassword(const string& inputPassword) const;
    bool login(const string& inputID, const string& inputPassword) const;
    friend Librarian* login(LinkedList<Librarian>& librarianList);
    void changePassword(const string& newPassword);
    friend ostream& operator<<(ostream& os, const Librarian &A);
    string toFileString() const;
    static void Header(){};
    static void Footer(){};
    void Display();
};

class Member{
    protected:
    string ID;
    string Name;
    string Contact;
    string *Hist; //List of Previous Transactions
    string *TransactionID; //List of Current, not turned in Transactions
    MemberState *CurrState;
    Date LastVio;
    int State;
    public:
    bool fromSuspended;
    int HistSize = 0;
    int TransSize = 0;
    Member() : Hist(nullptr), TransactionID(nullptr), CurrState(nullptr), State(0), HistSize(0), TransSize(0) {};;
    Member(string ID, string Name, string Contact, int State, int HistSize, int TransSize, Date Vio, string* Hist, string* Trans, bool hardpun);
    Member(string NameInp, string ContactInp, string studentID);
    Member(const Member &other);
    static Member *newMember(LinkedList<Member>& allMembers);
    ~Member();
    void Edit();
    void AddTrans(string TransID);
    void Returning(string TransID);
    void ReconstructList(LinkedList<Transaction>& AllTrans, int RecHist = 0);
    void SetState(MemberState *newState);
    void ChangeState(bool Punish, Member *member);
    void ChangeVio();
    string* getList(bool HistorTrans){
        return (HistorTrans) ? Hist : TransactionID;
    }
    static auto getStringPtr(int Types){
        switch (Types){
        case MemberstringID: return &Member::ID; 
        case MemberstringName: return &Member::Name;
        }
        return &Member::ID;
    };

    static auto getIntPtr(){
        return &Member::State;
    }

    string getString(int Types){
        switch (Types){
        case MemberstringID: return ID; 
        case MemberstringName: return Name;
        default: return "";
        }
    }
    void Cancelling(string ID);
    void DisplayList(int Num = 0, bool Hist = 0);
    void Display();
    void DisplaySingle();
    static void Header();
    static void Footer();
    int StatusCheck(){
        return State;
    }
    string toFileString() const;
    void Checkup();
    static string Grouping(const string inp[], int size);
    friend string Quoting(const string &inp);
    Member& operator=(const Member& other);
};

class MemberState{
    public:
    virtual ~MemberState(){};
    virtual void Sparing(Member *member) = 0;
    virtual void Punish(Member *member) = 0;
    virtual int  getState() = 0;
};

class Active: public MemberState{
    void Sparing(Member *member) override {}
    void Punish(Member *member) override;
    int getState() override;
};

class Warned: public MemberState{
    void Sparing(Member *member) override;
    void Punish(Member *member) override;
    int getState() override;
};

class Suspended: public MemberState{
    void Sparing(Member *member) override;
    void Punish(Member *member) override;
    int getState() override;
};

 struct Items{
    string BookID;
    unsigned int Amount;
    friend ostream& operator<<(ostream& out, const Items& item) {
        out << item.BookID << " x" << item.Amount;
        return out;
    }
};

class Transaction{
    string ID;
    string OwnerID;
    Items *List;
    Date Borrowing;
    Date Due;
    Date ReturnDate;
    TranState *State;
    int Status;
    public:
    unsigned int NumberofItems = 0;
    unsigned int ItemCount = 0;
    ~Transaction();
    Transaction(string ID, string OwnerID, int NumberofItems, int ItemCount, Date Borrowing, Date Due, Date Return, int Status, Items* List);
    Transaction(string Owner, bool Res, int borrowingdays, Items *ItemList, int Number, LinkedList<Resources*>* BooksList);
    Transaction(const Transaction &other);
    static string IDHelper(long);
    void CreateBookList(LinkedList<Resources*>* BooksList);
    void ReturnBooks(LinkedList<Resources*>* BooksList);
    void Checkup(LinkedList<Resources*>* Library);
    void Revalidate();
    void HandlingStates(int StateChange, int BorrowingDays = 7);
    void setState(TranState* newState);
    string getID(bool Types = 0){ 
        if (Types) return ID; 
        else return OwnerID;
     };
    static auto getDatePtr(int Types){
        switch (Types){
        case TransDateBorrowing: return &Transaction::Borrowing; 
        case TransDateDue: return &Transaction::Due;
        case TransDateReturn: return &Transaction::ReturnDate;
        }
        return &Transaction::Borrowing;
    };
    static auto getStringPtr(int Types){
        switch(Types){
            case TransstringID: return &Transaction::ID;
            case TransstringOwner: return &Transaction::OwnerID;
        }
        return &Transaction::ID;
    };
    static auto getStatePtr(){ return &Transaction::Status;}
    int GetStatus(){ return Status; }
    void Display();
    static void Header();
    static void Footer();
    void DisplaySingle();
    string toFileString() const;
    friend string Quoting(const string &inp);
    static string Grouping(const Items inp[], int size);
    void ReconstructBookList(LinkedList<Resources*>& List);
    Transaction& operator=(const Transaction& other);
};

class TranState{
    public:
        virtual ~TranState(){};
        virtual void handle(Transaction *Trans){};
        virtual void handleAlt(Transaction *Trans){
            throw ExceptionInvalidHandle();
        }
        virtual int getState() = 0;
};


class ActiveState: public TranState{
    public:
        int getState() override{
            return Actived;
        }
        void handle(Transaction *Trans) override;
        void handleAlt(Transaction *Trans) override;
};

class LateState: public TranState{
    public:
        int getState() override{
            return Overdue;
        }
        void handle(Transaction *Trans) override;
};

class ReserveState: public TranState{
    public:
        int getState() override{
            return Reserved;
        }
        void handle(Transaction *Trans) override;
        void handleAlt(Transaction *Trans) override;
};

class ReturnState: public TranState{
    public:
        int getState() override{
            return Returned;
        }
        void handle(Transaction *Trans) override {};
};

class CancelState: public TranState{
    public:
        int getState() override{
            return Cancelled;
        }
        void handle(Transaction *Trans) override {};
};

class FileHandler{
    private:        
        static string getField(stringstream &ss);
        static Date getDateField(const string &Str);
        static string* getstringArrField(string &ss, int &size);
        static Items* getItemsArrField(string &ss, int &ItemNum, int &ItemCount);

        static Librarian* createLib(string &line);
        static Resources* createRes(string &line);
        static Member* createMem(string &line);
        static Transaction* createTrans(string &line);

    public:
        template <typename Class>
        static void SaveFile(const string &filename, LinkedList<Class> &list);
        static void LoadResources(const string &filename, LinkedList<Resources*> &list);
        static void LoadMembers(const string &filename, LinkedList<Member> &list);
        static void LoadTransactions(const string &filename, LinkedList<Transaction> &list);
        static void LoadLibrarian(const string &filename, LinkedList<Librarian> &list);
    };

#endif // HEADER_H