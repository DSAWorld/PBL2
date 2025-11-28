#include "Method.cpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream> 

class Resources;
class Book;
class Magazine;
class Thesis;

string Quoting(const string &inp){
    return "\"|" + inp + "|\"";
};

string Librarian::toFileString() const {
    stringstream ss;
    ss  << Quoting(ID) << " , "
        << Quoting(Name) << " , "
        << Quoting(Contact) << " , "
        << Quoting(Password) << " , ";
    return ss.str();
};

string Books::toFileString() const {
    stringstream ss;
    ss << Quoting(ID) << " , "
       << Quoting(Name) << " , "
       << Quoting(Author) << " , "
       << Type << " , "
       << Genre << " , "
       << Available << " , "
       << TotalAmount << " , ";
    ss << Quoting(Publisher) << " , "
       << Quoting(ISBN);
    return ss.str();
}

string Magazine::toFileString() const {
    stringstream ss, date_ss;
    date_ss << IssueDate;
    ss << Quoting(ID) << " , "
       << Quoting(Name) << " , "
       << Quoting(Author) << " , "
       << Type << " , "
       << Genre << " , "
       << Available << " , "
       << TotalAmount << " , ";
    ss << Quoting(IssueNum) << " , "
       << Quoting(date_ss.str());
    return ss.str();
}

string Thesis::toFileString() const {
    stringstream ss;
    ss << Quoting(ID) << " , "
       << Quoting(Name) << " , "
       << Quoting(Author) << " , "
       << Type << " , "
       << Genre << " , "
       << Available << " , "
       << TotalAmount << " , ";
    ss << Quoting(Uni) << " , "
       << Quoting(Visor);
    return ss.str();
}


string Member::Grouping(const string inp[], int size){
    string Res = "[";
    for (int i = 0; i < size; i++){
        Res += " \'" + inp[i] + "\' ;";
    }
    Res += "]";
    return Res;
}

string Member::toFileString() const {
    stringstream ss, date_ss;
    Date tempLastVio = this->LastVio;
    if (tempLastVio.emptyDate()) date_ss << "X"; else date_ss << LastVio;
    ss  << Quoting(ID) << " , "
        << Quoting(Name) << " , "
        << Quoting(Contact) << " , "
        << CurrState->getState() << " , "
        << HistSize << " , "
        << TransSize << " , "
        << fromSuspended << " , "
        << Quoting(date_ss.str()) << " , "
        << Grouping(Hist, HistSize) << " , "
        << Grouping(TransactionID, TransSize);
    return ss.str();
}

string Transaction::Grouping(const Items inp[], int size){
    string Res = "[";
    for (int i = 0; i < size; i++){
        Res += " \'" + inp[i].BookID + "\'x" + to_string(inp[i].Amount) + " ;";
    }
    Res += "]";
    return Res;
}

string Transaction::toFileString() const {
    stringstream ss, borrow, due, ret;
    if (State->getState() == Cancelled) return "";
    borrow << Borrowing;
    due << Due;
    Date tempReturnDate = this->ReturnDate;
    if (tempReturnDate.emptyDate()) ret << "X"; else ret << ReturnDate;
    ss  << Quoting(ID) << " , "
        << Quoting(OwnerID) << " , "
        << NumberofItems << " , "
        << ItemCount << " , "
        << Quoting(borrow.str()) << " , "
        << Quoting(due.str()) << " , "
        << Quoting(ret.str()) << " , "
        << Status << " , "
        << Grouping(List, NumberofItems);
    return ss.str();
    }

string trim(string &in){
    size_t first = in.find_first_not_of(" \t\n\r\f\v");
    if (string::npos == first) {
        return "";
    }
    size_t last = in.find_last_not_of(" \t\n\r\f\v");
    return in.substr(first, (last - first + 1));
}

string unquote(string &in){
    if (in.length() >= 4 && 
        in.substr(0, 2) == "\"|" && 
        in.substr(in.length() - 2) == "|\"") {
        in = in.substr(2, in.length() - 4);
    }
    return in;
}

string ungroup(string &in){
    if (in.length() >= 2 && 
        in.front() == '[' && 
        in.back() == ']') {
        in = in.substr(1, in.length() - 2);
    }
    return in;
}

string unquoteArr(string &in){
    if (in.length() >= 2 && 
        in.front() == '\'' && 
        in.back() == '\'') {
        in = in.substr(1, in.length() - 2);
    }
    return in;   
}

