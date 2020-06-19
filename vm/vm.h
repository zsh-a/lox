#ifndef __VM__
#define __VM__

#include"common.h"
#include<memory>
#include"chunk.h"
#include<stack>
enum InterpretResult{
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
};

struct VM{  
    Chunk* chunk;
    int ip = 0;
    vector<Value> stk;

    uint8_t read_byte();
    Value read_constant();
    InterpretResult interpret(Chunk*);
    InterpretResult run();
};


#endif