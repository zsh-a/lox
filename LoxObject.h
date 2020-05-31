#ifndef __LOXOBJECT__
#define __LOXOBJECT__
#include<string>
class LoxFunction;
using std::string;
#define ESP 1e-5
class LoxObject{
public:
    enum Type{
        NIL,BOOLEAN,NUMBER,STRING,INTEGER,FUNCTION
    };
    Type type;

    string str;
    double num;
    bool boolean;
    int integer;
    LoxFunction* fun;

    LoxObject();
    LoxObject(const LoxObject&);
    LoxObject& operator=(const LoxObject&);
    LoxObject(const string&);
    LoxObject(double);
    LoxObject(int);
    LoxObject(bool);
    explicit LoxObject(LoxFunction*);
    LoxObject(void*);
    bool operator==(const LoxObject&);
    bool operator!=(const LoxObject&);

};

#endif