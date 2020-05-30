#ifndef __LOXFUNCTION__
#define __LOXFUNCTION__
#include"Ast.h"
#include"Interpreter.h"
using namespace std;
#include<vector>
class LoxFunction{
public:
    Function* decl;
    LoxFunction(Function* _decl):decl(_decl){}
    LoxObject call(Interpreter&,vector<LoxObject>&);
};

#endif