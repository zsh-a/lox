#include"Environment.h"

#include"Error.h"
void Environment::define(const string& name,const LoxObject& o){
    values[name] = o;
}
LoxObject Environment::get(const Token& _tk){
    if(auto it = values.find(_tk.lexeme);it != values.end()){
        return it->second;
    }
    // search in next scope
    if(enclosing) return enclosing->get(_tk);

    throw RuntimeError(_tk,"Undefined variable '" + _tk.lexeme+"'.");
}

void Environment::assign(const Token& name,const LoxObject& obj){
    if(auto it = values.find(name.lexeme);it != values.end()){
        it->second = obj;
        return;
    }
    if(enclosing){
        enclosing->assign(name,obj);
        return; 
    }

    throw RuntimeError(name,"Undefined variable '" + name.lexeme + "'.");
}