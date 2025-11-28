#include "FilesIO.cpp"

using namespace std;

Date CurrentDate(time(NULL));

bool Startup(LinkedList<Librarian>& librarianList, Librarian** currentUser){
    if (librarianList.isEmpty()) {
        cout << "\nKhong tim thay du lieu Thu thu. Tao tai khoan mac dinh (admin/admin).";
        librarianList.Add(Librarian("Administrator", "admin", "N/A", "admin"));
    }
    *currentUser = login(librarianList);
    if (*currentUser == nullptr){
        cout<<"\nThong tin khong hop le, chuong trinh se thoat";
        getchar();
        return false; 
    }
    return true;
}

void ResourcesMenu(){
    system("cls");
    cout<<"\n==================================="
        <<"\n        QUAN LY TAI NGUYEN         "
        <<"\n==================================="
        <<"\n[1] HIEN THI THONG TIN CAC TAI LIEU"
        <<"\n[2] NHAP THEM TAI LIEU"
        <<"\n[3] XOA TAI LIEU"
        <<"\n[4] SAP XEP LAI THU VIEN"
        <<"\n[5] TIM KIEM THONG TIN"
        <<"\n[0] QUAY LAI"
        <<"\n==================================="
        << "\nLua chon cua ban: ";
}

void ResourcesDisplay(LinkedList<Resources*>* Library){
    do{
        int choice = 0;
        Library->display();
        cout<<"\nNhap STT de xem chi tiet tai lieu, hoac 0 de thoat: ";
        cin>>choice;
        cin.ignore(1000, '\n');;
        if (choice == 0) return;
        Node<Resources*>* Temp = (*Library)[choice];
        if (Temp == nullptr) throw ExceptionOutofBound();
        Temp->DisplaySingle();
        getchar();
    } while (true);
}

void AddResources(LinkedList<Resources*>* Library){
    cout<<"\n---------THEM TAI LIEU---------"
        <<"\nNhap loai tai lieu them vao: "
        <<"\n[1] Sach"
        <<"\n[2] Tap chi"
        <<"\n[3] Luan van"
        <<"\n--------------------------------"
        << "\nLua chon cua ban: ";
    int Choice;
    cin>>Choice;
    cin.ignore(1000, '\n');;
    switch(Choice){
        case 1: {Books::newItem(Library); break;}
        case 2: {Magazine::newItem(Library); break;}
        case 3: {Thesis::newItem(Library); break;}
        default: throw ExceptionInvalidRes();
    }
        cin.ignore(1000, '\n');;
        getchar();
}

void DeleteResources(LinkedList<Resources*>* Library){
    cout<<"\n---------XOA TAI LIEU---------"
        <<"\nNhap loai tai lieu xoa: "
        <<"\n[1] Xoa theo STT"
        <<"\n[2] Xoa theo ID"
        <<"\n[0] Huy xoa"
        <<"\n--------------------------------"
        <<"\nLua chon: ";
    int Choice;
    cin>> Choice;
    cin.ignore(1000, '\n');
    switch(Choice){
        case 0: return;
        case 1: {
            Library->display(); 
            cout << "\nNhap STT can xoa: ";
            int idx;
            cin >> idx;
            Library->deleteIndex(idx);
            cout << "\nDa xoa tai nguyen co STT "<<idx;
            break;
            }
        case 2: {
            Library->display();
            string inputID;
            cout<<"\nNhap ID can xoa: ";
            getline(cin, inputID);
            Node<Resources*>* current = (*Library)[1];
            int foundIndex = -1;
            int currentIndex = 1;
            while (current != nullptr) {
            string currentID = current->data->getString(ResourcestringID);
            if (currentID == inputID) {
                foundIndex = currentIndex;
                break;
            }
            current = current->next;
            currentIndex++;
            }
            if (foundIndex != -1) {
            cout << "\nTim thay tai lieu: " << current->data->getString(ResourcestringName);
            cout << "\nXac nhan xoa? (1: Co, 0: Khong): ";
            int confirm;
            cin >> confirm;
            if (confirm == 1) {
                Library->deleteIndex(foundIndex);
                cout << "\nDa xoa thanh cong.";
            } else {
                cout << "\nDa huy xoa.";
                }
            }  else {
            cout << "\nKhong tim thay ID: " << inputID;
            }
            break;
        }
        default: throw ExceptionInvalidChoice();
    }
    cin.ignore(1000, '\n');;
    cout<<"\nNhan [1] de tiep tuc xoa, [0] de ket thuc: ";
    cin>>Choice;
    cin.ignore(1000, '\n');;
    if(Choice == 1){
        system("cls");
        DeleteResources(Library);
    }
}

