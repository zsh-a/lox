#ifndef __COMPILER__
#define __COMPILER__

#include"common.h"
#include"scanner.h"
struct Chunk;

struct Parser{
    Token current,previous;
    Scanner& scanner;

    bool hasError = false;
    bool panicMode = false;
    Parser(Scanner& sc):scanner(sc){}
    void comsume(TokenType type, const string& message);
    void advance();
};

enum Precedence{
  PREC_NONE,
  PREC_ASSIGNMENT,  // =
  PREC_OR,          // or
  PREC_AND,         // and
  PREC_EQUALITY,    // == !=
  PREC_COMPARISON,  // < > <= >=
  PREC_TERM,        // + -
  PREC_FACTOR,      // * /
  PREC_UNARY,       // ! -
  PREC_CALL,        // . ()
  PREC_PRIMARY
} ;

struct Compiler{
    using ParseFn = void (Compiler::*)();

    struct ParseRule{
        ParseFn prefix;
        ParseFn infix;
        Precedence precedence;
    };


    ParseRule rules[40] = {
        { &Compiler::grouping, NULL,    PREC_NONE },       // TOKEN_LEFT_PAREN
        { NULL,     NULL,    PREC_NONE },       // TOKEN_RIGHT_PAREN
        { NULL,     NULL,    PREC_NONE },      // TOKEN_LEFT_BRACE
        { NULL,     NULL,    PREC_NONE },       // TOKEN_RIGHT_BRACE
        { NULL,     NULL,    PREC_NONE },       // TOKEN_COMMA
        { NULL,     NULL,    PREC_NONE },       // TOKEN_DOT
        { &Compiler::unary,    &Compiler::binary,  PREC_TERM },       // TOKEN_MINUS
        { NULL,     &Compiler::binary,  PREC_TERM },       // TOKEN_PLUS
        { NULL,     NULL,    PREC_NONE },       // TOKEN_SEMICOLON
        { NULL,     &Compiler::binary,  PREC_FACTOR },     // TOKEN_SLASH
        { NULL,     &Compiler::binary,  PREC_FACTOR },     // TOKEN_STAR
        { NULL,     NULL,    PREC_NONE },       // TOKEN_BANG
        { NULL,     NULL,    PREC_NONE },       // TOKEN_BANG_EQUAL
        { NULL,     NULL,    PREC_NONE },       // TOKEN_EQUAL
        { NULL,     NULL,    PREC_NONE },       // TOKEN_EQUAL_EQUAL
        { NULL,     NULL,    PREC_NONE },       // TOKEN_GREATER
        { NULL,     NULL,    PREC_NONE },       // TOKEN_GREATER_EQUAL
        { NULL,     NULL,    PREC_NONE },       // TOKEN_LESS
        { NULL,     NULL,    PREC_NONE },       // TOKEN_LESS_EQUAL
        { NULL,     NULL,    PREC_NONE },       // TOKEN_IDENTIFIER
        { NULL,     NULL,    PREC_NONE },       // TOKEN_STRING
        { &Compiler::number,   NULL,    PREC_NONE },       // TOKEN_NUMBER
        { NULL,     NULL,    PREC_NONE },       // TOKEN_AND
        { NULL,     NULL,    PREC_NONE },       // TOKEN_CLASS
        { NULL,     NULL,    PREC_NONE },       // TOKEN_ELSE
        { NULL,     NULL,    PREC_NONE },       // TOKEN_FALSE
        { NULL,     NULL,    PREC_NONE },       // TOKEN_FOR
        { NULL,     NULL,    PREC_NONE },       // TOKEN_FUN
        { NULL,     NULL,    PREC_NONE },       // TOKEN_IF
        { NULL,     NULL,    PREC_NONE },       // TOKEN_NIL
        { NULL,     NULL,    PREC_NONE },       // TOKEN_OR
        { NULL,     NULL,    PREC_NONE },       // TOKEN_PRINT
        { NULL,     NULL,    PREC_NONE },       // TOKEN_RETURN
        { NULL,     NULL,    PREC_NONE },       // TOKEN_SUPER
        { NULL,     NULL,    PREC_NONE },       // TOKEN_THIS
        { NULL,     NULL,    PREC_NONE },       // TOKEN_TRUE
        { NULL,     NULL,    PREC_NONE },       // TOKEN_VAR
        { NULL,     NULL,    PREC_NONE },       // TOKEN_WHILE
        { NULL,     NULL,    PREC_NONE },       // TOKEN_ERROR
        { NULL,     NULL,    PREC_NONE },       // TOKEN_EOF
    };

    ParseRule* getRule(TokenType);

    Chunk& chunk;
    Parser& parser;
    Compiler(Chunk& _chunk,Parser& _parser):chunk(_chunk),parser(_parser){}
    bool compile();
    void number();
    void grouping();
    void unary();
    void expression();

    void parsePrecedence(Precedence precedence);
    void binary();
    uint8_t makeConstant(Value );
    void emitConstant(double);
    void emit(uint8_t);
    void emit(uint8_t,uint8_t);
};

#endif