#ifndef __INTERPRETER__
#define __INTERPRETER__
#include"Ast.h"
#include"LoxObject.h"

class Interpreter:public Visitor{
public:
    LoxObject visit(Binary* expr);
	LoxObject visit(Grouping* expr);
	LoxObject visit(Literal* expr);
	LoxObject visit(Unary* expr);
};

#endif