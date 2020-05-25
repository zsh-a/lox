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

Stmt* Parser::printStatement(){
    Expr* value = expression();
    consume(SEMICOLON,"expect ';' after value.");
    return new Print(value);
}

Stmt* Parser::expressionStatement(){
    Expr* expr = expression();  
    consume(SEMICOLON,"expect ';' after expression.");
    return new Expression(expr);
}

Expr* Parser::assignment(){
    Expr* expr = equality();
    
    if(match({EQUAL})){
        auto& equals = previous();
        // recursive parse 
        Expr* value = assignment();
        if(dynamic_cast<Variable*>(expr)){
            const Token name = ((Variable*)expr)->name;
            return new Assign(name,value);
        }
        Error::error(equals,"Invalid assignment target.");
    }
    return expr;
}

Stmt* Parser::block(){
    Block* stmts = new Block;
    while(!check(RIGHT_BRACE) && !isAtEnd()){
        stmts->statements.push_back(declaration());
    }
    consume(RIGHT_BRACE,"Expect '}' after block");
    return stmts;
}

Stmt* Parser::statement(){

    if(match({PRINT})) return printStatement();
    if(match({LEFT_BRACE})) return block();
    return expressionStatement();
}
// varDecl → "var" IDENTIFIER ( "=" expression )? ";" ;
Stmt* Parser::varDeclaration(){
    auto& name = consume(IDENTIFIER,"Expect a variable name");
    Expr* init = nullptr;
    if(match({EQUAL})){
        init = expression();
    }
    consume(SEMICOLON,"Expect ';' after variable declaration");
    return new Var(name,init);
}
/*
    program     → declaration* EOF ;

    declaration → varDecl
                | statement ;

    statement   → exprStmt
                | printStmt ;
*/
Stmt* Parser::declaration(){
    try{
        if(match({VAR})){
            return varDeclaration();
        }
        return statement();
    }catch(ParseError e){
        synchronize();
        return nullptr;
    }
}
shared_ptr<vector<Stmt*>> Parser::parse(){

    auto stmts = make_shared<vector<Stmt*>>();
    while(!isAtEnd()){
        stmts->push_back(declaration());
    }
    return stmts;
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
    if(match({IDENTIFIER})) return new Variable(previous()); 
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