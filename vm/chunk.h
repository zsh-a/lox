#ifndef __CHUNK__
#define __CHUNK__

#include"common.h"
#include"value.h"
using namespace std;
enum OpCode{
    OP_CONSTANT, 
     
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,

    OP_NEGATE,


    OP_RETURN,
};

struct Chunk{
    vector<uint8_t> code;
    ValueVector constants;
    vector<int> lines;
    void add(uint8_t,int);
    int addConstant(Value);

    int disassemble(int offset);
    void disassemble(const string&);
 
    
    int simpleInstruction(const string& name,int offset);
    int constantInstruction(const string& name,int offset);
};

#endif