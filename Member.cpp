#include "Member.h"
#include <stdlib.h>

Member::Member(string NameInp, string ContactInp, string IDInp){
    Name = NameInp;
    Contact = ContactInp;
    ID = IDInp;
    LastVio(0,0,0);
    state = Active;
    Hist = nullptr;
    TransactionID = nullptr;
}

Member::~Member(){
    delete [] Hist;
    delete [] TransactionID;
}

Member* Member::newMember(const LinkedList<Member>& allMembers){
    int n = 0;
    string TempID;
    cout<<"Nhap loai thanh thanh vien\n"
        <<"[1] Sinh vien\n"
        <<"[2] Tu do\n";
    while (n!=1 || n!=2){
        cin>>n;
        switch(n){
            case 1: {
                cout<<"Nhap so the sinh vien cho ID thu vien: ";
                string SVID;
                cin>>SVID;
                TempID = "SV-" + SVID;
                LinkedList<Member> existing = allMembers.SearchMethod(&Member::ID, TempID);
                if (!allMembers.isEmpty()){
                    cout<<"ID bi trung, vui long kiem tra lai"
                    cin.get()
                    return nullptr;
                }
                cin.get();
                break;
            }
            case 2: {
                do{
                srand(time(NULL));
                int RandNum = rand()*rand() % 90000001 + 9999999;
                TempID = "ID-" + to_string(RandNum);
                LinkedList<Member> existing = allMembers.SearchMethod(&Member::ID, TempID);
                } while(!allMembers.isEmpty());
                cout<<"\nID: "<<ID;
                cin.get();
                break;
            }
            default:{
                cout<<"Khong hop le";
                cin.get();
                break;
            }
        }
    }
    string NameInp, ContactInp;
    cout<<"\nNhap Ho va Ten: ";
    cin>>NameInp;
    cout<<"\nNhap thong tin lien he: ";
    cin>>ContactInp;
    Member* newMember = newMember(NameInp, ContactInp, TempID);
    cout<<"Da hoan thanh thu tuc dang ky";
    cin.get();
    return newMember;
}

void Member::Sparing(){
    
}