#ifndef __TOKEN__
#define __TOKEN__


#include<string>
#include<iostream>
using namespace std;
enum TokenType{
    // Single-character tokens.                      
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // One or two character tokens.                  
    BANG, BANG_EQUAL,                                
    EQUAL, EQUAL_EQUAL,                              
    GREATER, GREATER_EQUAL,                          
    LESS, LESS_EQUAL,                                

    // Literals.                                     
    IDENTIFIER, STRING, NUMBER,                      

    // Keywords.                                     
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,  
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,    

    TEOF                              
};

class Token{
public:
    TokenType type;
    string lexeme;


    union{
        double num;
        string str;
    };


    int line;

    //Token(const Token&) = default;
    Token(TokenType _type,int _line);

    Token(const Token& _tk);
    Token(TokenType _type,double _num,int _line);
    Token(TokenType _type,const string& _lexeme,const string& _str,int _line);
    ~Token(){

    }
};


#endif