#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string.h>
#include <exception>


using namespace std;

class Except: public exception{
    protected:
        string MSG;
    public:
        Except(const string &Msg): MSG(Msg){};
        const char* what() const noexcept{
            return MSG.c_str();
        }
};

class ExceptionIDDuplicate: public Except{
    public:ExceptionIDDuplicate(string Type):
        Except("Loi: Da ton tai ID " + Type + " nay trong du lieu, vui long kiem tra lai"){};
};

#endif // EXCEPTIONS_H