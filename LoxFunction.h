#ifndef __LOXFUNCTION__
#define __LOXFUNCTION__
#include"Ast.h"
#include"Interpreter.h"
using namespace std;
#include<vector>
class LoxFunction{
public:
    Function* decl;
    // for function closure
    Environment* closure;
    LoxFunction(Function* _decl,Environment* _closure):decl(_decl),closure(_closure){}
    LoxObject call(Interpreter&,vector<LoxObject>&);
};

#endif