void SortResources(LinkedList<Resources*>* Library){
    cout<< "\nChon thuoc tinh sap xep: "
        << "\n[1] Theo ID"
        << "\n[2] Theo Ten"
        << "\n[3] Theo So luong ton kho"
        << "\n[4] Theo loai tai nguyen"
        << "\n----------------------------"
        << "\nLua chon: ";
    int sortChoice;
    cin >> sortChoice;
    cin.ignore(1000, '\n');;
    switch(sortChoice) {
        case 1: 
            Library->SortWrap(Resources::getStringPtr(ResourcestringID)); 
            break;
        case 2: 
            Library->SortWrap(Resources::getStringPtr(ResourcestringName)); 
            break;
        case 3: 
            Library->SortWrap(Resources::getIntPtr(ResourcesintAvail)); 
            break;
        case 4:
            Library->SortWrap(Resources::getIntPtr(ResourcesintType));
            break;
        default: 
            throw ExceptionInvalidChoice();
    }
    cout << "\nDa sap xep xong.";
    Library->display();
    getchar();
    getchar();
}

void SearchResstring(LinkedList<Resources*>* Library, int TypeVal){
    cout<<"\nNhap chuoi can tim: ";
    string Input;
    getline(cin, Input);
    int Holder[Library->Size];
    int AntiHolder[Library->Size];
    int AntiHolderSize = 0, HolderSize = 0, MemType, Index = 1;
    Node<Resources*>* Search = (*Library)[Index];
    if (TypeVal == 1) MemType = ResourcestringID;
    else MemType = ResourcestringName;
    while(Search != nullptr){
        string Temp = Search->data->getString(MemType);
        if (Temp.find(Input) != string::npos) Holder[HolderSize++] = Index;
        Search = Search -> next;
        Index++;
    }
    if (HolderSize == 0){
        cout<<"\nKhong co du lieu nay";
        getchar();
        return;
    }
    Resources::Header();
    for(int i = 0; i < HolderSize; i++){
        Search = (*Library)[Holder[i]];
        cout<<"| "<<right<<setfill('0')<<setw(3)<<i+1<<" ";
        Search->Display();
    }
    Resources::Footer();
    while(1){
    cout<<"\nNhap STT cua sach can xem, them so luong sach hoac xoa: ";
    int STT, flag = 0;
    cin>>STT;
    cin.ignore(1000, '\n');;
    STT--;
    for (int i = 0; i<AntiHolderSize; i++) {
        if (STT == AntiHolder[i]){
            flag = 1;
            break;
        }
    }
    if (flag == 1){
        cout<<"\nTai lieu da bi danh dau xoa";
        getchar();
        flag=0;
        continue;
    }
    Search = (*Library)[Holder[STT]];
    if(Search == nullptr) throw ExceptionOutofBound();
    cout<<"\n[1] Xem thong tin"
        <<"\n[2] Them so luong tai lieu"
        <<"\n[3] Xoa tai lieu khoi thu vien"
        <<"\n[4] Chon tai lieu khac"
        <<"\n[0] Ngung"
        << "\nLua chon cua ban: ";
    int breakflag = 1;
    while(breakflag){
    int ChoiceNum = -1;
    cin>> ChoiceNum;
    cin.ignore(1000, '\n');;
        switch (ChoiceNum){
            case 1: Search->DisplaySingle();   break;
            case 2: {
                int Adding;
                cout<<"\nNhap so luong can them: ";
                cin>>Adding;
                cin.ignore(1000, '\n');;
                Search->data->AddingStockBook(Adding);
                break;
            }
            case 3: {
                Library->deleteIndex(Holder[STT]);
                AntiHolder[AntiHolderSize++] = STT;
                breakflag = 0;
                break;
            }
            case 4: breakflag = 0; break;
            case 0: return;
            default: throw ExceptionInvalidChoice();
            }
        getchar();
        if (breakflag) cout<<"Lua chon tiep theo: ";
        }
    }
}

