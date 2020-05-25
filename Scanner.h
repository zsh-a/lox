#ifndef __SCANNER__
#define __SCANNER__
#include<vector>
#include<unordered_map>
#include"Token.h"
#include"Error.h"
class Scanner{
public:
    string source;
    vector<Token> tokens;

    
    static unordered_map<string,TokenType> keywords;
    int line = 1;
    int start = 0,current = 0;
    bool isAtEnd();
    void scanToken();
    char advance();
    bool match(char ch);
    char peek();
    char peekNext();
    void str();
    void number();
    void identifier();
    void addToken(TokenType _type);
    void addToken(TokenType _type,const string& literal);
    void addToken(TokenType _type,double literal);
    Scanner(const string& _source);
    vector<Token>& scanTokens();
};
#endif