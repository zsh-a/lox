#include"Parser.h"
#include"Error.h"
Parser::Parser(const vector<Token>& _tokens)
    :tokens(_tokens)
{

}

const Token& Parser::consume(TokenType _type,const string& msg){
    if(check(_type)) return advance();
    throw error(peek(),msg);
}

bool Parser::match(const initializer_list<TokenType>& arg){
    for(auto& a:arg){
        if(check(a)){
            advance();
            return true;
        }
    }
    return false;
}


Expr* Parser::parse(){

    try{
        return expression();
    }catch(ParseError error){
        return nullptr;
    }
}
Expr* Parser::equality(){
    Expr* expr = comparison();
    while(match({BANG_EQUAL,EQUAL_EQUAL})){
        const Token& op = previous();
        Expr* right = comparison();
        expr = new Binary(expr,op,right);
    }
    
    return expr;
}

Expr* Parser::comparison(){
    Expr* expr = addition();
    while(match({GREATER, GREATER_EQUAL, LESS, LESS_EQUAL})){
        const Token& op = previous();
        Expr* right = addition();
        expr = new Binary(expr,op,right);
    }
    return expr;
}

Expr* Parser::addition(){
    Expr* expr = multiplication();
    while(match({MINUS, PLUS})){
        const Token& op = previous();
        Expr* right = multiplication();
        expr = new Binary(expr,op,right);
    }
    return expr;
}

Expr* Parser::multiplication(){
    Expr* expr = unary();
    while(match({SLASH, STAR})){
        const Token& op = previous();
        Expr* right = unary();
        expr = new Binary(expr,op,right);
    }
    return expr;
}

Expr* Parser::unary(){
    if(match({BANG, MINUS})){
        const Token& op = previous();
        Expr* right = unary();
        return new Unary(op,right);
    }
    return primary();
}

Expr* Parser::primary(){
    if(match({FALSE})) return new Literal(FALSE);
    if(match({TRUE})) return new Literal(TRUE);
    if(match({NIL})) return new Literal(NIL);
    if(match({STRING})) return new Literal(previous().str);
    if(match({NUMBER})) return new Literal(previous().num);
    if(match({LEFT_PAREN})){
        Expr* expr = expression();
        consume(RIGHT_PAREN,"Expect ')' after expression");
        return new Grouping(expr);
    }
    throw error(peek(),"Expect expression");
}

void Parser::synchronize(){
    advance();
    while(!isAtEnd()){
        if(previous().type == SEMICOLON) return;
        switch(peek().type){
            case CLASS:                            
            case FUN:                              
            case VAR:                              
            case FOR:                              
            case IF:                               
            case WHILE:                            
            case PRINT:                            
            case RETURN:
                return;
        }
        advance();
    }
}