void SearchResint(LinkedList<Resources*>* Library, int TypeVal){
    cout<<"\nNhap gia tri can tim: ";
    int Input;
    cin>>Input;
    cin.ignore(1000, '\n');;
    int Holder[Library->Size];
    int AntiHolder[Library->Size];
    int AntiHolderSize = 0, HolderSize = 0, MemType, Index = 1;
    Node<Resources*>* Search = (*Library)[Index];
    if (TypeVal == 3) MemType = ResourcesintAvail;
    else MemType = ResourcesintType;
    while(Search != nullptr){
        if (Search->data->getInt(MemType) == Input) Holder[HolderSize++] = Index;
        Search = Search -> next;
        Index++;
    }
    if (HolderSize == 0){
        cout<<"\nKhong co du lieu nay";
        getchar();
        return;
    }
    Resources::Header();
    for(int i = 0; i < HolderSize; i++){
        Search = (*Library)[Holder[i]];
        cout<<"| "<<right<<setfill('0')<<setw(3)<<i+1<<" ";
        Search->Display();
    }
    Resources::Footer();
    while(1){
    cin.ignore(1000, '\n');;
    cout<<"\nNhap STT cua sach can xem, them so luong sach hoac xoa";
    int STT, flag = 0;
    cin>>STT;
    cin.ignore(1000, '\n');;
    for (int i = 0; i<AntiHolderSize; i++) {
        if (STT == AntiHolder[i]){
            flag = 1;
            break;
        }
    }
    if (flag == 1){
        cout<<"\nTai lieu da bi danh dau xoa";
        getchar();
        flag = 0;
        continue;
    }
    Search = (*Library)[Holder[STT]];
    if (Search == nullptr) throw ExceptionOutofBound();
    cout<<"\n[1] Xem thong tin"
        <<"\n[2] Them so luong tai lieu"
        <<"\n[3] Xoa tai lieu khoi thu vien"
        <<"\n[4] Chon tai lieu khac"
        <<"\n[0] Ngung"
        << "\nLua chon cua ban: ";
    int breakflag = 1;
    while(breakflag){
    int ChoiceNum = -1;
    cin>> ChoiceNum;
    cin.ignore(1000, '\n');;
        switch (ChoiceNum){
            case 1: Search->DisplaySingle(); break;
            case 2: {
                int Adding;
                cout<<"\nNhap so luong can them: ";
                cin>>Adding;
                Search->data->AddingStockBook(Adding);
            }
            case 3: {
                Library->deleteIndex(Holder[STT]);
                AntiHolder[AntiHolderSize++] = STT;
                break;
            }
            case 4: return;
            default: throw ExceptionInvalidChoice();
            }
        cin.ignore(1000, '\n');;
        }
    }
}

void SearchResources(LinkedList<Resources*>* Library) {
    if (Library->isEmpty()) throw ExceptionEmptyList();
    cout<< "\n------------TIM KIEM------------"
        << "\nChon thuoc tinh tim kiem: "
        << "\n[1] Theo ID"
        << "\n[2] Theo Ten"
        << "\n[3] Theo So luong ton kho"
        << "\n[4] Theo loai tai nguyen"
        << "\n--------------------------------"
        << "\nLua chon: ";
    int TypeVal;
    cin >> TypeVal;
    cin.ignore(1000, '\n');;
    switch (TypeVal){
        case 1: case 2:{
            SearchResstring(Library, TypeVal);
            break;
        }
        case 3: case 4:{
            SearchResint(Library, TypeVal);
            break;
        }
        default: throw ExceptionInvalidVal(TypeVal);
    }
}

bool ResourcesHandle(LinkedList<Resources*>* Library){
    int choice;
    cin >>choice;
    cin.ignore(1000, '\n');;
    switch (choice){
        case 0: return 0;
        case 1:{    ResourcesDisplay(Library);  break;};
        case 2:{    AddResources(Library);      break;};
        case 3:{    DeleteResources(Library);   break;};
        case 4:{    SortResources(Library);     break;};
        case 5:{    SearchResources(Library);   break;};
        default: {  throw ExceptionInvalidChoice()   ;};
    }
    return 1;
}

