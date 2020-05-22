#include"Scanner.h"



unordered_map<string,TokenType> Scanner::keywords = {
    {"and",    AND},
    {"class",  CLASS},
    {"else",   ELSE},
    {"false",  FALSE},
    {"for",    FOR},
    {"fun",    FUN},
    {"if",     IF},
    {"nil",    NIL},
    {"or",     OR},
    {"print",  PRINT},
    {"return", RETURN},
    {"super",  SUPER},
    {"this",   THIS},
    {"true",   TRUE},
    {"var",    VAR},
    {"while",  WHILE}
};

Scanner::Scanner(const string& _source)
    :source(_source)
{

}

bool Scanner::isAtEnd(){
    return current >= source.size();
}

char Scanner::advance(){
    return source[current++];
}

void Scanner::addToken(TokenType _type){
    tokens.emplace_back(Token{_type,line});
}
void Scanner::addToken(TokenType _type,const string& literal){
    tokens.emplace_back(Token{_type,source.substr(start,current -start),literal,line});
}

void Scanner::addToken(TokenType _type,double literal){
    tokens.emplace_back(Token{_type,literal,line});
}

bool Scanner::match(char ch){
    if(isAtEnd()) return false;
    if(source[current] != ch) return false;
    current++;
    return true;
}

char Scanner::peek(){
    if(isAtEnd()) return '\0';
    return source[current];
}
// parse string
void Scanner::str(){
    string s;
    while(peek() != '"' && !isAtEnd()){
        if(peek() == '\n') line++;
        advance();
    }
    if(isAtEnd()){
        // error string
        Error::error(line,"unexpected string literal");
        return;
    }
    
    addToken(STRING,source.substr(start+1,current - start -1));
    advance();
}
char Scanner::peekNext(){
    if(current + 1 < source.size()) return source[current + 1];
    return '\0';
}
void Scanner::number(){
    double num = source[start] - '0';
    while(isdigit(peek())){
        num = num*10 + peek() - '0';
        advance();
    }
    double fnum = 0;
    int base = 10;
    if(peek() == '.' && isdigit(peekNext())){
        advance();
        while(isdigit(peek())){
            fnum += (peek() - '0')*1.0/base;
            base*=10;
            advance();
        }
    }
    addToken(NUMBER,num+fnum);
}
// parse id
void Scanner::identifier(){
    
    while(isalpha(peek())){
        advance();
    }
    string s = source.substr(start,current - start);
    if(auto it = keywords.find(s); it != keywords.end()){
        addToken(it->second);
    }else
        addToken(IDENTIFIER,s);
}
void Scanner::scanToken(){
    char c = advance();
    switch (c)
    {
        case '(':addToken(LEFT_PAREN);break;
        case ')': addToken(RIGHT_PAREN); break;    
        case '{': addToken(LEFT_BRACE); break;     
        case '}': addToken(RIGHT_BRACE); break;    
        case ',': addToken(COMMA); break;          
        case '.': addToken(DOT); break;            
        case '-': addToken(MINUS); break;          
        case '+': addToken(PLUS); break;           
        case ';': addToken(SEMICOLON); break;      
        case '*': addToken(STAR); break; 
        case '!':addToken(match('=')?BANG_EQUAL:BANG);
        case '=': addToken(match('=') ? EQUAL_EQUAL : EQUAL); break;    
        case '<': addToken(match('=') ? LESS_EQUAL : LESS); break;      
        case '>': addToken(match('=') ? GREATER_EQUAL : GREATER); break;
        case '/':
            if(match('/')){
                // comment start
                while(peek() != '\n' && !isAtEnd()) advance();
            }else if(match('*')){
                // match multi comment
                bool isend = false;
                while(true){
                    switch(advance()){
                        case '*':
                            if(peek() == '/'){
                                isend =  true;
                                advance();
                                break;
                            }
                            break;
                        case '\n':line++;break;
                    }
                    if(isend || isAtEnd()) break;
                }
                if(!isend) Error::error(line,"unexpected end with comment");

            }else{
                addToken(SLASH);
            }
            break;
        case '\n':line++;break;
        case ' ':
        case '\t':
        case '\r':break;
        case '"':str();break;
        
    default:
        if(isdigit(c)){
            number();
        }else if(isalpha(c)){
            identifier();
        }else{
            Error::error(line,"unexpected character.");
        }
        
        break;
    }
    
}
const vector<Token>& Scanner::scanTokens(){
    while(!isAtEnd()){
        start = current;
        scanToken();
    }
    tokens.emplace_back(Token{TEOF,line});
    return tokens;
}