#ifndef __LOXOBJECT__
#define __LOXOBJECT__
#include<string>
class LoxFunction;
using std::string;
#define ESP 1e-5
class LoxObject{
public:
    enum Type{
        NIL,BOOLEAN,NUMBER,STRING,FUNCTION
    };
    Type type;

    string str;
    double num;
    bool boolean;
    LoxFunction* fun;

    LoxObject();
    LoxObject(const LoxObject&);
    LoxObject& operator=(const LoxObject&);
    LoxObject(const string&);
    LoxObject(double);
    LoxObject(bool);
    explicit LoxObject(LoxFunction*);
    LoxObject(void*);
    bool operator==(const LoxObject&);
    bool operator!=(const LoxObject&);

};

#endif