void ResourcesRun(LinkedList<Resources*>* Library){
    try{
        int runflag = 1;
        while(runflag){
        ResourcesMenu();
        runflag = ResourcesHandle(Library);
        if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
    } catch (const Except &Err){
        cout<<Err.what();
        getchar();
        ResourcesRun(Library);
        }
}

void MemberMenu(){
    system("cls");
    cout << "\n==================================="
         << "\n        QUAN LY THANH VIEN         "
         << "\n==================================="
         << "\n[1] HIEN THI DANH SACH THANH VIEN"
         << "\n[2] DANG KY THANH VIEN MOI"
         << "\n[3] TIM KIEM & XU LY"
         << "\n[4] SAP XEP DANH SACH"
         << "\n[0] QUAY LAI"
         << "\n==================================="
         << "\nLua chon cua ban: ";
}

void MemberDisplay(LinkedList<Member>* MemberList, LinkedList<Transaction>* TransList){    
    do{
        int choice = 0;
        MemberList->display();
        cout<<"\nNhap STT de xem chi tiet, hoac 0 de thoat: ";
        cin>>choice;
        cin.ignore(1000, '\n');;
        if (choice == 0) return;
        Node<Member>* Temp = (*MemberList)[choice];
        if (Temp == nullptr) throw ExceptionOutofBound();
        Temp->DisplaySingle();
        int Amount = Temp->data.TransSize;
        string *MemTransList = Temp->data.getList(0);
        cout<<"Nhap tu 1 den "<<Amount<<" de xem tinh trang the muon, 0 de thoat: ";
        int num = -1;
        cin >> num;
        cin.ignore(1000, '\n');;
        if (num == 0) return;
        if (num < 0 || num > Amount) throw ExceptionOutofBound();
        Transaction TempTrans = *(TransList->SearchItem(Transaction::getStringPtr(TransstringID), MemTransList[num-1]));
        TempTrans.DisplaySingle();
        getchar();
    } while (true);
}

void MemberAdd(LinkedList<Member>* MemberList){
    Member* newMember = Member::newMember(*MemberList);
    if(newMember){
        MemberList->Add(*newMember);
        delete newMember;
    } else {
        cout<<"Tao thanh vien that bai";
    }
}

void MemberSort(LinkedList<Member>* MemberList){
    cout<< "\n-------SAP XEP THANH VIEN-------"
        << "\nChon thuoc tinh sap xep: "
        << "\n[1] Theo ID"
        << "\n[2] Theo Ten"
        << "\n[3] Theo tinh trang hoat dong"
        << "\n--------------------------------"
        << "\nLua chon: ";
    int sortChoice;
    cin >> sortChoice;
    cin.ignore(1000, '\n');;
    switch(sortChoice) {
        case 1: 
            MemberList->SortWrap(Member::getStringPtr(MemberstringID)); 
            break;
        case 2: 
            MemberList->SortWrap(Member::getStringPtr(MemberstringName)); 
            break;
        case 3: 
            MemberList->SortWrap(Member::getIntPtr()); 
            break;
        default: 
            throw ExceptionInvalidChoice();
    }
    cout << "\nDa sap xep xong.";
    MemberList->display();
    getchar();
}

void MemberSearch(LinkedList<Member>* MemberList, LinkedList<Transaction>* TransList, LinkedList<Resources*>* Library){
    if (MemberList->isEmpty()) throw ExceptionEmptyList();
    cout<<"\nNhap ID hoac ten thanh vien: ";
    string Val;
    getline(cin, Val);
    cout<<"\nKieu thong tin muon tim: "
        <<"\n[1] ID"
        <<"\n[2] Ten"
        <<"\nLua chon: ";
    int Type;
    cin>>Type;
    cin.ignore(1000, '\n');;
    if (Type != 1 && Type != 2) throw ExceptionInvalidChoice();
    int Indices[MemberList->Size];
    Node<Member>* current = (*MemberList)[1];
    int currentidx = 1, IndicesSize = 0;
    while (current){
        if (current->data.getString(Type).find(Val) != string::npos){
            Indices[IndicesSize++] = currentidx;
        }
        currentidx++;
        current = current -> next;
    }
    if (IndicesSize == 0){
        cout<<"Khong ton tai du lieu nay";
        getchar();
        return;
    }
    Member::Header();
    for(int i = 0; i < IndicesSize; i++){
        current = (*MemberList)[Indices[i]];
        cout<<"| "<<right<<setfill('0')<<setw(3)<<i+1<<" ";
        current->Display();
    }
    cout<<"\nNhap so thu tu cua thanh vien can xem, hoac thuc hien tra sach";
    cout<<"\nNhan 0 de huy: ";
    int STT;
    cin>>STT;
    cin.ignore(1000, '\n');;
    if (STT == 0) return;
    Node<Member>* CurrItem = (*MemberList)[STT];
    if (CurrItem == nullptr) throw ExceptionOutofBound();
    int choices;
    cout<<"\n[1] Xem thong tin"
        <<"\n[2] Hien thi danh sach cac giao dich"
        <<"\n[3] Thuc hien tra sach"
        <<"\n[4] Chinh sua thong tin"
        <<"\n[0] Ngung"
        <<"\nLua chon: ";
    cin>>choices;
    cin.ignore(1000, '\n');;
    switch (choices){
        case 1:{
            CurrItem->DisplaySingle();
            getchar();
            break;
        }
        case 2:{
            string *CurrentTransactionList = CurrItem->data.getList(0);
            Transaction::Header();
            for(int i = 0; i < CurrItem->data.TransSize; i++){
                Transaction TransItem = *TransList->SearchItem(Transaction::getStringPtr(TransstringID), CurrentTransactionList[i]);
                cout<<"| "<<right<<setfill('0')<<setw(3)<<i+1<<" ";
                TransItem.Display();
            };
            int Number = CurrItem->data.TransSize;
            string *OldTransactionList = CurrItem->data.getList(1);
            for(int i = 0; i < CurrItem->data.HistSize; i++){
                Transaction TransItem = *TransList->SearchItem(Transaction::getStringPtr(TransstringID), OldTransactionList[i]);
                cout<<"| "<<right<<setfill('0')<<setw(3)<<i+1+Number<<" ";
                TransItem.Display();
            }
            Transaction::Footer();
            getchar();
            break;
        }
        case 3:{
            string *CurrentTransactionList = CurrItem->data.getList(0);
            Transaction::Header();
            for(int i = 0; i < CurrItem->data.TransSize; i++){
                Transaction TransItem = *TransList->SearchItem(Transaction::getStringPtr(TransstringID), CurrentTransactionList[i]);
                cout<<"| "<<right<<setfill('0')<<setw(3)<<i+1<<" ";
                TransItem.Display();
            }
            Transaction::Footer();
            int Returningnum;
            cout<<"Nhap STT can tra: ";
            cin>> Returningnum;
            cin.ignore(1000, '\n');;
            if (Returningnum > CurrItem->data.TransSize || Returningnum < 1) throw ExceptionOutofBound();
            Transaction *TransItem = TransList->SearchItem(Transaction::getStringPtr(TransstringID), CurrentTransactionList[Returningnum]);
            CurrItem->data.Returning(CurrentTransactionList[Returningnum]);
            TransItem->ReturnBooks(Library);
            break;
        }
        case 4: {
            CurrItem->data.Edit();
            break;
        }
        case 0: return;
        default: throw ExceptionInvalidChoice();
    }
    
}

bool MemberHandle(LinkedList<Member>* MemberList, LinkedList<Transaction>* TransList, LinkedList<Resources*>* Library){
    int choice;
    cin >>choice;
    cin.ignore(1000, '\n');;
    switch (choice){
        case 0: return 0;
        case 1:{    MemberDisplay(MemberList, TransList);  break;};
        case 2:{    MemberAdd(MemberList);      break;};
        case 3:{    MemberSearch(MemberList, TransList, Library); break;}
        case 4:{    MemberSort(MemberList);     break;};
        default: {  throw ExceptionInvalidChoice()   ;};
    }
    return 1;
}

void MemberRun(LinkedList<Member>* MemberList, LinkedList<Transaction>* TransList, LinkedList<Resources*>* Library){
        try{
        bool runflag = 1;
        while(runflag){
        MemberMenu();
        runflag=MemberHandle(MemberList,TransList,Library);
        if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
            }
        cin.ignore(1000, '\n');;
        }
    } catch (const Except &Err){
        cout<<Err.what();
        getchar();
        MemberRun(MemberList,TransList,Library);
        }
}

