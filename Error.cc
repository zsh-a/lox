#include"Error.h"
#include<iostream>

using namespace std;

int Error::errorNum = 0;

void Error::error(int line,const string& message){
    errorNum++;
    report(line,"",message);
}

void Error::report(int line,const string& where,const string& message){
    cout << "[line " << line <<"] ERROR " << where <<": "<<message<<endl;
}

void Error::error(const Token& tk,const string& msg){
    errorNum++;
    if(tk.type == TEOF)
        report(tk.line," at end ",msg);
    else
        report(tk.line," at '" + tk.lexeme +"'",msg);
}
bool Error::hadRuntimeError = false;
void Error::runtimeError(RuntimeError error){
    cout << error.what() << endl << "[line " << error.token.line <<"]" << endl;
    hadRuntimeError = true;
}
RuntimeError::RuntimeError(const Token& _tk,const string msg):runtime_error(msg),token(_tk){
    
}