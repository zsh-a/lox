#include"LoxFunction.h"
#include<cassert>
LoxObject LoxFunction::call(Interpreter& inter,vector<LoxObject>& args){
    Environment* env = new Environment(closure);
    for(int i = 0;i < decl->params.size();i++){
        env->define(decl->params[i].str,args[i]);
    }
    try{

        inter.executeBlock(decl->body,env);
    }catch(ReturnValue r){
        //cout << r.obj.type << endl;
        return r.obj;
    }
    return nullptr;
}