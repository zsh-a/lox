#include"Interpreter.h"
#include"Error.h"
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

string Interpreter::stringify(const LoxObject& _o){
    if(_o.type == LoxObject::NIL) return "nil";
    if(_o.type == LoxObject::NUMBER){
        if((double)(long)_o.num == _o.num) return to_string((long)_o.num);
        return to_string(_o.num);
    }
    if(_o.type == LoxObject::BOOLEAN) return _o.boolean?"true":"false";
    return _o.str;
}

void Interpreter::interpret(Expr* expr){

    try{
        auto value = evaluate(expr);
        cout << stringify(value) << endl;
    }catch(RuntimeError e){
        Error::runtimeError(e);
    }

}