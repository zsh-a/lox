#ifndef __INTERPRETER__
#define __INTERPRETER__
#include"Ast.h"
#include"LoxObject.h"
#include"Environment.h"
#include<memory>
#include<vector>
class Interpreter:public Visitor,public StmtVisitor{
public:

    Environment* environment = new Environment;

    bool isTruthy(const LoxObject&);

    void checkNumberOperand(const Token&,const LoxObject&);
    void checkNumberOperands(const Token&,const LoxObject&,const LoxObject&);

    LoxObject evaluate(Expr*);
    LoxObject visit(Binary* expr);
	LoxObject visit(Grouping* expr);
	LoxObject visit(Literal* expr);
	LoxObject visit(Unary* expr);
    LoxObject visit(Variable* expr);
    LoxObject visit(Assign* expr);
    string stringify(const LoxObject&);


    void executeBlock(Block*,Environment*);

    void visit(Expression*);
	void visit(Print*);
    void visit(Var*);
    void visit(Block*);
    void execute(Stmt*);
    void interpret(shared_ptr<vector<Stmt*>>);
};

#endif