#include "Transaction.h"
#include <time.h>
#include <sstream>
using namespace std;

Transaction::Transaction(string Owner, int state, int borrowingdays, Items *ItemList){
    long Time = time(NULL);
    ID = IDHelper(Time);
    OwnerID = Owner;
    State = state;
    if(state == Actived){
    Time = time(NULL);
    Borrowing((int)Time);
    Due = Borrowing + borrowingdays;
    }
    if (List == nullptr){
        List = CreateBookList();
    } else {
        List = ItemList;
    }
}

Transaction::Transaction(const string& str){
    stringstream ss(str);
    string token;
    getline(ss, ID, ',');
    getline(ss, OwnerID, ',');
    getline(ss, token, ',');
    ItemCount = stoi(token);
    getline(ss, token, ',');
    Borrowing = Date(token);
    getline(ss, token, ',');
    Due = Date(token);
    getline(ss, token, ',');
    ReturnDate = Date(token);
    getline(ss, token, ',');
    Fee = stoi(token);
    getline(ss, token, ',');
    State = stoi(token);
    List = CreateBookList();
    while (getline(ss, token, ';')){
        stringstream itemss(token);
        string bookid;
        string amountstr;
        getline(itemss, bookid, ',');
        getline(itemss, amountstr, ',');
        unsigned int amount = stoi(amountstr);
        Items newItem(bookid, amount);
        List->InsertAtEnd(newItem);
    }
}

string Transaction::IDHelper(long Val){
    string YMD;
    long HMS = (Val+25200) % 86400;
    Date Temp(Val);
    YMD = to_string(Temp.Y-2000) + StringHelper(Temp.M) + StringHelper(Temp.D);
    int H = HMS / 3600;
    int M = (HMS % 3600) / 60;
    int S = (HMS % 3600) % 60;
    YMD +=  StringHelper(H) + StringHelper(M) +StringHelper(S);
    return YMD;
}

void Transaction::BorrowDate(int Days = 14){
    long TimePassed = time(NULL);
    Date CheckDay(TimePassed);
    Borrowing = CheckDay;
    Due = Borrowing + Days;
}

void Transaction::CalculateFee(Member &ReturningMember){
    Fee = 12000;
    for(int i = 0; i<ItemCount; i++) Fee+=500;
    int lateFee = 1000;
    if (ReturnDate > Due){
        int DaysLate = ReturnDate - Due;
        if (DaysLate <= 7) Fee += DaysLate*lateFee;
        else if (DaysLate <= 14) {
            Fee += lateFee*7 + (DaysLate-7)*(2500 + 500*(DaysLate-7));
            ReturningMember.Punish();
        }
        else if (DaysLate <= 28){
            Fee += 61000 + (DaysLate-14)*4*lateFee;
            ReturningMember.Punish(true);
        }
    }
}

void Transaction::Search(const LinkedList<Transaction>& List){
    cout<<"Nhap lua chon tim kiem theo:\n"
        <<"[1] Chu the muon\n"
        <<"[2] Ma the muon\n"
        <<"[3] Tinh trang the\n"
        <<"[0] Huy\n";
    int Choice = -1;
    while(Choice < 0 || Choice > 3){
        cin >> Choice;
        switch (Choice){
            case 1: {
                string ID;
                cout<<"\nNhap ID chu the:";
                cin >> ID;
                LinkedList<Transaction> existing = List.SearchMethod(getStringPtr(stringID), ID);
                if (existing.isEmpty()){
                    cout<<"\nKhong ton tai ID nay";
                    cin.get();
                    return;
                }
                else cout << List;
            };
            case 2: {
                string ID;
                cout<<"\nNhap ID the:";
                cin >> ID;
                LinkedList<Transaction> existing = List.SearchMethod(getStringPtr(stringOwner), ID);
                if (existing.isEmpty()){
                    cout<<"\nKhong ton tai ID nay";
                    cin.get();
                    return;
                }
                else cout << List;
            };
            case 3: {
                int Num = 0;
                cout<<"\nNhap tinh trang the:"
                    <<"\n[1] Dang cho muon"
                    <<"\n[2] Da tra"
                    <<"\n[3] Qua han"
                    <<"\n[4] Dang chuan bi"
                    <<"\n[5] San sang";
                while (Num <1 || Num > 5) {
                    cin >> Num;
                    if (Num < 1 || Num > 5) cout<<"\nKhong hop le";
                }
                LinkedList<Transaction> existing = List.SearchMethod(getIntPtr(intState), Num-1);
                if (existing.isEmpty()){
                    cout<<"Khong co the nao co tinh trang nay";
                    cin.get();
                    return;
                }
                else cout << List;
            }
            case 0: return;
            default: {
                cout<<"Khong hop le";
                cin.get();
                break;
            }
        }
    }
}

string Transaction::toString(LinkedList<Items>* ItemList) const{
    string str="";
    Node<Items>* current = ItemList->head;
    while (current != nullptr){
        str += current->data.toString() + ";";
        current = current->next;
    }
    return str;
}

void Transaction::CreateBookList(LinkedList<Books>& AllBooks){
    List = new LinkedList<Items>();
    for (int i = 0; i < ItemCount; i++){
        string BookID;
        unsigned int Amount;
        cout << "Nhap ID sach thu " << i+1 << ": ";
        cin >> BookID;
        Books* bookPtr = AllBooks.SearchMethodSingle(&Books::ID, BookID);
        if (bookPtr == nullptr){
            cout << "Khong tim thay sach voi ID nay. Vui long nhap lai." << endl;
            i--;
            continue;
        }
        cout << "Nhap so luong muon thu " << i+1 << ": ";
        cin >> Amount;
        if (Amount > bookPtr->Available){
            cout << "Khong du so luong sach. Vui long nhap lai." << endl;
            i--;
            continue;
        }
        Items newItem(BookID, Amount);
        List.Add(newItem);
        bookPtr->Available -= Amount;
    }
}

string Transaction::toString() const{
    string str="";
    str += ID;
    str += "," + OwnerID;
    str += "," + to_string(ItemCount);
    str += "," + Borrowing.toString();
    str += "," + Due.toString();
    str += "," + ReturnDate.toString();
    str += "," + to_string(Fee);
    str += "," + to_string(State);
    str += "," + toString(List);
    return str;
}