void TransactionMenu(){
    system("cls");
    cout << "\n==================================="
         << "\n        QUAN LY MUON TRA           "
         << "\n==================================="
         << "\n[1] HIEN THI DANH SACH GIAO DICH"
         << "\n[2] MUON TAI LIEU"
         << "\n[3] XU LY TRA SACH"
         << "\n[4] NHAN/GIA HAN GIAO DICH"
         << "\n[5] SAP XEP DANH SACH GIAO DICH"
         << "\n[0] QUAY LAI"
         << "\n==================================="
         << "\nLua chon cua ban: ";
}

void TransactionDisplay(LinkedList<Transaction>* TransList){
    do{
        int choice = 0;
        TransList->display();
        cout<<"\nNhap STT de xem chi tiet the muon, hoac 0 de thoat: ";
        cin>>choice;
        cin.ignore(1000, '\n');;
        if (choice == 0) return;
        Node<Transaction>* Temp = (*TransList)[choice];
        if (Temp == nullptr) throw ExceptionOutofBound();
        Temp->DisplaySingle();
        getchar();
    } while (true);
}

void TransactionBorrowing(LinkedList<Member>* MemberList, LinkedList<Transaction>* TransList, LinkedList<Resources*>* Library){
    cout<<"\n-----------------TAO GIAO DICH MOI-----------------"
        <<"\nNhap ID thanh vien can muon: ";
    string memID;
    getline(cin, memID);
    Member* borrow = MemberList->SearchItem(Member::getStringPtr(MemberstringID), memID);
    if (!borrow){
        cout<<"\nKhong ton tai thanh vien voi ID nay";
        getchar();
        return;
    }
    if (borrow->StatusCheck() == SuspendedNum){
        cout<<"\nThanh vien nay dang bi han che";
        getchar();
        return;
    }
    cout<<"\nHinh thuc dat: "
        <<"\n[1] Giao dich tai cho"
        <<"\n[2] Dat truoc";
    int State;
    cin>>State;
    cin.ignore(1000, '\n');;
    cout<<"\nThoi han "
        <<(State-1) ? "lay sach: " : "tra sach: ";
    int days;
    cin>>days;
    cin.ignore(1000, '\n');;
    Transaction newTrans(memID, (State - 1), days, nullptr, 0, Library);
    if (newTrans.NumberofItems > 0){
        TransList->Add(newTrans);
        borrow->AddTrans(newTrans.getID(true));
        cout<<"\nGiao dich thanh cong";
    } else {
        cout << "\nPhieu muon bi huy hoac khong co sach nao duoc chon.";
    }
    getchar();
}

