#ifndef __SCANNER__
#define __SCANNER__
#include"common.h"

enum TokenType{
    // Single-character tokens.
    TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE,
    TOKEN_COMMA, TOKEN_DOT, TOKEN_MINUS, TOKEN_PLUS,
    TOKEN_SEMICOLON, TOKEN_SLASH, TOKEN_STAR,

    // One or two character tokens.
    TOKEN_BANG, TOKEN_BANG_EQUAL,
    TOKEN_EQUAL, TOKEN_EQUAL_EQUAL,
    TOKEN_GREATER, TOKEN_GREATER_EQUAL,
    TOKEN_LESS, TOKEN_LESS_EQUAL,

    // Literals.
    TOKEN_IDENTIFIER, TOKEN_STRING, TOKEN_NUMBER,

    // Keywords.
    TOKEN_AND, TOKEN_CLASS, TOKEN_ELSE, TOKEN_FALSE,
    TOKEN_FOR, TOKEN_FUN, TOKEN_IF, TOKEN_NIL, TOKEN_OR,
    TOKEN_PRINT, TOKEN_RETURN, TOKEN_SUPER, TOKEN_THIS,
    TOKEN_TRUE, TOKEN_VAR, TOKEN_WHILE,

    TOKEN_ERROR,
    TOKEN_EOF
};

struct Token{
    TokenType type;
    const char* start;
    int length;
    int line;
};


struct Scanner
{

    int start = 0,current = 0,line = 1;
    string source;
    Scanner(string& _source):source(_source){}

    bool isAtEnd();

    Token makeToken(TokenType);
    Token errorToken(const string&);
    char advance();
    char peek();
    bool match(char);
    void skipWhitespace();
    Token str();
    Token number();
    Token identifier();
    TokenType identifierType();

    TokenType checkKeyword(int s,int len,const char* rest,TokenType t);
    Token scanToken();
};

#endif