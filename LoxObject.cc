#include"LoxObject.h"

bool LoxObject::operator==(const LoxObject& _o){
    if(type == NIL && _o.type == NIL) return true;
    if(type == NIL || _o.type == NIL) return false;
    if(type == NUMBER) return abs(num - _o.num) < ESP;
    if(type == STRING) return str == _o.str;


    return false;
}

bool LoxObject::operator!=(const LoxObject& _o){
    return !(*this == _o);
}

LoxObject::LoxObject(const string& _str):type(STRING),str(_str){
    
}

LoxObject::LoxObject(double _d):type(NUMBER){
    num = _d;
}

LoxObject::LoxObject(bool _b):type(BOOLEAN),boolean(_b){

}

LoxObject::LoxObject(void*):type(NIL){

}

LoxObject::LoxObject():type(NIL){

}

LoxObject::LoxObject(const LoxObject& _o):type(_o.type){

    str = _o.str;
    num = _o.num;
    boolean = _o.boolean;
    fun = _o.fun;
}

LoxObject& LoxObject::operator=(const LoxObject& _o){
    type = _o.type;
    str = _o.str;
    num = _o.num;
    boolean = _o.boolean;
    fun = _o.fun;
    return *this;
}
#include<iostream>
#include"LoxFunction.h"
using namespace std;
LoxObject::LoxObject(LoxFunction* _fun):type(FUNCTION),fun(_fun){
    
}