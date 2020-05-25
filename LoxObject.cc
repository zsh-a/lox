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
    switch(type){
        case STRING:str = _o.str;break;
        case NUMBER:num = _o.num;break;
        case BOOLEAN:boolean = _o.boolean;
    }
}

LoxObject& LoxObject::operator=(const LoxObject& _o){
    type = _o.type;
    switch(type){
        case STRING:str = _o.str;break;
        case NUMBER:num = _o.num;break;
        case BOOLEAN:boolean = _o.boolean;
    }
    return *this;
}