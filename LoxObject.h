#ifndef __LOXOBJECT__
#define __LOXOBJECT__
#include<string>
using std::string;
#define ESP 1e-5
class LoxObject{
public:
    enum Type{
        NIL,BOOLEAN,NUMBER,STRING
    };
    Type type;
    union 
    {
        string str;
        double num;
        bool boolean;
    };
    LoxObject();
    LoxObject(const LoxObject&){};
    LoxObject(const string&);
    LoxObject(double);
    LoxObject(bool);
    LoxObject(void*);
    bool operator==(const LoxObject&);
    bool operator!=(const LoxObject&);
    ~LoxObject(){}
};

#endif