#include"Interpreter.h"
#include"Error.h"
#include"LoxFunction.h"
#include<cassert>
LoxObject Interpreter::evaluate(Expr* expr){
    return expr->accept(this);
}

bool Interpreter::isTruthy(const LoxObject& _obj){
    if(_obj.type == LoxObject::NIL) return false;
    if(_obj.type == LoxObject::BOOLEAN) return _obj.boolean;
    return true;
}

void Interpreter::checkNumberOperand(const Token& _tk,const LoxObject& _o){
    if(_o.type == LoxObject::NUMBER) return;
    throw RuntimeError(_tk,"Operand must be a number");
}

void Interpreter::checkNumberOperands(const Token& _tk,const LoxObject& _o1,const LoxObject& _o2){
    if(_o1.type == LoxObject::NUMBER && _o2.type == LoxObject::NUMBER) return;
    throw RuntimeError(_tk,"Operand must be a number");
}

LoxObject Interpreter::visit(Binary* expr){
    auto left = evaluate(expr->left);

    if(expr->op.type == OR){
        if(isTruthy(left)) return left;
        else return evaluate(expr->right);
    }else if(expr->op.type == AND){
        if(!isTruthy(left)) return left;
        else return evaluate(expr->right);
    }

    auto right = evaluate(expr->right);

    switch(expr->op.type){
        case MINUS:
            checkNumberOperands(expr->op,left,right);
            return left.num - right.num;
        case SLASH:
            checkNumberOperands(expr->op,left,right);
            return left.num / right.num;
        case STAR: 
            checkNumberOperands(expr->op,left,right);
            return left.num * right.num;
        case PLUS:
            if(left.type == LoxObject::NUMBER && right.type == LoxObject::NUMBER){
                return left.num + right.num;
            }
            return stringify(left) + stringify(right);
            
            throw RuntimeError(expr->op, "Operands must be two numbers or two strings.");
        case GREATER:
            checkNumberOperands(expr->op,left,right);
            return left.num > right.num;
        case GREATER_EQUAL:
            checkNumberOperands(expr->op,left,right);
            return left.num >= right.num;
        case LESS:
            checkNumberOperands(expr->op,left,right);
            return left.num < right.num;
        case LESS_EQUAL: 
            checkNumberOperands(expr->op,left,right);
            return left.num <= right.num;
        case BANG_EQUAL: return left != right;
    }
    return nullptr;
}

LoxObject Interpreter::visit(Grouping* expr){
    return evaluate(expr->expression);
}

LoxObject Interpreter::visit(Literal* expr){

    switch (expr->type)
    {
    case STRING:return expr->str;
    case NUMBER: return expr->num;
    case NIL: return LoxObject();
    default:
        break;
    }
    
}

LoxObject Interpreter::visit(Unary* expr){
    auto obj = evaluate(expr->right);

    switch (expr->op.type)
    {
    case MINUS:
        checkNumberOperand(expr->op,obj);
        return -obj.num;
    case BANG: return !obj.boolean;
    }
    return nullptr;
}


LoxObject Interpreter::visit(Variable* expr){
    return environment->get(expr->name);
}

LoxObject Interpreter::visit(Assign* expr){
    auto value = evaluate(expr->value);
    environment->assign(expr->name,value);
    return value;
}

string Interpreter::stringify(const LoxObject& _o){
    if(_o.type == LoxObject::NIL) return "nil";
    if(_o.type == LoxObject::NUMBER){
        if((double)(long)_o.num == _o.num) return to_string((long)_o.num);
        return to_string(_o.num);
    }
    if(_o.type == LoxObject::BOOLEAN) return _o.boolean?"true":"false";
    return _o.str;
}


void Interpreter::execute(Stmt* stmt){
    stmt->accept(this);
}

void Interpreter::interpret(shared_ptr<vector<Stmt*>> stmts){

    try{
        for(auto stmt:*stmts){
            execute(stmt);
        }
    }catch(RuntimeError e){
        Error::runtimeError(e);
    }

}

void Interpreter::visit(Expression* expr){
    evaluate(expr->expression);
}

void Interpreter::visit(Print* print){
    auto obj = evaluate(print->expression);
    cout << stringify(obj) << endl;
}

void Interpreter::visit(Var* stmt){
    LoxObject obj;
    
    if(stmt->initializer){
        
        obj = evaluate(stmt->initializer);
    }
    
    environment->define(stmt->name.lexeme,obj);
}

void Interpreter::executeBlock(Block* stmts,Environment* env){
    auto old = environment;
    // enter scope 
    environment = env;
    for(Stmt* stmt:stmts->statements){
        execute(stmt);
    }
    // leavel scope
    environment = old;
    delete env;
}

void Interpreter::visit(Block* stmts){
    executeBlock(stmts,new Environment(environment));
}

void Interpreter::visit(If* stmt){
    if(isTruthy(evaluate(stmt->condition))){
        execute(stmt->thenBranch);
    }else{
        execute(stmt->elseBranch);
    }
}

void Interpreter::visit(While* stmt){
    while(isTruthy(evaluate(stmt->condition))){
        execute(stmt->body);
    }
}

LoxObject Interpreter::visit(Call* expr){

    LoxObject callee = evaluate(expr->callee);
    //cout << callee.fun->decl->name<< endl;
    vector<LoxObject> args;
    for(auto it:expr->args){
        args.push_back(evaluate(it));
    }
    
    return callee.fun->call(*this,args);
}

void Interpreter::visit(Function* stmt){
    LoxFunction* fun = new LoxFunction(stmt);
    auto obj = LoxObject(fun);
    environment->define(stmt->name.str,obj);
}