#ifndef __Environment__
#define __Environment__
#include<unordered_map>
#include"LoxObject.h"
#include"Token.h"
using std::unordered_map;
class Environment{
public:
    // scope list pointer
    Environment* enclosing;
    unordered_map<string,LoxObject> values;

    Environment(){
        enclosing = nullptr;
    }
    Environment(Environment* _enclosing):enclosing(_enclosing){}
    
    void define(const string&,const LoxObject&);
    LoxObject get(const Token&);
    LoxObject get(const string&);
    void assign(const Token&,const LoxObject&);
    Environment* ancestor(int dist);
    LoxObject getAt(int dist,const string& name);
    void assignAt(int dist,const Token&,LoxObject v);
    ~Environment(){
        
    }
};
#endif