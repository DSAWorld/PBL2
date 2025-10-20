#include "Transaction.h"
#include <time.h>

using namespace std;

Transaction::Transaction(string Owner, int state, int borrowingdays, Items *ItemList){
    long Time = time(NULL);
    ID = IDHelper(Time);
    OwnerID = Owner;
    State = state;
    if(state == Active){
    Borrowing = new Date(time(NULL));
    Due = Borrowing + borrowingdays;
    }
    if (List == nullptr){
        List = CreateBookList();
    } else {
        List = ItemList;
    }
    
}

Transaction::IDHelper(long Val){
    string YMD;
    long HMS = (Val+25200) % 86400;
    Date Temp(Val);
    YMD = to_string(Temp.Y-2000) + 
        ((Temp.M<10) ? {"0" + to_string(Temp.M)} : to_string(Temp.M)) + 
        ((Temp.D<10) ? {"0" + to_string(Temp.D)} : to_string(Temp.D)) +
        to_string(HMS);
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

void Transaction::Search(const LinkedList<Member>& List){
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
                LinkedList<Member> existing = List.SearchMethod(getStringPtr(stringID), ID);
                if (existing.isEmpty()){
                    cout<<"\nKhong ton tai ID nay";
                    cin.get;
                    return;
                }
                else cout << List;
            };
            case 2: {
                string ID;
                cout<<"\nNhap ID the:";
                cin >> ID;
                LinkedList<Member> existing = List.SearchMethod(getStringPtr(stringOwner), ID);
                if (existing.isEmpty()){
                    cout<<"\nKhong ton tai ID nay";
                    cin.get;
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
                LinkedList<Member> existing = List.SearchMethod(getIntPtr(intState), Num-1);
                if (existing.isEmpty()){
                    cout<<"Khong co the nao co tinh trang nay";
                    cin.get;
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