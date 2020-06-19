#include"scanner.h"
#include<cstring>

bool Scanner::isAtEnd(){
    return current >= source.size();
}

Token Scanner::makeToken(TokenType t){
    return {t,source.c_str() + start,current-start,line};
}

Token Scanner::errorToken(const string& s){
    return {TOKEN_ERROR,s.c_str(),s.size(),line};
}

char Scanner::advance(){
    return source[current++];
}

bool Scanner::match(char ch){
    if(isAtEnd()) return false;
    if(source[current] != ch) return false;
    current++;
    return true;
}

char Scanner::peek(){
    return source[current];
}
void Scanner::skipWhitespace(){
    for(;;){
        switch(char c = peek();c){
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            case '\n':
                line++;
                advance();
                break;
            default:
                return;
        }
    }
}

Token Scanner::str(){
    while(peek() != '"' && !isAtEnd()){
        if(peek() == '\n') line++;
        advance();
    }
    if(isAtEnd()) return errorToken("Unterminated string.");
    advance();
    return makeToken(TOKEN_STRING);
}

Token Scanner::number(){
    while(isdigit(peek())) advance();
    if(peek() == '.'){
        advance();
        while(isdigit(peek())) advance();

    } 
    return makeToken(TOKEN_NUMBER);
}

TokenType Scanner::checkKeyword(int s,int len,const char* rest,TokenType t){
    if(current- start == s + len && memcmp(source.c_str() + start + s,rest,len) == 0) return t;
    return TOKEN_IDENTIFIER;
}

TokenType Scanner::identifierType(){
    switch(source[start]){
        case 'a': return checkKeyword(1, 2, "nd", TOKEN_AND);
        case 'c': return checkKeyword(1, 4, "lass", TOKEN_CLASS);
        case 'e': return checkKeyword(1, 3, "lse", TOKEN_ELSE);
        case 'f':
            if(current - start > 1){
                switch(source[start + 1]){
                    case 'a':return checkKeyword(2,3,"lse",TOKEN_FALSE);
                    case 'o': return checkKeyword(2, 1, "r", TOKEN_FOR);
                    case 'u': return checkKeyword(2, 1, "n", TOKEN_FUN);
                }

            }
            break;
        case 'i': return checkKeyword(1, 1, "f", TOKEN_IF);
        case 'n': return checkKeyword(1, 2, "il", TOKEN_NIL);
        case 'o': return checkKeyword(1, 1, "r", TOKEN_OR);
        case 'p': return checkKeyword(1, 4, "rint", TOKEN_PRINT);
        case 'r': return checkKeyword(1, 5, "eturn", TOKEN_RETURN);
        case 's': return checkKeyword(1, 4, "uper", TOKEN_SUPER);
        case 't':
            if (current - start > 1) {
                switch (source[start + 1]) {
                case 'h': return checkKeyword(2, 2, "is", TOKEN_THIS);
                case 'r': return checkKeyword(2, 2, "ue", TOKEN_TRUE);
                }
            }
            break;
        case 'v': return checkKeyword(1, 2, "ar", TOKEN_VAR);
        case 'w': return checkKeyword(1, 4, "hile", TOKEN_WHILE);
        

    }
}

Token Scanner::identifier(){
    while(isalpha(peek()) || isdigit(peek())) advance();
    return makeToken(identifierType());
}

Token Scanner::scanToken(){
    skipWhitespace();
    start = current;

    if(isAtEnd()) return makeToken(TOKEN_EOF);

    char c = advance();
    if (isalpha(c)) return identifier();
    if(isdigit(c)) return number();
    switch(c){

        case '(': return makeToken(TOKEN_LEFT_PAREN);
        case ')': return makeToken(TOKEN_RIGHT_PAREN);
        case '{': return makeToken(TOKEN_LEFT_BRACE);
        case '}': return makeToken(TOKEN_RIGHT_BRACE);
        case ';': return makeToken(TOKEN_SEMICOLON);
        case ',': return makeToken(TOKEN_COMMA);
        case '.': return makeToken(TOKEN_DOT);
        case '-': return makeToken(TOKEN_MINUS);
        case '+': return makeToken(TOKEN_PLUS);
        case '*': return makeToken(TOKEN_STAR);
        case '!':
            return makeToken(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
        case '=':
            return makeToken(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
        case '<':
            return makeToken(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
        case '>':
            return makeToken(match('=') ?
                        TOKEN_GREATER_EQUAL : TOKEN_GREATER);
        case '/':
            if(match('/')){
                while(peek() != '\n' && !isAtEnd()) advance();
            }else{
                return makeToken(TOKEN_SLASH);
            }
            break;
        case '"': return str();
        default:
            break;

    }
    return errorToken("Unexpected character.");
}