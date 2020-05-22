#include"LoxObject.h"

bool LoxObject::operator==(void* _o){
    return type == NIL;
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