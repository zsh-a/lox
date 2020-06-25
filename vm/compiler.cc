#include"compiler.h"
#include"error.h"
#include"chunk.h"
void Parser::comsume(TokenType type, const string& message){
    if(current.type == type) {
        advance();
        return;
    }   
    Error::errorAtCurrent(*this,message);
}
void Parser::advance(){
    previous = current;
    for(;;){
        current = scanner.scanToken();
        if(current.type != TOKEN_ERROR)break;

        Error::errorAtCurrent(*this,current.start);
    }
}

void Compiler::emit(uint8_t v){
    chunk.add(v,parser.previous.line);
}

void Compiler::emit(uint8_t v1,uint8_t v2){
    emit(v1);
    emit(v2);
}

uint8_t Compiler::makeConstant(Value v){
    
    int constant = chunk.addConstant(v);
    if (constant > UINT8_MAX) {
        Error::error(parser,"Too many constants in one chunk.");
        return 0;
    }
    return constant;
}

void Compiler::emitConstant(double value){
    emit(OP_CONSTANT,makeConstant(value));
}
void Compiler::number(){
    double value = strtod(parser.previous.start,NULL);
    emitConstant(value);
}
 
void Compiler::grouping(){
    expression();
    parser.comsume(TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
}

void Compiler::unary(){
    TokenType opType = parser.previous.type;

    parsePrecedence(PREC_UNARY);

    switch(opType){
        case TOKEN_MINUS:emit(OP_NEGATE);break;
        default:
            return;
    }
}

void Compiler::parsePrecedence(Precedence precedence){
    parser.advance();
    ParseFn prefixRule = getRule(parser.previous.type)->prefix;
    if(!prefixRule){
        Error::error(parser,"Expect expression.");
        return;
    }
    (this->*prefixRule)();
    
    while(precedence <= getRule(parser.current.type)->precedence){
        parser.advance();
        ParseFn infixRule = getRule(parser.previous.type)->infix;
        (this->*infixRule)();
    }

}

void Compiler::expression(){
    parsePrecedence(PREC_ASSIGNMENT);
}


void Compiler::binary(){
    TokenType opType = parser.previous.type;

    auto rule = getRule(opType);
    parsePrecedence((Precedence)(rule->precedence + 1));
    switch(opType){
        case TOKEN_PLUS:emit(OP_ADD);break;
        case TOKEN_MINUS:emit(OP_SUBTRACT);break;
        case TOKEN_STAR:emit(OP_MULTIPLY);break;
        case TOKEN_SLASH:emit(OP_DIVIDE);break;
        default:
            return;
    } 
}

Compiler::ParseRule* Compiler::getRule(TokenType type){
    return &rules[type];
}

bool Compiler::compile(){


    parser.advance();
    expression();
    parser.comsume(TOKEN_EOF, "Expect end of expression.");
    // string source = "1 + 2";
    // Scanner scanner(source);
    // int line = -1;
    // for(;;){
    //     Token token = scanner.scanToken();
    //     if (token.line != line) {
    //         printf("%4d ", token.line);
    //         line = token.line;
    //     } else {
    //         printf("   | ");
    //     }
    //     //cout << token.length << endl;
    //     printf("%2d '%.*s'\n", token.type, token.length, token.start); 

    //     if (token.type == TOKEN_EOF) break;
    // }
    emit(OP_RETURN);
    return !parser.hasError;
}