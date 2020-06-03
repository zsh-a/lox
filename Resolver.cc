#include"Resolver.h"
#include"Error.h"
void Resolver::beginScope(){
    scopes.emplace_back();
}

void Resolver::endScope(){
    scopes.pop_back();
}
void Resolver::resolve(vector<Stmt*>& stmts){
    for(auto it: stmts){
        resolve(it);
    }
}

void Resolver::resolve(Expr* expr){
    expr->accept(this);
}
void Resolver::resolve(Stmt* stmt){
    stmt->accept(this);
}

void Resolver::visit(Block* stmt){
    beginScope();
    resolve(stmt->statements);
    endScope();
}

void Resolver::declare(const Token& name){
    if(scopes.empty()) return;
    auto& it = scopes.back();
    if(it.count(name.lexeme)) Error::error(name,"Variable with this name already declared in this scope.");
    it.insert({name.lexeme,false});
}

void Resolver::define(const Token& name){
    if(scopes.empty()) return;
    auto& it = scopes.back();
    it[name.lexeme] = true;
}

void Resolver::resolveLocal(Expr* expr,const Token& name){
    int n = scopes.size();
    for(int i = n-1;i >=0;--i){
        if(scopes[i].count(name.lexeme)){
            inter.resolve(expr,n-i-1);
            return;
        }
    }
}

LoxObject Resolver::visit(Variable* expr){
    if(scopes.size()){
        // cout << scopes.back()[expr->name.lexeme] << endl;
        if(auto it = scopes.back().find(expr->name.lexeme);it != scopes.back().end() && it->second == false){
            Error::error(expr->name,"Cannot read local variable in its own initializer.");
        }
    }
    resolveLocal(expr,expr->name);
    return nullptr;
}
void Resolver::visit(Var* stmt){
    declare(stmt->name);
    if(stmt->initializer){
        resolve(stmt->initializer);
    }
    define(stmt->name);
}

LoxObject Resolver::visit(Assign* expr){
    resolve(expr->value);
    resolveLocal(expr,expr->name);
    return nullptr;
}

void Resolver::resolveFunction(Function* fun,FunctionType t){
    auto enclosingFunction = currentFunction;
    currentFunction = t;
    beginScope();
    for(auto& it:fun->params){
        declare(it);
        define(it);
    }
    resolve(fun->body);
    endScope();
    currentFunction = enclosingFunction;
}

void Resolver::visit(Function* fun){

    declare(fun->name);
    define(fun->name);
    resolveFunction(fun,FUNCTION);
}

void Resolver::visit(Expression* stmt){
    resolve(stmt->expression);

}

void Resolver::visit(If* stmt){
    resolve(stmt->condition);
    resolve(stmt->thenBranch);
    if(stmt->elseBranch) resolve(stmt->elseBranch);
}

void Resolver::visit(Print* stmt){
    if(stmt->expression)
        resolve(stmt->expression);
}

void Resolver::visit(Return* stmt){
    if(currentFunction != FUNCTION)
        Error::error(stmt->keyword,"Cannot return from top-level code.");
    
    if(stmt->expr)
        resolve(stmt->expr);
}

void Resolver::visit(While* stmt){
    resolve(stmt->condition);
    resolve(stmt->body);
}

LoxObject Resolver::visit(Binary* expr){
    resolve(expr->left);
    resolve(expr->right);
    return nullptr;
}

LoxObject Resolver::visit(Call* expr){
    resolve(expr->callee);

    for(auto it:expr->args){
        resolve(it);
    }
    return nullptr;
}

LoxObject Resolver::visit(Grouping* expr){
    resolve(expr->expression);
    return nullptr;
}

LoxObject Resolver::visit(Unary* expr){
    resolve(expr->right);
    return nullptr;
}