string FileHandler::getField(stringstream &ss){
    string field;
    if (!getline(ss, field, ',')) return "";
    while (field.find("\"|") != string::npos && field.find("|\"") == string::npos) {
        string next_segment;
        if (!getline(ss, next_segment, ',')) break;
        field += "," + next_segment;
    }
    field = trim(field);
    field = unquote(field);
    field = ungroup(field);
    return field;
}

Date FileHandler::getDateField(const string &Str){
    if (Str == "X" || Str == "x" || Str.empty()){
        return Date(0,0,0);
    }
    stringstream date_ss(Str);
    int d, m, y;
    char temp1, temp2;
    date_ss >> d >> temp1 >> m >> temp2 >> y;
    return Date(d, m, y);
}

string* extendstringsize(string *data, int &maxsize){
    int oldsize = maxsize;
    maxsize *= 2;
    string *newdata = new string[maxsize*2];
    for(int i = 0; i<oldsize; i++){
        newdata[i] = data[i];
    }
    return newdata;
}

string* FileHandler::getstringArrField(string &ss, int &size){
    int maxsize = 32;
    string *IDs = new string[maxsize]; 
    size = 0;
    if (ss.empty()) return nullptr;
    stringstream sstream(ss);
    string segment;
    while(getline(sstream, segment, ';')){
        segment = trim(segment);
        if (segment.empty()) continue;
        IDs[size++]=unquoteArr(segment);
        if(size >= maxsize){
            string *newIDs = extendstringsize(IDs, maxsize);
            delete [] IDs;
            IDs = newIDs;
        }
    }
    if (size == 0) return nullptr;
    string* Arr = new string[size];
    for(int i = 0; i < size; i++){
        Arr[i] = IDs[i];
    }
    delete [] IDs;
    return Arr;
}

Items* extendItemssize(Items *data, int &maxsize){
    int oldsize = maxsize;
    maxsize *= 2;
    Items *newdata = new Items[maxsize];
    for(int i = 0; i<oldsize; i++){
        newdata[i] = data[i];
    }
    return newdata;
}

Items* FileHandler::getItemsArrField(string &ss, int &ItemNum, int &ItemCount){
    int maxsize = 32;
    Items *ItemsList = new Items[maxsize];
    ItemNum = 0;
    ItemCount = 0;
    if (ss.empty()) return nullptr;
    stringstream sstream(ss);
    string segment;
    Items tempItem;
    while (getline(sstream, segment, ';')){
        segment = trim(segment);
        if (segment.empty()) continue;
        segment = unquoteArr(segment);
        size_t Pos = segment.rfind('x');
        if (Pos == string::npos) continue;
        tempItem.BookID = segment.substr(0, Pos);
        tempItem.Amount = stoi(segment.substr(Pos+1));

        ItemsList[ItemNum++] = tempItem;
        if (ItemNum >= maxsize){
            Items *newItemsList = extendItemssize(ItemsList, maxsize);
            delete [] ItemsList;
            ItemsList = newItemsList;
        }
        ItemCount += tempItem.Amount;
    }
    if (ItemNum == 0) return nullptr;
    Items *Arr = new Items[ItemNum];
    for(int i = 0; i < ItemNum; i++){
        Arr[i] = ItemsList[i];
    }
    delete [] ItemsList;
    return Arr;
}

Librarian* FileHandler::createLib(string &line){
    stringstream ss(line);
    string ID = getField(ss);
    string Name = getField(ss);
    string Contact = getField(ss);
    string Pass = getField(ss);
    
    return new Librarian(Name, ID, Contact, Pass);
}

Resources* FileHandler::createRes(string &line){
    stringstream ss(line);

    string ID = getField(ss);
    string Name = getField(ss);
    string Author = getField(ss);
    int type = stoi(getField(ss));
    int genre = stoi(getField(ss));
    int available = stoi(getField(ss));
    int total = stoi(getField(ss));
    switch (type){
        case ResBook:{
            string Publisher = getField(ss);
            string ISBN = getField(ss);
            return new Books(ID, Name, Author, available, total, genre, Publisher, ISBN);
        }
        case ResMagazine:{
            string issueNum = getField(ss);
            string date = getField(ss);
            Date iss = getDateField(date);
            return new Magazine(ID, Name, Author, available, total, genre, issueNum, iss);
        }
        case ResThesis:{
            string Uni = getField(ss);
            string Visor = getField(ss);
            return new Thesis(ID, Name, Author, available, total, genre, Uni, Visor);
        }
        default: throw ExceptionInvalidRes();
    }
}