void TransactionReturning(LinkedList<Member>* MemberList, LinkedList<Transaction>* TransList, LinkedList<Resources*>* Library){
    int IntList[TransList->Size];
    int ListSize = 0;
    for(int i = 0; i < TransList->Size; i++){
        Node<Transaction>* Temp = (*TransList)[i+1];
        int Stat = Temp->data.GetStatus();
        if (Stat == Actived || Stat == Overdue){
            IntList[ListSize++] = i+1;
        }
    };
    if (ListSize == 0){
        cout<<"\nKhong co du lieu nay";
        getchar();
        return;
    }
    Transaction::Header();
    for(int i = 0; i < ListSize; i++){    
        cout<<"| "<<right<<setfill('0')<<setw(3)<<i+1<<" ";
        (*TransList)[IntList[i]]->Display();
    }
    cin.ignore(1000, '\n');;
    Transaction::Footer();
    cout<<"\n[1] Tra theo STT"
        <<"\n[2] Tra theo ID"
        <<"\nLua chon: ";
    int choice;
    cin>> choice;
    if (choice != 1 && choice != 2) throw ExceptionInvalidChoice();
    cin.ignore(1000, '\n');;
    string ownerID, transID;
    if (choice == 1){
        int number = 0;
        cout<<"Nhap STT: ";
        Node<Transaction>* Temp = (*TransList)[number-1];
        if (Temp == nullptr) throw ExceptionOutofBound();
        Temp->data.ReturnBooks(Library);
        transID = Temp->data.getID(true);
        ownerID = Temp->data.getID(false);
    } else {
        getline(cin, transID);
        Transaction *Temp = TransList->SearchItem(Transaction::getStringPtr(TransstringID), transID);
        Temp->ReturnBooks(Library);
        ownerID = Temp->getID(false);
    }
    Member *Owner = MemberList->SearchItem(Member::getStringPtr(MemberstringID), ownerID);
    if (Owner){
        Owner->Returning(transID);
    }
    cout<<"Da hoan tat tra sach";
    getchar();
}

void Extend(LinkedList<Transaction>* TransList, LinkedList<Member>* MemberList){
    int IntList[TransList->Size];
    int ListSize = 0;
    for(int i = 0; i < TransList->Size; i++){
        Node<Transaction>* Temp = (*TransList)[i+1];
        int Stat = Temp->data.GetStatus();
        cout<<Stat<<endl;
        if (Stat == Actived || Stat == Overdue){
            IntList[ListSize++] = i+1;
        }
    };
    if (ListSize == 0){
        cout<<"\nKhong co du lieu nay";
        getchar();
        return;
    }
    Transaction::Header();
    for(int i = 0; i < ListSize; i++){    
        cout<<"| "<<right<<setfill('0')<<setw(3)<<i+1<<" ";
        (*TransList)[IntList[i]]->Display();
    }
    Transaction::Footer();
    // cout<<"\n[1] Gia han theo STT"
    //     <<"\n[2] Gia han theo ID"
    //     <<"\nLua chon: ";
    // int choice = 0;
    // cin>> choice;
    // cin.ignore(1000, '\n');;
    // if (choice != 1 && choice != 2) throw ExceptionInvalidChoice();
    // if (choice == 1){
        cout<<"\nNhap STT can gia han: ";
        int STT;
        cin >> STT;
        cin.ignore(1000, '\n');;
        Node<Transaction>* Temp = (*TransList)[IntList[STT-1]];
        if (Temp == nullptr) throw ExceptionOutofBound();
        Temp->data.Revalidate();
    // } else {
    //     string ID;
    //     cout<<"\nNhap ID giao dich can thuc hien: ";
    //     getline(cin, ID);
    //     Transaction *Temp = TransList->SearchItem(Transaction::getStringPtr(TransstringID), ID);
    //     Temp->Revalidate();
    // }
    cout<<"\nDa gia han";
    getchar();
}

