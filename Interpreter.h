#ifndef __INTERPRETER__
#define __INTERPRETER__
#include"Ast.h"
#include"LoxObject.h"

class Interpreter:public Visitor{
public:
    bool isTruthy(const LoxObject&);

    void checkNumberOperand(const Token&,const LoxObject&);
    void checkNumberOperands(const Token&,const LoxObject&,const LoxObject&);

    LoxObject evaluate(Expr*);
    LoxObject visit(Binary* expr);
	LoxObject visit(Grouping* expr);
	LoxObject visit(Literal* expr);
	LoxObject visit(Unary* expr);

    string stringify(const LoxObject&);

    void interpret(Expr*);
};

#endif