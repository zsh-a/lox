#include"LoxFunction.h"
#include<cassert>
LoxObject LoxFunction::call(Interpreter& inter,vector<LoxObject>& args){
    Environment* env = new Environment(inter.globals);
    for(int i = 0;i < decl->params.size();i++){
        env->define(decl->params[i].str,args[i]);
    }
    inter.executeBlock(decl->body,env);
    return nullptr;
}