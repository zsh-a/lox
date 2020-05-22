#ifndef __ERROR__
#define __ERROR__
#include<string>
#include"Token.h"
using std::string;
class Error{
public:
    static int errorNum;;
    static void error(int line,const string& message);
    static void error(const Token& tk,const string& msg);
    static void report(int line,const string& where,const string& message);
};
#endif