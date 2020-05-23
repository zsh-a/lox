#ifndef __ERROR__
#define __ERROR__
#include<string>
#include"Token.h"
using std::string;


class RuntimeError:public runtime_error{
public:
    const Token& token;
    RuntimeError(const Token&,const string msg);
};
class Error{
public:
    static int errorNum;;

    static bool hadRuntimeError;
    static void error(int line,const string& message);
    static void error(const Token& tk,const string& msg);
    static void report(int line,const string& where,const string& message);
    static void runtimeError(RuntimeError error);
};


#endif