Member* FileHandler::createMem(string &line){
    stringstream ss(line);
    
    string id = getField(ss);
    string name = getField(ss);
    string contact = getField(ss);
    int state = stoi(getField(ss));
    int histSize = stoi(getField(ss));
    int transSize = stoi(getField(ss));
    int hardpunish = stoi(getField(ss));
    string lastVioStr = getField(ss);
    string histGroup = getField(ss);
    string transGroup = getField(ss);

    Date lastVio = getDateField(lastVioStr);
    int HistTrue;
    int TransTrue;
    string* histArray = getstringArrField(histGroup, HistTrue);
    string* TransArray = getstringArrField(transGroup, TransTrue);
    if ( HistTrue != histSize ) cerr<<"\nCanh bao: du lieu lich su cua thanh vien ("<<id<<") co the dang bi that lac\n";
    if ( TransTrue != transSize ) cerr<<"\nCanh bao: du lieu the muon cua thanh vien ("<<id<<") co the dang bi that lac\n";
    return new Member(id, name, contact, state, HistTrue, TransTrue, lastVio, histArray, TransArray, hardpunish);
}

Transaction* FileHandler::createTrans(string &line){
    stringstream ss(line);

    string id = getField(ss);
    string ownerID = getField(ss);
    int numItems = stoi(getField(ss));
    int itemCount = stoi(getField(ss));
    string borrowStr = getField(ss);
    string dueStr = getField(ss);
    string returnStr = getField(ss);
    int state = stoi(getField(ss));
    string itemGroup = getField(ss);

    Date borrowDate = getDateField(borrowStr);
    Date dueDate = getDateField(dueStr);
    Date returnDate = getDateField(returnStr);

    int actualNumItems = 0;
    int actualItemCount = 0;
    Items* itemList = getItemsArrField(itemGroup, actualNumItems, actualItemCount);

    if (actualNumItems != numItems || actualItemCount != itemCount) {
        cerr << "\nCanh bao: The muon nay ("<<id<<") co the dang bi that lac";
    }
    return new Transaction(id, ownerID, actualNumItems, actualItemCount, borrowDate, dueDate, returnDate, state, itemList);
}

template <typename Class> void FileHandler::SaveFile(const string &filename, LinkedList<Class> &list){
    ofstream file(filename);
    if (!file.is_open()){
        cerr<<"\nFile khong ton tai";
        return;
    }
    Node<Class>* current = list[1];
    while(current){
        string Data;
        if constexpr (is_pointer_v<Class>){
            Data = current->data->toFileString();
        } else {
            Data = current->data.toFileString();
        }
        if (!Data.empty()){
            file << Data << endl;
        }
        current = current->next;
    }
    file.close();
}

void FileHandler::LoadResources(const string &filename, LinkedList<Resources*> &list){
    ifstream file(filename);
    if (!file.is_open()){
        cerr<<"\nFile khong ton tai";
        return;
    }
    string line;
    while (getline(file, line)){
        if (line.empty() || line[0] == '#') continue;
        Resources* res = createRes(line);
        if (res) list.Add(res);
    }
    file.close();
}


void FileHandler::LoadMembers(const string &filename, LinkedList<Member> &list){
    ifstream file(filename);
    if (!file.is_open()){
        cerr<<"\nFile khong ton tai";
        return;
    }
    string line;
    while (getline(file, line)){
        if (line.empty() || line[0] == '#') continue;
        Member* res = createMem(line);
        if (res) {
            list.Add(*res);
            delete res;
        }
    }
    file.close();
}

void FileHandler::LoadTransactions(const string &filename, LinkedList<Transaction> &list){
    ifstream file(filename);
    if (!file.is_open()){
        cerr<<"\nFile khong ton tai";
        return;
    }
    string line;
    while (getline(file, line)){
        if (line.empty() || line[0] == '#') continue;
        Transaction* res = createTrans(line);
        if (res) list.Add(*res);
    }
    file.close();
}

void FileHandler::LoadLibrarian(const string &filename, LinkedList<Librarian> &list){
    ifstream file(filename);
    if (!file.is_open()){
        cerr<<"\nFile khong ton tai";
        return;
    }
    string line;
    while (getline(file, line)){
        if (line.empty() || line[0] == '#') continue;
        Librarian* res = createLib(line);
        if (res) list.Add(*res);
    }
    file.close();
}