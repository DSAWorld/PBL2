#include "Header.h"

Resources::Resources(string ID, string Name, string Author, int Type, int Available, int Total, int Genre){
    this->ID = ID;
    this->Name = Name;
    this->Author = Author;
    this->Type = Type;
    this->TotalAmount = Total;
    this->Available = Available;
    this->Genre = Genre;
}

Resources::Resources(const Resources &A){
    this->ID = A.ID;
    this->Name = A.Name;
    this->Author = A.Author;
    this->Type = A.Type;
    this->TotalAmount = A.TotalAmount;
    this->Available = A.Available;
    this->Genre = A.Genre;
}

Books::Books(const Books &A):Resources(A){
    this->Publisher = A.Publisher;
    this->ISBN = A.ISBN;
}

Magazine::Magazine(const Magazine &A):Resources(A){
    this->IssueNum = A.IssueNum;
    this->IssueDate = A.IssueDate;
}

Thesis::Thesis(const Thesis &A):Resources(A){
    this->Uni = A.Uni;
    this->Visor = A.Visor;
}

string GenreHelper(int Genre){
    switch(Genre){
        case BookTextbook:      return "Giao trinh";
        case BookJournals:      return "Tap san chuyen nganh";
        case BookSTEM:          return "Khoa hoc & Ky thuat (STEM)";
        case BookLaw:           return "Phap luat";
        case BookPsychologies:  return "Tam ly, chinh tri, tu tuong";
        case BookMisc:          return "Tong hop / Khac";
        
        case MagazineResearch:  return "Tap chi nghien cuu";
        case MagazineReview:    return "Tap chi phe binh";
        case MagazineStudies:   return "Tap chi chuyen khao";
        case MagazineCommentary:return "Tap chi binh luan";
    }
    return "Tai lieu khac";
}

void Books::DisplaySingle(){
    cout<<"[Sach]"
        <<"\nID: "<<ID
        <<"\nTen sach: "<<Name
        <<"\nTac gia: "<<Author
        <<"\nNha xuat ban: "<<Publisher
        <<"\nISBN: "<<ISBN
        <<"\nThe loai: "<<GenreHelper(Genre)
        <<"\nTong so luong: "<<TotalAmount
        <<"\nSo luong hien co: "<<Available<<endl;
}

void Magazine::DisplaySingle(){
    cout<<"[Tap chi]"
        <<"\nID: "<<ID
        <<"\nTen tap chi: "<<Name
        <<"\nTac gia: "<<Author
        <<"\nSo phat hanh: "<<IssueNum
        <<"\nNgay phat hanh: "<<IssueDate
        <<"\nThe loai: "<<GenreHelper(Genre)
        <<"\nTong so luong: "<<TotalAmount
        <<"\nSo luong hien co: "<<Available<<endl;
}

void Thesis::DisplaySingle(){
    cout<<"[Luan van]"
        <<"\nID: "<<ID
        <<"\nTen luan van: "<<Name
        <<"\nTac gia: "<<Author
        <<"\nTruong dai hoc: "<<Uni
        <<"\nGiao vien huong dan: "<<Visor
        <<"\nThe loai: Luan van"
        <<"\nTong so luong: "<<TotalAmount
        <<"\nSo luong hien co: "<<Available<<endl;
}

void Books::newItem(LinkedList<Resources*>* BooksList){
    string ID, Name, Author, Publisher, ISBN;
    int Available, Total, Genre;
    cout<<"Nhap ID sach: ";
    cin>>ID;
    cout<<"Nhap ISBN: ";
    cin>>ISBN;
    Node<Resources*>* start = (*BooksList)[1];
    int tempTest;
    while (start != nullptr){
        Resources* existing = start->data;
        tempTest = existing->IDExist(ID, ISBN);
        if (tempTest == 1){
            throw ExceptionIDDuplicate("tai nguyen");
        }
        else if (tempTest == 2){
            cout<<"\nPhat hien ISBN trung lap:";
            existing->Display();
            cout<<"Nhap tong so luong sach nhap, nhap 0 de huy: ";
            cin>>Total;
            while(Total < 0){
                cout<<"\nSo luong khong hop le, vui long nhap lai: ";
                cin>>Total;
            }
            existing->AddingStockBook(Total);
            if (Total == 0){
                cout<<"\nDa huy cap nhat.";
                return;
            }
            cout<<"\nDa cap nhat so luong sach.";
            return;
        }
        start = start->next;
    }
    cin.ignore();
    cout<<"Nhap ten sach: ";
    getline(cin, Name);
    cout<<"Nhap tac gia: ";
    getline(cin, Author);
    cout<<"Nhap nha xuat ban: ";
    getline(cin, Publisher);
    cout<<"Nhap tong so luong sach nhap: ";
    cin>>Total;
    BooksList->Add(new Books(ID, Name, Author, Total, Total, Genre, Publisher, ISBN));
}

void Magazine::newItem(LinkedList<Resources*>* BooksList){
    string ID, Name, Author, IssueNum;
    int Available, Total, Genre;
    Date IssueDate;
    cout<<"Nhap ID tap chi: ";
    cin>>ID;
    Node<Resources*>* start = (*BooksList)[1];
    int tempTest;
    while (start != nullptr){
        Resources* existing = start->data;
        tempTest =existing->IDExist(ID, ID);
        if (tempTest == 1){
            throw ExceptionIDDuplicate("tai nguyen");
        }
        start = start->next;
    }
    cin.ignore();
    cout<<"Nhap tieu de tap chi: ";
    getline(cin, Name);
    cout<<"Nhap tac gia: ";
    getline(cin, Author);
    cout<<"Nhap so phat hanh: ";
    getline(cin, IssueNum);
    cout<<"Nhap ngay phat hanh (dd/mm/yyyy): ";
    cin>>IssueDate;
    if (!IssueDate.isValid() || IssueDate < CurrentDate) throw ExceptionInvalidDate();
    cout<<"Nhap tong so luong tap chi nhap: ";
    cin>>Total;
    BooksList->Add(new Magazine(ID, Name, Author, Total, Total, Genre, IssueNum, IssueDate));
}

