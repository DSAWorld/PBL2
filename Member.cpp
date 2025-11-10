#include "Member.h"
#include <stdlib.h>

Member::Member(string NameInp, string ContactInp, bool isStudent, string studentID, const LinkedList<Member>& allMembers) {
    Name = NameInp;
    Contact = ContactInp;
    
    if (isStudent) {
        ID = "SV-" + studentID;
        LinkedList<Member> existing = allMembers.SearchMethod(&Member::ID, ID);
        if (!existing.isEmpty()) {
            throw ExceptionIDDuplicate("sinh vien");
        }
    } else {
        LinkedList<Member> existing;
        do {
            srand(time(NULL));
            int RandNum = rand()*rand() % 90000001 + 9999999;
            ID = "ID-" + to_string(RandNum);
            LinkedList<Member> existing = allMembers.SearchMethod(&Member::ID, ID);
        } while (!existing.isEmpty());
    }

    LastVio = Date(0,0,0);
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
                cin.get();
                break;
            }
            case 2: {
                LinkedList<Member> existing;
                do{
                srand(time(NULL));
                int RandNum = rand()*rand() % 90000001 + 9999999;
                TempID = "ID-" + to_string(RandNum);
                LinkedList<Member> existing = allMembers.SearchMethod(&Member::ID, TempID);
                } while (!existing.isEmpty());
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
    Member* newMember = new Member(NameInp, ContactInp, (n == 1), TempID, allMembers);
    cout<<"Da hoan thanh thu tuc dang ky";
    cin.get();
    return newMember;
}

void Member::Sparing(){
    
}