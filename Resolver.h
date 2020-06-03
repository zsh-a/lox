#ifndef __RESOLVER__
#define __RESOLVER__

#include"Ast.h"
#include"Interpreter.h"
#include<unordered_map>
using namespace std;

class Resolver:public Visitor,public StmtVisitor{
public:
    Interpreter& inter;
    vector<unordered_map<string,bool>> scopes;

    enum FunctionType{
        NONE,FUNCTION
    };

    FunctionType currentFunction = NONE;
    Resolver(Interpreter& _inter):inter(_inter){}
    void beginScope();
    void endScope();
    void resolve(Stmt*);
    void resolve(Expr*);
    void resolve(vector<Stmt*>&);
    void declare(const Token&);
    void define(const Token&);
    void visit(Block*);
    void visit(Var*);
    LoxObject visit(Assign*);
    LoxObject visit(Variable*);
    void visit(Function*);
    void visit(Expression* stmt);
    void visit(If* stmt);
    void visit(Print* stmt);
    void visit(While* stmt);
    void visit(Return*);
    LoxObject visit(Binary* expr);
    LoxObject visit(Call* expr);
    LoxObject visit(Unary* expr);
    LoxObject visit(Grouping* expr);
    void resolveFunction(Function* fun,FunctionType);
    void resolveLocal(Expr* expr,const Token& name);


    LoxObject visit(Literal* literal){
        return nullptr;
    }
};
#endif