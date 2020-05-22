#include"Token.h"

Token::Token(TokenType _type,int _line)
    :type(_type),line(_line)
{

}
Token::Token(const Token& _tk):line(_tk.line),type(_tk.type),lexeme(_tk.lexeme){
    if(type == NUMBER) num = _tk.num;
    else if(type == STRING || type == IDENTIFIER) str = _tk.str; 
}
Token::Token(TokenType _type,double _num,int _line)
    :type(_type),num(_num),line(_line)
{

}

Token::Token(TokenType _type,const string& _lexeme,const string& _str,int _line)
    :type(_type),lexeme(_lexeme),str(_str),line(_line)
{

}

