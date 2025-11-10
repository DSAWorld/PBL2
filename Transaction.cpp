#include "Transaction.h"
#include <time.h>

using namespace std;

Transaction::Transaction(string Owner, int state, int borrowingdays, Items *ItemList, int Number, LinkedList<Resources>& BooksList){
    long Time = time(NULL);
    ID = IDHelper(Time);
    OwnerID = Owner;
    if (List == nullptr || Number == 0){
        cout<<"Danh sach trong hoac co van de, can phai lap danh sach cac sach muon";
        CreateBookList(BooksList);
    } else {
        List = ItemList;
        NumberofItems = Number;
        for(int i = 0; i<Number; i++){
            ItemCount += List[i].Amount;
        }
    }
    Status = state;
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

// void Transaction::CalculateFee(Member &ReturningMember){
//     Fee = 12000;
//     for(int i = 0; i<ItemCount; i++) Fee+=500;
//     int lateFee = 1000;
//     if (ReturnDate > Due){
//         int DaysLate = ReturnDate - Due;
//         if (DaysLate <= 7) Fee += DaysLate*lateFee;
//         else if (DaysLate <= 14) {
//             Fee += lateFee*7 + (DaysLate-7)*(2500 + 500*(DaysLate-7));
//             ReturningMember.Punish();
//         }
//         else if (DaysLate <= 28){
//             Fee += 61000 + (DaysLate-14)*4*lateFee;
//             ReturningMember.Punish(true);
//         }
//     }
// }

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
                LinkedList<Transaction> existing = List.SearchMethod(getStringPtr(TransstringID), ID);
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
                LinkedList<Transaction> existing = List.SearchMethod(getStringPtr(TransstringOwner), ID);
                if (existing.isEmpty()){
                    cout<<"\nKhong ton tai ID nay";
                    cin.get();
                    return;
                }
                else cout << List;
            };
            // case 3: {
            //     int Num = 0;
            //     cout<<"\nNhap tinh trang the:"
            //         <<"\n[1] Dang cho muon"
            //         <<"\n[2] Da tra"
            //         <<"\n[3] Qua han"
            //         <<"\n[4] Dang chuan bi"
            //         <<"\n[5] San sang";
            //     while (Num <1 || Num > 5) {
            //         cin >> Num;
            //         if (Num < 1 || Num > 5) cout<<"\nKhong hop le";
            //     }
            //     LinkedList<Transaction> existing = List.SearchMethod(getIntPtr(intState), Num-1);
            //     if (existing.isEmpty()){
            //         cout<<"Khong co the nao co tinh trang nay";
            //         cin.get();
            //         return;
            //     }
            //     else cout << List;
            // }
            case 0: return;
            default: {
                cout<<"Khong hop le";
                cin.get();
                break;
            }
        }
    }
}

void Transaction::CreateBookList(LinkedList<Resources>& BooksList){
    if(BooksList.isEmpty()) {
        cout<<"Co su co ve he thong sach, vui long thu lai sau";
        return;
    }
    BooksList.SortWrap(Resources::getStringPtr(ResourcestringID), true);
    cout<<BooksList;
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
    cout<<"Nhap so thu tu cua sach thu "<<i+1<<" can muon va so luong can:";
        cin>>Val;
        while(Val > BooksList.Size || Val < 0){
            cout<<"\nVui long chi nhap tu 0 den "<<BooksList.Size;
            cin>>Val;
        }
        if (Val == 0) {
            cout<<"\nDa lap thanh cong danh sach gom "<<i+1<<" dau sach";
            break;
        }
        Resources *Choosing = BooksList.searchIndex(Val);
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
        delete State;
        State = newState;
    }

void Transaction::ReturnBooks(LinkedList<Resources>& BooksList){
    for (int i = 0; i < NumberofItems; i++){
        Resources *Item = BooksList.SearchItem(Resources::getStringPtr(ResourcestringID), List[i].BookID);
        Item->ReturningBook(List[i].Amount);
    }
}

void ActiveState::handle(Transaction *Trans) {
    cout<<"\nDang tra sach";
    Trans->setState(new ReturnState());
}

void ReserveState::handle(Transaction *Trans) {
    cout<<"\nDa nhan sach";
    Trans->setState(new ActiveState());
}

void ReserveState::handleAlt(Transaction *Trans) {
    cout<<"\nChu the da khong nhan sach trong 3 ngay, dang huy the";
    Trans->setState(new CancelState());
}

