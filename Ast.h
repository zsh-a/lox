#ifndef __Expr__
#define __Expr__
#include"Token.h"
#include<vector>
using std::vector;
#include"LoxObject.h"
class Visitor;
class Expr{
public:
	string parenthesize(const string& name,const initializer_list<Expr*>& exprs);
	virtual LoxObject accept(Visitor* visitor) = 0;
	virtual ~Expr(){}
};
class Binary:public Expr{
public:
	Expr* left;
	const Token op;
	Expr* right;
	Binary(Expr* _left,const Token& _op,Expr* _right):
		left(_left),op(_op),right(_right)
	{

	}

	LoxObject accept(Visitor* visitor);
	~Binary(){
		delete left;
		delete right;
	}
};
class Grouping:public Expr{
public:
	Expr* expression;
	Grouping(Expr* _expression):expression(_expression){}

	LoxObject accept(Visitor* visitor);
	~Grouping() {
		delete expression;
	}
};
class Literal:public Expr{
public:

	double num;
	string str;
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

};
class Unary:public Expr {
public:
	const Token op;
	Expr* right;
	Unary(const Token& _op,Expr* _right):op(_op),right(_right){}

	LoxObject accept(Visitor* visitor);
	~Unary(){
		delete right;
	}
};

class Variable :public Expr{
public:
	const Token name;
	Variable(const Token& _name):name(_name){}
	LoxObject accept(Visitor* visitor);
};

class Assign:public Expr{
public:
	const Token name;
	Expr* value;
	Assign(const Token& _name,Expr* _value):name(_name),value(_value){}
	LoxObject accept(Visitor* visitor);
};


class Visitor{
public:
	virtual LoxObject visit(Binary* binary) = 0;
	virtual LoxObject visit(Grouping* grouping) = 0;
	virtual LoxObject visit(Literal* literal) = 0;
	virtual LoxObject visit(Unary* unary) = 0;
	virtual LoxObject visit(Variable* unary) = 0;
	virtual LoxObject visit(Assign* unary) = 0;
};
/*
	program     → declaration* EOF ;

	declaration → varDecl
				| statement ;

	statement → exprStmt
          | printStmt
          | block ;

	block     → "{" declaration* "}" ;
*/
class StmtVisitor;
class Stmt{
public:
	virtual void accept(StmtVisitor* visitor) = 0;
};

class Expression :public Stmt{
public:
	Expr* expression;
	Expression(Expr* expr):expression(expr){}
	void accept(StmtVisitor* visitor);
	~Expression(){
		delete expression;
	}
};

class Print :public Stmt{
public:
	Expr* expression;
	Print(Expr* expr):expression(expr){}
	void accept(StmtVisitor* visitor);
	~Print(){
		delete expression;
	}
};

class Var :public Stmt{
public:
	const Token name;
	Expr* initializer;
	Var(const Token& _name,Expr* _expr):name(_name),initializer(_expr){}
	void accept(StmtVisitor* visitor);
};

class Block:public Stmt{
public:
	vector<Stmt*> statements;
	Block(){}
	Block(initializer_list<Stmt*> _o){
		for(auto it:_o) statements.push_back(it);
	}
	void accept(StmtVisitor* visitor);
};

class If:public Stmt{
public:
	Expr* condition;
	Stmt* thenBranch,*elseBranch;
	If(Expr* _condition,Stmt* _thenBranch,Stmt*_elseBranch)
		:condition(_condition),thenBranch(_thenBranch),elseBranch(_elseBranch){}
	void accept(StmtVisitor* visitor);
};

class While:public Stmt{
public:
	Expr* condition;
	Stmt* body;
	While(Expr* _condition,Stmt* _body)
		:condition(_condition),body(_body){}
	void accept(StmtVisitor* visitor);
};

class StmtVisitor{
public:
	virtual void visit(Expression*) = 0;
	virtual void visit(Print*) = 0;
	virtual void visit(Var*) = 0;
	virtual void visit(Block*) = 0;
	virtual void visit(If*) = 0;
	virtual void visit(While*) = 0;
};




#endif