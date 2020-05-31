#ifndef __PARSER__
#define __PARSER__
#include"Token.h"
#include<vector>
#include"Error.h"
#include"Ast.h"
#include<memory>
/*
    expression     → equality ;
    equality       → comparison ( ( "!=" | "==" ) comparison )* ;
    comparison     → addition ( ( ">" | ">=" | "<" | "<=" ) addition )* ;
    addition       → multiplication ( ( "-" | "+" ) multiplication )* ;
    multiplication → unary ( ( "/" | "*" ) unary )* ;
    unary          → ( "!" | "-" ) unary
                | primary ;
    primary        → NUMBER | STRING | "false" | "true" | "nil"
                | "(" expression ")" ;

*/

class Parser{
public:
    // error handle
    class ParseError{

    };
    ParseError error(const Token& tk,const string& msg){
        Error::error(tk,msg);
        return ParseError();
    }

    const vector<Token>& tokens;
    int current = 0;

    Parser(const vector<Token>& _tokens);


    const Token& peek(){return tokens[current];}
    const Token& previous(){return tokens[current-1];}
    bool isAtEnd(){return peek().type == TEOF;}
    const Token& consume(TokenType _type,const string& msg);


    const Token& advance(){
        if(!isAtEnd()) current++; 
        return previous();
    }
    bool check(TokenType _type){
        if(isAtEnd()) return false;
        return _type == peek().type;
    }
    bool match(const initializer_list<TokenType>& t);


    // error recovery
    void synchronize();

    shared_ptr<vector<Stmt*>> parse();

    Stmt* declaration();
    Stmt* varDeclaration();
    Stmt* statement();
    Stmt* printStatement();
    Stmt* expressionStatement();
    Stmt* ifStatement();
    Stmt* whileStatement();
    Stmt* forStatement();
    Stmt* returnStatement();

    Stmt* function(const string&);
    Stmt* block();
    Expr* expression(){return assignment();}

    Expr* logic_or();
    Expr* logic_and();
    Expr* assignment();
    Expr* equality();
    Expr* comparison();
    Expr* addition();
    Expr* multiplication();
    Expr* unary();
    Expr* call();

    Expr* primary();

    Expr* finishCall(Expr*);
};


#endif