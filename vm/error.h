#ifndef __ERROR__
#define __ERROR__
#include"common.h"
#include"compiler.h"
struct Error{
    static bool hasError;
    static void errorAtCurrent(Parser& parser,const string&msg);
    static void errorAt(Parser& parser,Token& token,const string&msg);
    static void error(Parser& parser,const string&msg);
};
#endif