void ReserveTake(LinkedList<Transaction>* TransList, LinkedList<Member>* MemberList, LinkedList<Resources*>* Library){
    int IntList[TransList->Size];
    int ListSize = 0;
    for(int i = 0; i < TransList->Size; i++){
        Node<Transaction>* Temp = (*TransList)[i+1];
        int Stat = Temp->data.GetStatus();
        cout << Stat <<endl;
        if (Stat == Reserved){
            IntList[ListSize++] = i+1;
        }
    };
    if (ListSize == 0){
        cout<<"\nKhong co du lieu nay";
        getchar();
        return;
    }
    Transaction::Header();
    for(int i = 0; i < ListSize; i++){    
        cout<<"| "<<right<<setfill('0')<<setw(3)<<i+1<<" ";
        (*TransList)[IntList[i]]->Display();
    }
    Transaction::Footer();
    Transaction *Temp = nullptr;
    cout<<"Nhap STT can thuc hien: ";
    int choice;
    int STT;
    cin >> STT;
    cin.ignore(1000, '\n');;
    Node<Transaction>* Node = (*TransList)[IntList[STT-1]];
    if (Node == nullptr) throw ExceptionOutofBound();
    Temp = &(Node->data);
    cout<<"\nThong tin giao dich:\n";
        Temp->DisplaySingle();
    cout<<"\n[1] Nhan tai lieu"
        <<"\n[2] Huy giao dich"
        <<"\nLua chon: ";
    cin >> choice;
    cin.ignore(1000, '\n');;
    if (choice != 1 && choice != 2) throw ExceptionInvalidChoice();
    if (choice == 1){
    Temp->HandlingStates(Actived, 14);
    cout<< "\nDa xac nhan nhan tai lieu. Trang thai chuyen sang DANG MUON.";
    } else {
    Temp->ReturnBooks(Library);
    Temp->HandlingStates(Cancelled);
    string ownerID = Temp->getID();
    Member* mem = MemberList->SearchItem(Member::getStringPtr(MemberstringID), ownerID);
    if (mem) mem->Cancelling(Temp->getID(true));
    cout<< "\nDa huy giao dich.";
    }
    getchar();
}

void TransactionRevalidate(LinkedList<Transaction>* TransList, LinkedList<Member>* MemberList, LinkedList<Resources*>* Library){
    cout<<"\n[1] Nhan, huy giao dich da dat truoc"
        <<"\n[2] Gia han giao dich"
        <<"\nLua chon: ";
    int Choices;
    cin>>Choices;
    cin.ignore(1000, '\n');;
    if (Choices != 1 && Choices != 2) throw ExceptionInvalidChoice();
    if (Choices == 1)   ReserveTake(TransList, MemberList, Library);
    else                Extend(TransList, MemberList);
}

void SortTrans(LinkedList<Transaction>* TransList){
    cout<< "\nChon thuoc tinh sap xep: "
        << "\n[1] Theo ID"
        << "\n[2] Theo ID chu the"
        << "\n[3] Theo theo thoi gian muon"
        << "\n[4] Theo thoi gian den han"
        << "\n[5] The tinh trang the"
        << "\nLua chon: ";
    int sortChoice;
    cin >> sortChoice;
    cin.ignore(1000, '\n');;
    switch(sortChoice) {
        case 1: 
            TransList->SortWrap(Transaction::getStringPtr(TransstringID)); 
            break;
        case 2: 
            TransList->SortWrap(Transaction::getStringPtr(TransstringOwner));
            break;
        case 3: 
            TransList->SortWrap(Transaction::getDatePtr(TransDateBorrowing));
            break;
        case 4:
            TransList->SortWrap(Transaction::getDatePtr(TransDateDue));
            break;
        case 5:
            TransList->SortWrap(Transaction::getStatePtr());
            break;
        default: 
            throw ExceptionInvalidChoice();
    }
    cout << "\nDa sap xep xong.";
    TransList->display();
    getchar(); cin.ignore(1000, '\n');;
}

bool TransHandle(LinkedList<Member>* MemberList, LinkedList<Transaction>* TransList, LinkedList<Resources*>* Library){
    int choice;
    cin >>choice;
    cin.ignore(1000, '\n');;
    switch (choice){
        case 0: return 0;
        case 1:{    TransactionDisplay(TransList);  break;};
        case 2:{    TransactionBorrowing(MemberList, TransList, Library);      break;};
        case 3:{    TransactionReturning(MemberList, TransList, Library);      break;};
        case 4:{    TransactionRevalidate(TransList, MemberList, Library);     break;};
        case 5:{    SortTrans(TransList);   break;};
        default: {  throw ExceptionInvalidChoice()   ;};
    }
    return 1;
}

