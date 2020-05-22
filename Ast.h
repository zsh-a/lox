#ifndef __Expr__
#define __Expr__
#include"Token.h"
#include"LoxObject.h"
class Visitor;
class Expr{
public:
	string parenthesize(const string& name,const initializer_list<Expr*>& exprs);
	virtual LoxObject accept(Visitor* visitor) = 0;
	virtual string print() = 0;
	virtual ~Expr(){}
};
class Binary:public Expr{
public:
	Expr* left;
	const Token& op;
	Expr* right;
	Binary(Expr* _left,const Token& _op,Expr* _right):
		left(_left),op(_op),right(_right)
	{

	}

	LoxObject accept(Visitor* visitor);
	~Binary() override{
		delete left;
		delete right;
	}
};
class Grouping:public Expr{
public:
	Expr* expression;
	Grouping(Expr* _expression):expression(_expression){}

	LoxObject accept(Visitor* visitor);
	~Grouping() override {
		delete expression;
	}
};
class Literal:public Expr{
public:

	union{
		double num;
		string str;
	};
	TokenType type;
	Literal(double _num){
		num = _num;
		type = NUMBER;
	}
	Literal(TokenType _type):type(_type){

	}
	Literal(const string& _str):str(_str){
		type =STRING;
	}

	LoxObject accept(Visitor* visitor);
	string print(){
		if(type == NUMBER) return to_string(num);
		return str;
	}

	~Literal()override{

	}
};
class Unary:public Expr {
public:
	const Token& op;
	Expr* right;
	Unary(const Token& _op,Expr* _right):op(_op),right(_right){}

	LoxObject accept(Visitor* visitor);
	~Unary(){
		delete right;
	}
};


class Visitor{
public:
	virtual LoxObject visit(Binary* binary) = 0;
	virtual LoxObject visit(Grouping* grouping) = 0;
	virtual LoxObject visit(Literal* literal) = 0;
	virtual LoxObject visit(Unary* unary) = 0;
};


#endif