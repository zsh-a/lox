#ifndef __INTERPRETER__
#define __INTERPRETER__
#include"Ast.h"
#include"LoxObject.h"
#include"Environment.h"
#include<memory>
#include<vector>
class Interpreter:public Visitor,public StmtVisitor{
public:
    Environment* globals = new Environment;
    Environment* environment = globals;

    // var binding
    unordered_map<Expr*,int> locals;

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
    LoxObject visit(Call*);
    string stringify(const LoxObject&);


    void executeBlock(Block*,Environment*);

    void visit(Expression*);
	void visit(Print*);
    void visit(Var*);
    void visit(Block*);
    void visit(If*);
    void visit(While*);
    void visit(Function*);
    void visit(Return*);
    void execute(Stmt*);
    void interpret(shared_ptr<vector<Stmt*>>);

    void resolve(Expr* expr,int depth);


    LoxObject lookUpVariable(const Token& name,Expr* expr);
};

class ReturnValue{
public:
    LoxObject obj;
    ReturnValue(const LoxObject& _obj):obj(_obj){}
};

#endif