void Thesis::newItem(LinkedList<Resources*>* BooksList){
    string ID, Name, Author, Uni, Visor;
    int Available, Total, Genre;
    cout<<"Nhap ID luan van: ";
    cin>>ID;
    Node<Resources*>* start = (*BooksList)[1];
    int tempTest;
    while (start != nullptr){
        Resources* existing = start->data;
        tempTest = existing->IDExist(ID, ID);
        if (tempTest == 1){
            throw ExceptionIDDuplicate("tai nguyen");
        }
        start = start->next;
    }
    cin.ignore();
    cout<<"Nhap ten luan van: ";
    getline(cin, Name);
    cout<<"Nhap tac gia: ";
    getline(cin, Author);
    cout<<"Nhap truong dai hoc: ";
    getline(cin, Uni);
    cout<<"Nhap giao vien huong dan: ";
    getline(cin, Visor);
    cout<<"Nhap tong so ban luan van: ";
    cin>>Total;
    BooksList->Add(new Thesis(ID, Name, Author, Total, Total, Genre, Uni, Visor));
}

void Resources::Display(){
    cout<<"|  "<<ID<<"  "
        <<"| "<<left<<setw(40)<<setfill(' ')<<truncate(Name, 40)<<" "
        <<"| "<<left<<setw(30)<<setfill(' ')<<truncate(Author, 30)<<" "
        <<"|";
    switch (Type){
        case ResBook: cout<<"   Sach    "; break;
        case ResMagazine: cout<<"  Tap chi  "; break;
        case ResThesis: cout<<" Luan van  "; break;
    };
    cout<<"| "<<right<<setw(3)<<setfill('0')<<Available<<" / "<<setw(3)<<setfill('0')<<TotalAmount<<"  |\n";
}

void Resources::Header(){
    cout<<"|====================================================================================================================|\n"
        <<"| STT | MA SACH |               TEN TAI LIEU               |          TEN TAC GIA           | LOAI SACH |  SO LUONG  |\n"
        <<"|====================================================================================================================|\n";
}

void Resources::Footer(){
    cout<<"|====================================================================================================================|\n";
}

Date::Date(int ConvVal){
    int TimeVal = (ConvVal+25200) / 86400;
    Date UnitTime(1,1,1970);
    *this = UnitTime + TimeVal;
}

Date::Date(const Date &A):D(A.D), M(A.M), Y(A.Y){}

