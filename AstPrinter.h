#ifndef __ASTPRINTER__
#define __ASTPRINTER__
#include"Token.h"
#include"Ast.h"
#include"LoxObject.h"
class AstPrinter:public Visitor{
public:
	
	string parenthesize(const string& name,const initializer_list<Expr*>& exprs);
	LoxObject visit(Binary* expr);
	LoxObject visit(Grouping* expr);
	LoxObject visit(Literal* expr);
	LoxObject visit(Unary* expr);

};
#endif