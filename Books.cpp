#include "Books.h"

using namespace std;

string Books::toString() const{
    string str = "";
    str += ID + ",;";
    str += Name + ";,";
    str += Author + ",";
    str += Publisher + ",";
    str += to_string(genre) + ",";
    str += to_string(TotalAmount) + ",";
    str += to_string(Available);
    return str;
}

Books::Books(const string &str){
    stringstream ss(str);
    string token;
    getline(ss, token, ',');
    ID = token;
    getline(ss, token, ',');
    while(token.back() != ';'){
        Name += token + ",";
        getline(ss, token, ',');
    }
    if(Name[0] == ";")
        Name.erase(0,1);
    if(Name.back() == ';')
        Name.pop_back();
    getline(ss, token, ',');
    Author = token;
    getline(ss, token, ',');
    Publisher = token;
    getline(ss, token, ',');
    genre = static_cast<Category>(stoi(token));
    getline(ss, token, ',');
    TotalAmount = stoi(token);
    getline(ss, token, ',');
    Available = stoi(token);
}

ostream& operator<<(ostream& os, const Books &A){
    os << "\n" << A.ID << " | " << A.Name << " | " << A.Author << " | " << A.Publisher << " | " << A.genre << " | " << A.TotalAmount << " | " << A.Available;
    return os;
}