void TransactionRun(LinkedList<Member>* MemberList, LinkedList<Transaction>* TransList, LinkedList<Resources*>* Library){
        try{
        bool runflag = 1;
        while(runflag){
        TransactionMenu();
        runflag = TransHandle(MemberList,TransList,Library);
        if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
    } catch (const Except &Err){
        cout<<Err.what();
        getchar();
        TransactionRun(MemberList,TransList,Library);
        }
}

void LibrarianMenuDisplay() {
    system("cls");
    cout << "\n==================================="
         << "\n        THONG TIN CA NHAN          "
         << "\n==================================="
         << "\n[1] XEM THONG TIN"
         << "\n[2] DOI MAT KHAU"
         << "\n[0] QUAY LAI"
         << "\n==================================="
         << "\nLua chon cua ban: ";
}

void LibrarianRun(Librarian* currentUser, LinkedList<Librarian>& libList) {
    while(true) {
        LibrarianMenuDisplay();
        int choice;
        cin >> choice;
        cin.ignore(1000, '\n');;

        switch(choice) {
            case 0: return;
            case 1: 
                cout << "\n--- THONG TIN ---";
                cout << "\n" << *currentUser;
                getchar();
                break;
            case 2: {
                string oldPass, newPass, confirmPass;
                cout << "\n--- DOI MAT KHAU ---";
                cout << "\nNhap mat khau cu: ";
                getline(cin, oldPass);
                if (!currentUser->verifyPassword(oldPass)) {
                    cout << "\nMat khau cu khong dung!";
                } else {
                    cout << "Nhap mat khau moi: ";
                    getline(cin, newPass);
                    cout << "Xac nhan mat khau moi: ";
                    getline(cin, confirmPass);
                    if (newPass == confirmPass) {
                        currentUser->changePassword(newPass);
                        cout << "\nDoi mat khau thanh cong!";
                        FileHandler::SaveFile("librarians.txt", libList); 
                    } else {
                        cout << "\nMat khau xac nhan khong khop.";
                    }
                }
                getchar();
                break;
            }
            default: throw ExceptionInvalidChoice();
        }
    }
}

void MainMenuDisplay() {
    system("cls");
    cout << "\n======================================="
         << "\n    HE THONG QUAN LY THU VIEN (LMS)    "
         << "\n======================================="
         << "\n[1] QUAN LY TAI NGUYEN (SACH/BAO)"
         << "\n[2] QUAN LY THANH VIEN"
         << "\n[3] QUAN LY MUON / TRA"
         << "\n[4] THONG TIN CA NHAN (LIBRARIAN)"
         << "\n[0] LUU DU LIEU VA THOAT"
         << "\n======================================="
         << "\nLua chon cua ban: ";
}

void Checkup(LinkedList<Member>* MemberList, LinkedList<Transaction>* TransList, LinkedList<Resources*>* Library){
    Node<Member> *nodeMem = (*MemberList)[1];
    while(nodeMem){
        nodeMem->data.Checkup();
        nodeMem=nodeMem->next;
    }
    Node<Transaction> *nodeTrans = (*TransList)[1];
    while(nodeTrans){
        nodeTrans->data.Checkup(Library);
        nodeTrans=nodeTrans->next;
    }
}

int main(){
    // Startup();
    // LinkedList<Resources*> LibraryList;
    // LinkedList<Transaction> TransacList;
    // LinkedList<Member> MemberList;
    // FileHandler::LoadResources("resources.txt", LibraryList);
    // FileHandler::LoadMembers("members.txt", MemberList);
    // FileHandler::LoadTransactions("transactions.txt", TransacList);
    // LibraryList.display();
    // TransacList.display();
    // MemberList.display();
    // getchar();
    // Node<Resources*>* firstResourceNode = LibraryList[1];
    // cout<<endl;
    // firstResourceNode->DisplaySingle();
    // MemberList[1]->DisplaySingle();
    // MemberList[2]->DisplaySingle();
    // MemberList[3]->DisplaySingle();
    // cout<<endl;
    // Node<Transaction>* firstTransactionNode = TransacList[1];
    // cout<<endl;
    // firstTransactionNode->DisplaySingle();
    // getchar();
    LinkedList<Librarian> librarianList; 
    FileHandler::LoadLibrarian("librarians.txt", librarianList);
    Librarian* currentUser = nullptr;
    if (!Startup(librarianList, &currentUser)) {
        return 0;
    }
    LinkedList<Resources*> LibraryList;
    LinkedList<Transaction> TransacList;
    LinkedList<Member> MemberList;
    
    cout << "\nDang tai du lieu...";
    FileHandler::LoadResources("resources.txt", LibraryList);
    FileHandler::LoadMembers("members.txt", MemberList);
    FileHandler::LoadTransactions("transactions.txt", TransacList);
    cout << " Hoan tat.\n";
    Checkup(&MemberList, &TransacList, &LibraryList);
    while(true) {
        MainMenuDisplay();
        int choice;
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(1000, '\n');
            continue;
        }
        
        if (choice == 0) {
            cout << "\nDang luu du lieu...";
            FileHandler::SaveFile("resources.txt", LibraryList);
            FileHandler::SaveFile("members.txt", MemberList);
            FileHandler::SaveFile("transactions.txt", TransacList);
            cout << "\nDa luu. Tam biet!";
            break;
        }
        
        switch(choice) {
            case 1: ResourcesRun(&LibraryList); break;
            case 2: MemberRun(&MemberList, &TransacList, &LibraryList); break;
            case 3: TransactionRun(&MemberList, &TransacList, &LibraryList); break;
            case 4: LibrarianRun(currentUser, librarianList); break;
            default: 
                cout << "\nLua chon khong hop le.";
                getchar();
        }
    }
    return 0;
}