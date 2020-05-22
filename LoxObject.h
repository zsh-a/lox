#ifndef __LOXOBJECT__
#define __LOXOBJECT__
#include<string>
using std::string;
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
    bool operator==(void*);
    ~LoxObject(){}
};

#endif