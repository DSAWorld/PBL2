#include <iostream>

using namespace std;

template <typename Type> bool Comp(const Type &A, const Type &B, bool &Asc){
    if (Asc) return A < B; else return A > B;
}

template <typename Type> void Swap(Type &A, Type &B){
    Type Temp = A;
    A = B;
    B = Temp;
}

template <typename ClassType, typename MemberType> 
int Partition(ClassType A[], MemberType ClassType::*memberPtr, int low, int high, bool &Asc){
    ClassType &Obj[] = A[(high+low)/2];
    int i = low - 1;
    for(int j = low; j <= high - 1; j++){
        if(Comp(A[i].*memberPtr,A[j].*memberPtr, Asc)){
            i++;
            Swap(A[i]; A[j]);
        }
    }
    Swap(A[++i], A[high]);
    return i;
}

template <typename ClassType, typename MemberType>
void Sort(ClassType A[], MemberType ClassType::*memberPtr, int low, int high, bool &Asc){
    if (low < high){
        int Point = Partition(A, low, high, memberPtr);
        Sort(A, low, Point - 1, memberPtr, Asc);
        Sort(A, Point + 1, high, memberPtr, Asc);
    }
}

template <typename ClassType, typename MemberType>
int SortWrap(ClassType A[], MemberType ClassType::*memberPtr, int size){
    if(A == nullptr || size < 1){
        cout<<"\nDanh sach rong";
        return 0;
    }
    int Choice = -1;
    cout<<"\nNhap lua chon:"
        <<"\n[0] khong sort"
        <<"\n[1] tang dan"
        <<"\n[2] giam dan";
    while(true){
        cin>>Choice;
        switch(Choice){
            case 0: return 0;
            case 1: {Sort(A, memberPtr, 0, size-1, 1); return 1}
            case 2: {Sort(A, memberPtr, 0, size-1, 0); return 1}
            default: {cout<<"\nKhong hop le";}
        }
    }
}