int Date::NoofDay(){
    const int Mon[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (M == 2 && ((Y % 4 == 0 && Y % 100 !=0) || Y % 400 == 0)) return 29;
    else return Mon[M-1];
}

bool Date::isValid(){
    return !( D < 1 || M < 1 || M > 12 || D > NoofDay() );
}
Date Date::operator + (int Add) {
    Date NewDate = *this;
    NewDate.D += Add;
    int Temp = NewDate.NoofDay();
    while (NewDate.D > Temp){
        NewDate.M++;
        NewDate.D -= Temp;
        if(NewDate.M == 13){
            NewDate.Y++;
            NewDate.M = 1;
        }
        Temp = NewDate.NoofDay();
    }
    return NewDate;
}

Date Date::operator - (int Sub){
    Date NewDate = *this;
    NewDate.D -= Sub;
    while (NewDate.D < 1){
        NewDate.M--;
        if(NewDate.M == 0){
            NewDate.Y--;
            NewDate.M = 12;
        }
        NewDate.D += NewDate.NoofDay();
    }
    return NewDate;
}

int Date::operator - (Date &Sub) const {
    const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int days1 = Y * 365 + D;
    for (int i = 0; i < M - 1; i++){
        days1 += monthDays[i];
    };
    days1 += (Y / 4) - (Y / 100) + (Y / 400);
    int days2 = Sub.Y * 365 + Sub.D;
    for (int i = 0; i < Sub.M - 1; i++){
        days2 += monthDays[i];
    };
    days2 += (Sub.Y / 4) - (Sub.Y / 100) + (Sub.Y / 400);
    return days1 - days2;
}

bool Date::operator < (Date &Sub){
    return *this-Sub<=0;
}

bool Date::operator > (Date &Sub){
    return !(*this < Sub);
}

bool Date::operator == (Date &Sub){
    return (D == Sub.D && M == Sub.M && Y == Sub.Y);
}

istream& operator>>(istream& in, Date& x)
{
    string input;
    if (!getline(in, input)) return in;
    auto trim = [](string &s){
        while(!s.empty() && isspace(s.front())) s.erase(s.begin());
        while(!s.empty() && isspace(s.back()))  s.pop_back();
    };
    trim(input);
    if (input.empty()) {
        x.D = x.M = x.Y = 0;
        return in;
    }
    char sep1 = 0, sep2 = 0;
    int d = 0, m = 0, y = 0;

    stringstream ss(input);
    if ((ss >> d >> sep1 >> m >> sep2 >> y) && (sep1 == '/' || sep1 == '-') && (sep2 == '/' || sep2 == '-'))
    {
        x.D = d;
        x.M = m;
        x.Y = y;
        if (!x.isValid()) {
            x.D = x.M = x.Y = 0;
        }
        return in;
    }
    x.D = x.M = x.Y = 0;
    return in;
}

ostream &operator <<(ostream &out, const Date &x){
    out<<StringHelper(x.D)<<"/"<<StringHelper(x.M)<<"/"<<x.Y;
    return out;
};

Librarian::Librarian(string NameInp, string IDInp, string ContactInp, string PasswordInp)
    : Name(NameInp), ID(IDInp), Contact(ContactInp), Password(PasswordInp) {}

Librarian::Librarian(const Librarian &A)
    : Name(A.Name), ID(A.ID), Contact(A.Contact), Password(A.Password) {}

Librarian::Librarian() : Name(""), ID(""), Contact(""), Password("admin") {}

Librarian::Librarian(const string &str) {
    stringstream ss(str);
    getline(ss, Name, ',');
    getline(ss, ID, ',');
    getline(ss, Contact, ',');
    getline(ss, Password, ',');
}

Librarian::~Librarian() {}

bool Librarian::verifyPassword(const string& inputPassword) const {
    return Password == inputPassword;
}

bool Librarian::login(const string& inputID, const string& inputPassword) const {
    return (ID == inputID) && verifyPassword(inputPassword);
}

Librarian* login(LinkedList<Librarian>& librarianList) {
    string inputID, inputPassword;
    cout << "\n===================================";
    cout << "\n           DANG NHAP              ";
    cout << "\n===================================";
    cout << "\nNhap ID: ";
    getline(cin, inputID);
    cout << "Nhap Password: ";
    getline(cin, inputPassword);
    
    Node<Librarian>* current = librarianList[1];
    while (current != nullptr) {
        if (current->data.login(inputID, inputPassword)) {
            cout << "\nDang nhap thanh cong. Xin chao, " << current->data.Name << "!" << endl;
            return &(current->data); 
        }
        current = current->next;
    }
    cout << "\nDang nhap that bai. ID hoac Password sai." << endl;
    return nullptr;
}

// Librarian Librarian::newLibrarian() {
//     string name, id, contact;
//     cout << "Enter Name: ";
//     getline(cin, name);
//     cout << "Enter ID: ";
//     getline(cin, id);
//     cout << "Enter Contact: ";
//     getline(cin, contact);
//     return Librarian(name, id, contact);
// }

void Librarian::changePassword(const string& newPassword) {
    Password = newPassword;
}

ostream& operator<<(ostream& os, const Librarian &A) {
    os << "Librarian Name: " << A.Name << "\nID: " << A.ID << "\nContact: " << A.Contact;
    return os;
}

void Librarian::Display(){
    cout<< Name <<" "<< ID <<" "<< Password;
}

template <typename Class> LinkedList<Class>::LinkedList(const LinkedList<Class> &other):head(nullptr), tail(nullptr){
        if (!other.head) return;
        Node<Class> *currentOther = other.head;
        while (currentOther)
        {
            this->Add(currentOther->data);
            currentOther = currentOther->next;
        }
    };

template <typename Class>
void LinkedList<Class>::Add(Class Data){
    Node<Class> *newNode = new Node<Class>(Data);
    if (head == nullptr){
        head = newNode;
        tail = head;
        Size++;
    }
    else {
        tail->next = newNode;
        tail = newNode;
        Size++;
    }
}

template <typename Class>
void LinkedList<Class>::Pushback(Class Data){
    Node<Class> *newNode = new Node<Class>(Data);
    if (head == nullptr){
        head = newNode;
        tail = head;
        Size++;
    } else {
        newNode -> next = head;
        head = newNode;
        Size++;
    }
}

template <typename Class>
LinkedList<Class>::~LinkedList(){
    Node<Class> *temp = head;
    while (temp != nullptr){
        Node<Class> *next = temp->next;
        if constexpr (is_pointer_v<Class>) {
            delete temp->data;
        }
        delete temp;
        temp = next;
    }
    head = nullptr;
    tail = nullptr;
}

template <typename Class> 
void LinkedList<Class>::deleteIndex(int index) {
    if (head == nullptr) {
        throw ExceptionEmptyList();
        return;
    }
    if (index < 1) {
        throw ExceptionInvalidVal(index);
        return;
    }
    Node<Class> *current = head;
    Node<Class> *prev = nullptr;
    if (index == 1) {
        head = head->next;
        if (head == nullptr) tail = nullptr;
        if constexpr (is_pointer_v<Class>) {
            delete current->data;
        }
        delete current;
        return;
    }
    int count = 1;
    while (current != nullptr && count < index) {
        prev = current;
        current = current->next;
        count++;
    }
    if (current == nullptr) {
        throw ExceptionOutofBound();
    }
    prev->next = current->next;
    if (current == tail) tail = prev;
    if constexpr (is_pointer_v<Class>) {
            delete current->data;
        }
    delete current;
    Size--;
}

template <typename Class> void LinkedList<Class>::display() const {
    Node<Class> *temp = head;
    if (!temp) {
        throw ExceptionEmptyList();
    }
    system("cls");
    BaseType<Class>::type::Header();
    int Indexing = 1;
    while (temp)
    {
        cout<<"| "<<right<<setw(3)<<setfill('0')<<Indexing++<<" ";
        temp->Display();
        temp = temp->next;
    }
    BaseType<Class>::type::Footer();
};

template <typename Class>
template <typename Member> 
LinkedList<Class> LinkedList<Class>::SearchMethod(Member (BaseType<Class>::type::*memberPtr), Member Data) const {
    LinkedList<Class> Result;
    Node<Class> *Curr = head;
    while (Curr != nullptr){
        if((*Curr)->*memberPtr == Data){
            if constexpr (is_pointer_v<Class>) {
                Result.Add(new typename BaseType<Class>::type(*(Curr->data)));
            } else {
                Result.Add(Curr->data);
            }
        }
        Curr = Curr->next;
    }
    return Result;
};
template <typename Class>
void LinkedList<Class>::Swap(Node<Class>* A, Node<Class>* B) {
    Class Temp = A->data;
    A->data = B->data;
    B->data = Temp;
}

template <typename Class>
template <typename Member>
Node<Class>* LinkedList<Class>::Partition(Node<Class>* low, Node<Class>* high, Member (BaseType<Class>::type::*memberPtr), bool &Asc) {
    if (!low || !high) return low; // defensive
    Member pivotVal = (*high)->*memberPtr;
    Node<Class>* i = low;
    Node<Class>* j = low;
    while (j != high) {
        if (Asc ? ((*j)->*memberPtr < pivotVal) : ((*j)->*memberPtr > pivotVal)) {
            Swap(i, j);
            i = i->next;
        }
        j = j->next;
    }
    Swap(i, high);
    return i;
}

template <typename Class>
template <typename Member>
void LinkedList<Class>::Sort(Node<Class>* low, Node<Class>* high, Member (BaseType<Class>::type::*memberPtr), bool &Asc){
    if (!low || !high || low == high || low == high->next) return;
    Node<Class> *Point = Partition(low, high, memberPtr, Asc);
    if (Point != high) {
        Sort(low, Point, memberPtr, Asc); 
    } 
    else {
        Node<Class>* current = low;
        while (current->next != high && current != high) {
            current = current->next;
        }
        if (current != high) {
            Sort(low, current, memberPtr, Asc);
        }
    }
    Sort(Point->next, high, memberPtr, Asc);
}

template <typename Class>
template <typename Member> 
void LinkedList<Class>::SortWrap(Member (BaseType<Class>::type::*memberPtr), int autoSort){
    if(head == nullptr){
        throw ExceptionEmptyList();
    }
    if(head->next == nullptr){
        return;
    }
    int Choice = -1;
    if (autoSort){
        bool Asc = true;
        Sort(head, tail, memberPtr, Asc);
        return;
    }
    bool Asc;
    cout<<"\nNhap lua chon:"
        <<"\n[0] Khong sap xep"
        <<"\n[1] Tang dan"
        <<"\n[2] Giam dan"
        <<"\nLua chon: ";
    while(true){
        cin>>Choice;
        if (Choice == 0) return;
        if (Choice == 1 || Choice == 2) {
            if (Choice == 1) Asc = 1;
            else Asc = 0;
            break;
        };
    }
    Sort(head, tail, memberPtr, Asc);
}

template <typename Class>
template <typename Member>
Class *LinkedList<Class>::SearchItem(Member (BaseType<Class>::type::*memberPtr), Member Data){
    Node<Class> *current = head;
    while (current != nullptr){
        if((*current)->*memberPtr == Data) return &(current->data);
        current = current->next;
    }
    return nullptr;
}

template <typename Class>
Node<Class>* LinkedList<Class>::operator[](int index){
    if (index < 1) return nullptr;
    int i = index-1;
    Node<Class> *current = head;
    while (i && current){
        current = current -> next;
        i--;
    }
    if (!current) return nullptr;
    return current;
}

Member::Member(string NameInp, string ContactInp, string InpID) {
    Name = NameInp;
    Contact = ContactInp;
    ID = InpID;
    LastVio = Date(0,0,0);
    CurrState = new Active();
    State = CurrState->getState();
    Hist = nullptr;
    TransactionID = nullptr;
}

Member::~Member(){
    delete [] Hist;
    delete [] TransactionID;
    delete CurrState;
}

Member::Member(const Member &other){
    ID = other.ID;
    Name = other.Name;
    Contact = other.Contact;
    LastVio = other.LastVio;
    HistSize = other.HistSize;
    TransSize = other.TransSize;
    fromSuspended = other.fromSuspended;
    if (other.Hist && HistSize > 0) {
        Hist = new string[HistSize];
        for (int i = 0; i < HistSize; i++) {
            Hist[i] = other.Hist[i];
        }
    } else {
        Hist = nullptr;
    }
    if (other.TransactionID && TransSize > 0) {
        TransactionID = new string[TransSize];
        for (int i = 0; i < TransSize; i++) {
            TransactionID[i] = other.TransactionID[i];
        }
    } else {
        TransactionID = nullptr;
    }
    State = other.CurrState->getState();
    switch(State){
        case ActiveNum: this->CurrState = new Active(); break;
        case WarnedNum: this->CurrState = new Warned(); break;
        case SuspendedNum: this->CurrState = new Suspended(); break;
        default: this->CurrState = new Active();
    }
}

void Member::Checkup(){
    int Value = CurrState->getState();
    switch (Value){
        case ActiveNum: fromSuspended = 0; return;
        case WarnedNum:{
            int AddingDays = (fromSuspended) ? 21 : 7;
            if ((LastVio + AddingDays) < CurrentDate)
            CurrState->Sparing(this);
        }
        case SuspendedNum:{
            fromSuspended = 1;
            if ((LastVio + 21) < CurrentDate){
            LastVio = LastVio + 21;
            CurrState->Sparing(this);
            }
        }
    }
}

Member* Member::newMember(LinkedList<Member>& allMembers){
    int n = 0;
    string TempID;
    cout<<"Nhap loai thanh thanh vien\n"
        <<"[1] Sinh vien\n"
        <<"[2] Tu do\n";
        cin>>n;
        cin.ignore(9999, '\n');
    switch(n){
        case 1: {
            cout<<"Nhap so the sinh vien cho ID thu vien: ";
            string SVID;
            cin>>SVID;
            TempID = "SV-" + SVID;
            cin.get();
            if (allMembers.SearchItem(&Member::ID, TempID) != nullptr) throw ExceptionIDDuplicate("sinh vien");
            break;
            }
        case 2: {
            do{
            srand(time(NULL));
            int RandNum = rand()*rand() % 90000001 + 9999999;
            TempID = "ID-" + to_string(RandNum);
            LinkedList<Member> existing = allMembers.SearchMethod(&Member::ID, TempID);
            } while (allMembers.SearchItem(&Member::ID, TempID) != nullptr);
            cout<<"\nID: "<<TempID;
            cin.get();
            break;
        }
    }
    string NameInp, ContactInp;
    cout<<"\nNhap Ho va Ten: ";
    getline(cin, NameInp);
    cout<<"\nNhap thong tin lien he: ";
    getline(cin, ContactInp);
    Member* newMember = new Member(NameInp, ContactInp, TempID);
    cout << "Da hoan thanh thu tuc dang ky";
    getchar();
    return newMember;
}

void Member::ChangeVio(){
    LastVio = CurrentDate;
}

void Member::SetState(MemberState *newState){
        if (CurrState) delete CurrState;
        CurrState = newState;
        State = CurrState->getState();
}

void Member::ChangeState(bool Punish, Member *member){
    if (Punish) member->CurrState->Punish(member);
    else member->CurrState->Sparing(member);
}

void Active::Punish(Member *member) {
    member->ChangeVio();
    member->SetState(new Warned());
}

void Warned::Sparing(Member *member){
    member->SetState(new Active());
}

void Warned::Punish(Member *member){
    member->ChangeVio();
    member->SetState(new Suspended());
}

void Suspended::Sparing(Member *member){
    member->SetState(new Warned());
    member->fromSuspended = true;
}

void Suspended::Punish(Member *member){
    member->ChangeVio();
}

int Active::getState(){
    return 0;
}

int Warned::getState(){
    return 1;
}

int Suspended::getState(){
    return 2;
}

void Member::Edit(){
    cout<<"===========================================\n"
        <<"\nChinh sua thong tin thanh vien "<<ID<<": "
        <<"[1] Ten thanh vien\n"
        <<"[2] Thong tin lien he\n"
        <<"===========================================\n";
    int n = -1;
    cin>>n;
    switch(n){
        case 1: {
            cout<<"\nNhap ten thanh vien moi: ";
            string NewName;
            cin>>NewName;
            Name = NewName;
            cout<<"\nDa cap nhat ten thanh vien.";
            break;
        }
        case 2: {
            cout<<"\nNhap thong tin lien he moi: ";
            string NewContact;
            cin>>NewContact;
            Contact = NewContact;
            cout<<"\nDa cap nhat thong tin lien he.";
            break;
        }
        default: {
            cout<<"\nLua chon khong hop le.";
            break;
        }
    }
}

void Member::AddTrans(string TransID){
    string *NewList = new string[TransSize + 1];
    for (int i = 0; i < TransSize; i++){
        NewList[i] = TransactionID[i];
    }
    NewList[TransSize] = TransID;
    delete [] TransactionID;
    TransactionID = NewList;
    TransSize++;
}

void Member::Cancelling(string TransID){
    if (TransSize <= 0 || TransactionID == nullptr) return;
    int index = -1;
    for (int i = 0; i < TransSize; i++) {
        if (TransactionID[i] == TransID) {
            index = i;
            break;
        }
    }
    if (index == -1) throw ExceptionDontExist();
    string *NewList = nullptr;
    if (TransSize - 1 > 0) {
        NewList = new string[TransSize - 1];
        int k = 0;
        for (int i = 0; i < TransSize; i++) {
            if (i == index) continue;
            NewList[k++] = TransactionID[i];
        }
    }
    delete [] TransactionID;
    TransactionID = NewList;
    TransSize--;
}

void Member::Returning(string TransID){
    int Ind = -1;
    for (int i = 0; i < TransSize; i++){
        if (TransactionID[i] == TransID){
            Ind = i;
            break;
        }
    }
    if (Ind == -1) return;
    string *NewList = new string[HistSize + 1];
    for (int i = 0; i < HistSize; i++){
        NewList[i] = Hist[i];
    }
    NewList[HistSize] = TransID;
    delete [] Hist;
    Hist = NewList;
    HistSize++;
    string *NewTransList = new string[TransSize - 1];
    for(int i = 0, j = 0; i < TransSize; i++){
        if (i != Ind){
            NewTransList[j++] = TransactionID[i];
        }
    }
    delete [] TransactionID;
    TransactionID = NewTransList;
    TransSize--;
}

void Member::ReconstructList(LinkedList<Transaction>& AllTrans, int RecHist){
    int TotalSize = (RecHist) ? HistSize : TransSize;
    if (AllTrans.isEmpty()){
        throw ExceptionEmptyList();
        getchar();
        return;
    };
    if (TotalSize == 0){
        cout<<"\nKhong co giao dich nao de hien thi";
        getchar();
        return;
    };
    LinkedList<Transaction> tempTrans=AllTrans.SearchMethod(Transaction::getStringPtr(TransstringID), ID);
    if (tempTrans.isEmpty()){
        cout<<"\nKhong tim thay bat ky giao dich nao";
        getchar();
        return;
    }
    string Temp = (RecHist) ? "da tra" : "dang muon";
    while (1){
    cout<<"\nCac giao dich "<< Temp <<" cua thanh vien "<<ID<<":\n";
    tempTrans.display();
    int ind = 0;
    cout<<"\nNhap so thu tu giao dich can xem chi tiet, nhap 0 de thoat: ";
    cin>>ind;
    if (ind == 0) return;
    if (ind < 1 || ind > tempTrans.Size){
        cout<<"\nKhong hop le, vui long thu lai.";
        cin.get();
        continue;
    }
    Node<Transaction>* item = tempTrans[ind];
    item->DisplaySingle();
    }
    getchar();
}

void Member::Header(){
    cout<<"|=================================================================================|\n"
        <<"| STT |  MA SO THE  |         TEN THANH VIEN         |   LIEN LAC    | TRANG THAI |\n"
        <<"|=================================================================================|\n";
}

void Member::Display(){
    cout<<"| "<<ID<<" | "
        <<left<<setw(30)<<setfill(' ')<<truncate(Name, 30)<<" | "
        <<left<<setw(12)<<setfill(' ')<<truncate(Contact, 12)<<" | "
        <<((CurrState->getState() == ActiveNum) ? "HOAT DONG " : (CurrState->getState() == WarnedNum) ? " CANH BAO " : "  BI CAM  ")<<" |\n";
}

void Member::Footer(){
    cout<<"|=================================================================================|\n";
}

void Member::DisplaySingle(){
    cout<<"| Ma so the: "<<ID<<endl
        <<"| Ten thanh vien: "<<Name<<endl
        <<"| Thong tin lien lac: "<<Contact<<endl
        <<"| Trang thai: "<<((CurrState->getState() == ActiveNum) ? "HOAT DONG" : (CurrState->getState() == WarnedNum) ? "CANH BAO" : "BI CAM")<<endl
        <<"| So luong giao dich dang muon: "<<TransSize<<endl;
        DisplayList(TransSize, 0);
    cout<<"| So luong giao dich da tra: "<<HistSize<<endl;
        DisplayList(HistSize, 1);
}

void Member::DisplayList(int Num, bool Hist){
    if (Num == 0) return;
    if (Hist){
        cout << "| ID cac the da tra:    ";
    } else {
        cout << "| ID cac the dang muon: ";
    }
    for(int i = 0; i < Num; i++){
        cout << ((Hist) ? this->Hist[i] : TransactionID[i]) << "   "; 
        if (i % 5 == 4) cout << "\n                        ";
    }
    cout << endl;
}

Transaction::Transaction(string Owner, bool Res, int borrowingdays, Items *ItemList, int Number, LinkedList<Resources*>* BooksList){
    long Time = time(NULL);
    ID = IDHelper(Time);
    OwnerID = Owner;
    if (List == nullptr || Number == 0){
        CreateBookList(BooksList);
    } else {
        List = ItemList;
        NumberofItems = Number;
        for(int i = 0; i<Number; i++){
            ItemCount += List[i].Amount;
        }
    }
    State = nullptr;
    (Res) ? HandlingStates(Reserved, borrowingdays) : HandlingStates(Actived, borrowingdays);
}

Transaction::Transaction(const Transaction &other) {
    ID = other.ID;
    OwnerID = other.OwnerID;
    NumberofItems = other.NumberofItems;
    ItemCount = other.ItemCount;
    Borrowing = other.Borrowing;
    Due = other.Due;
    ReturnDate = other.ReturnDate;
    if (other.State) {
        this->Status = other.State->getState();
    } else {
        this->Status = 0;
    }
    if (other.List != nullptr && NumberofItems > 0) {
        List = new Items[NumberofItems];
        for (int i = 0; i < NumberofItems; i++) {
            List[i] = other.List[i];
        }
    } else {
        List = nullptr;
    }
    if (other.State != nullptr) {
        int stateNum = other.State->getState();
        switch(stateNum){
            case Reserved:  this->State = new ReserveState(); break;
            case Returned:  this->State = new ReturnState(); break;
            case Overdue:   this->State = new LateState(); break;
            case Cancelled: this->State = new CancelState(); break;
            default:        this->State = new ActiveState(); break;
        }
    } else {
        this->State = new ActiveState();
    }
}

string Transaction::IDHelper(long Val){
    string YMD;
    long HMS = (Val+25200) % 86400;
    Date Temp(Val);
    YMD = to_string(Temp.Y-2000) + StringHelper(Temp.M) + StringHelper(Temp.D) + "-";
    int H = HMS / 3600;
    int M = (HMS % 3600) / 60;
    int S = (HMS % 3600) % 60;
    YMD +=  StringHelper(H) + StringHelper(M) +StringHelper(S);
    return YMD;
}


void Transaction::CreateBookList(LinkedList<Resources*>* BooksList){
    if(BooksList->isEmpty()) {
        cout<<"Co su co ve he thong sach, vui long thu lai sau";
        return;
    }
    BooksList->SortWrap(Resources::getStringPtr(ResourcestringID), true);
    BooksList->display();
    cout<<"\nNhap so loai sach can dat, nhan 0 de huy:";
    int n = -1;
    cin>>n;
    if(n <= 0){
        cout<<"\nDa huy";
        return;
    }
    Items *LoanList = new Items[n];
    cout<<"Nhap nhung quyen sach can muon, nhan 0 de ket thuc som:\n";
    int Val, i;
    for (i = 0; i < n; i++){
    cout<<"Nhap so thu tu cua sach thu "<<i+1<<" can muon va so luong can: ";
        cin>>Val;
        while(Val > BooksList->Size || Val < 0){
            cout<<"\nVui long chi nhap tu 0 den "<<BooksList->Size<<": ";
            cin>>Val;
        }
        if (Val == 0) {
            cout<<"\nDa lap thanh cong danh sach gom "<<i+1<<" dau sach";
            break;
        }
        Resources *Choosing = (*BooksList)[Val]->data;
        LoanList[i].BookID = Choosing->getString(ResourcestringID);
        int max=Choosing->getInt(ResourcesintAvail);
        cout<<"\nNhap so luong sach "<<Choosing->getString(ResourcestringName)<<" can chon"
            <<"\nTu 0 den "<<max;
        cin>>LoanList[i].Amount;
        if(LoanList[i].Amount > max){
            cout<<"\nHien tai sach loai nay chi co "<<max<<" quyen, khong du dap ung nhu cau";
            i--;
            continue;
        }
        Choosing->LendingBook(LoanList[i].Amount);
    }
    if (i+1<n){
        Items *ListItem = new Items[i+1];
        NumberofItems = i+1;
        for(int j = 0; j<=i; j++){
            ListItem[j] = LoanList[j];
            ItemCount += LoanList[j].Amount;
        }
        List = ListItem;
        delete [] LoanList;
        return;
    }
    NumberofItems = n;
    for(int j = 0; j<n; j++){
        ItemCount += LoanList[j].Amount;
    }
    List = LoanList;
}

void Transaction::setState(TranState* newState){
        if (State) delete State;
        State = newState;
        Status = State->getState();
    }

void Transaction::ReturnBooks(LinkedList<Resources*>* BooksList){
    if (Status != Actived && Status != Overdue && Status != Reserved) return;
    this->HandlingStates(Returned);
    for (int i = 0; i < NumberofItems; i++){
        Resources** ItemPtr = BooksList->SearchItem(Resources::getStringPtr(ResourcestringID), List[i].BookID);
        if (ItemPtr == nullptr) cout<<"Canh bao: khong tim thay sach co ID: "<<List[i].BookID; 
        else (*ItemPtr)->ReturningBook(List[i].Amount);
    }
}

void ActiveState::handle(Transaction *Trans) {
    cout<<"\nDang tra sach";
    Trans->setState(new ReturnState());
}

void ActiveState::handleAlt(Transaction *Trans) {
    Trans->setState(new LateState());
}

void LateState::handle(Transaction *Trans){
    cout<<"\nDang tra sach";
    Trans->setState(new ReturnState());
}

void ReserveState::handle(Transaction *Trans) {
    cout<<"\nDa nhan sach";
    Trans->setState(new ActiveState());
}

void ReserveState::handleAlt(Transaction *Trans) {
    cout<<"\nDang huy the";
    Trans->setState(new CancelState());
}

void Transaction::Header(){
    cout<<"|=============================================================================================|\n"
        <<"| STT |  MA THE MUON  |  MA CHU THE  | NGAY MUON  |  NGAY DEN HAN  |  NGAY TRA  | TRANG THAI  |\n"
        <<"|=============================================================================================|\n";
}

void Transaction::Display(){
    cout<<"| "<<ID
        <<" | "<<OwnerID
        <<" | "<<Borrowing
        <<" |   "<<Due
        <<"   | ";
    if (!ReturnDate.emptyDate()) {
        cout << ReturnDate;
    } else {
        cout << " CHUA TRA ";
    }
    cout<<" | ";
    switch (State->getState()){
        case Reserved:
            cout<<"  GIU CHO  |";
            break;
        case Actived:
            cout<<" DANG MUON |";
            break;
        case Returned:
            cout<<"  DA TRA   |";
            break;
        case Overdue:
            cout<<"  QUA HAN  |";
            break;
    }
    cout<<"\n";
}

void Transaction::Footer(){
    cout<<"|=============================================================================================|\n";
}

void Transaction::HandlingStates(int StateChange, int BorrowingDays){
    if (State == nullptr && (StateChange == Reserved || StateChange == Actived)){
        Borrowing = CurrentDate;
        Due = Borrowing + BorrowingDays;
        if (StateChange == Reserved) setState(new ReserveState());
        if (StateChange == Actived) setState(new ActiveState());
        return;
    }
    if (State == nullptr) return;
    if (State->getState() == Reserved && StateChange == Actived){
        Borrowing = CurrentDate;
        Due = Borrowing + BorrowingDays;
        State->handle(this);
        return;
    }
    if (State->getState() == Reserved && StateChange == Cancelled){
        State->handleAlt(this);
        return;
    }
    if (State->getState() == Actived && StateChange == Returned){
        ReturnDate = CurrentDate;
        State->handle(this);
        return;
    }
    if (State->getState() == Actived && StateChange == Overdue){
        State->handleAlt(this);
        return;
    }
}

void Transaction::Checkup(LinkedList<Resources*>* Library){
    if (State->getState() == Actived && CurrentDate > Due){
        HandlingStates(Overdue);
        return;
    }
    if (State->getState() == Actived && CurrentDate > Due){
        HandlingStates(Cancelled);
        ReturnBooks(Library);
        return;
    }
};

void Transaction::Revalidate(){
    cout<<"\nNhap so ngay can gia han cho the "<<ID<<": ";
    int Days;
    cin>>Days;
    Due = Due + Days;
    int StateVal;
    StateVal = State->getState();
    if(StateVal == Reserved || StateVal == Returned || StateVal == Cancelled){
        cout<<"Khong the gia han the co tinh trang nay";
    };
    if(StateVal == Overdue && (CurrentDate < Due || CurrentDate == Due)){
        setState(new ActiveState());
    }
    getchar();
    return;
};

void Transaction::DisplaySingle(){
    cout<<"| Ma the: "          <<ID<<endl
        <<"| Ma chu the: "      <<OwnerID<<endl
        <<"| Ngay muon: "       <<Borrowing<<endl
        <<"| Ngay den han: "    <<Due<<endl
        <<"| Ngay tra: ";
    if (!ReturnDate.emptyDate()) {
        cout                    << ReturnDate << endl;
    } else {
        cout                    << "CHUA TRA" << endl;
    }
    cout<<"| Trang thai: ";
    switch (State->getState()){
        case Reserved:
            cout                <<"GIU CHO"<<endl;
            break;
        case Actived:
            cout                <<"DANG MUON"<<endl;
            break;
        case Returned:
            cout                <<"DA TRA"<<endl;
            break;
    }
    cout<<"| Danh sach ID cac sach muon: \n";
    for (int i = 0; i < NumberofItems; i++){
        cout                    <<"| - "<<List[i].BookID<<" x"<<List[i].Amount<<endl;
    }
}

Transaction::~Transaction(){
    delete [] List;
    delete State;
}

Transaction::Transaction(string ID, string OwnerID, int NumberofItems, int ItemCount, Date Borrowing, Date Due, Date Return, int Status, Items *List){
    this->ID = ID;
    this->OwnerID = OwnerID;
    this->NumberofItems = NumberofItems;
    this->ItemCount = ItemCount;
    this->Borrowing = Borrowing;
    this->Due = Due;
    this->ReturnDate = Return;
    this->List = List;
    this->Status = Status;
    switch(Status){
            case Reserved: this->State = new ReserveState(); break;
            case Returned: this->State = new ReturnState(); break;
            case Overdue:  this->State = new LateState(); break;
            case Cancelled:this->State = new CancelState(); break;
            default:       this->State = new ActiveState(); break;
    }
};


Member::Member(string ID, string Name, string Contact, int State, int HistSize, int TransSize, Date Vio, string* Hist, string* Trans, bool hardpun){
    this->ID = ID;
    this->Name = Name;
    this->Contact = Contact;
    this->HistSize = HistSize;
    this->TransSize = TransSize;
    this->LastVio = Vio;
    this->Hist = Hist;
    this->TransactionID = Trans;
    this->fromSuspended = hardpun;
    this->State = State;
    switch(State){
        case ActiveNum: this->CurrState = new Active(); break;
        case WarnedNum: this->CurrState = new Warned(); break;
        case SuspendedNum: this->CurrState = new Suspended(); break;
    }
}

void Transaction::ReconstructBookList(LinkedList<Resources*>& List){
    if (NumberofItems == 0){
        cout<<"Danh sach rong";
        return;
    }
    int j = 0;
    string currentID;
    Resources** tempList = new Resources*[NumberofItems];
    for(int i = 0; i < NumberofItems; i++){
        currentID = this->List[i].BookID;
        Resources **foundRes = List.SearchItem(Resources::getStringPtr(ResourcestringID), currentID);
        if (foundRes) tempList[j++] = *foundRes;
    }
    Resources::Header();
    for(int i = 0; i < j; i++){
        cout<<"| "<<right<<setw(3)<<setfill('0')<<i+1<<" ";
        tempList[i]->Display();
    }
    int val=-1;
    Resources::Footer();
    while(1){
        cin >> val;
        if (val < 0 || val > j) cout<<"\nKhong hop le";
        if (val == 0) {
            delete tempList;
            return;
        }
        tempList[val]->DisplaySingle();
    }
}

Member& Member::operator=(const Member& other) {
    if (this == &other) return *this;
    delete[] Hist;
    delete[] TransactionID;
    delete CurrState;
    ID = other.ID;
    Name = other.Name;
    Contact = other.Contact;
    LastVio = other.LastVio;
    HistSize = other.HistSize;
    TransSize = other.TransSize;
    fromSuspended = other.fromSuspended;
    State = other.CurrState->getState();
    if (other.Hist && HistSize > 0) {
        Hist = new string[HistSize];
        for (int i = 0; i < HistSize; i++) Hist[i] = other.Hist[i];
    } else {
        Hist = nullptr;
    }

    if (other.TransactionID && TransSize > 0) {
        TransactionID = new string[TransSize];
        for (int i = 0; i < TransSize; i++) TransactionID[i] = other.TransactionID[i];
    } else {
        TransactionID = nullptr;
    }
    switch(State){
        case ActiveNum: this->CurrState = new Active(); break;
        case WarnedNum: this->CurrState = new Warned(); break;
        case SuspendedNum: this->CurrState = new Suspended(); break;
        default: this->CurrState = new Active();
    }
    return *this;
}
Transaction& Transaction::operator=(const Transaction& other) {
    if (this == &other) return *this;
    delete[] List;
    delete State;
    ID = other.ID;
    OwnerID = other.OwnerID;
    NumberofItems = other.NumberofItems;
    ItemCount = other.ItemCount;
    Borrowing = other.Borrowing;
    Due = other.Due;
    ReturnDate = other.ReturnDate;
    Status = other.Status;
    if (other.List && NumberofItems > 0) {
        List = new Items[NumberofItems];
        for (int i = 0; i < NumberofItems; i++) List[i] = other.List[i];
    } else {
        List = nullptr;
    }
    if (other.State) {
        int s = other.State->getState();
        switch(s){
            case Reserved:  this->State = new ReserveState(); break;
            case Returned:  this->State = new ReturnState(); break;
            case Overdue:   this->State = new LateState(); break;
            case Cancelled: this->State = new CancelState(); break;
            default:        this->State = new ActiveState(); break;
        }
    } else {
        this->State = new ActiveState();
    }
    return *this;
}