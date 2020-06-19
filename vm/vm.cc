#include"vm.h"

InterpretResult VM::interpret(Chunk* _chunk){
    chunk = _chunk;
    ip = 0;
    return run();
}
uint8_t VM::read_byte(){
    return chunk->code[ip++];
}

Value VM::read_constant(){
    return chunk->constants[read_byte()];
}
InterpretResult VM::run(){

#define BINARY_OP(op)\
    do{\
        double b = stk.back();stk.pop_back();\
        double a = stk.back();stk.pop_back();\
        stk.push_back(a op b);\
    }while(0)

    for(;;){
#ifdef DEBUG_TRACE_EXECUTION
        printf("          ");
        for(int i = 0;i < stk.size();i++){
            printf("[ ");
            printValue(stk[i]);
            printf(" ]");
        }
        printf("\n");
        chunk->disassemble(ip);
#endif

        switch(uint8_t instruction = read_byte();instruction){
            case OP_CONSTANT:{
                Value c = read_constant();
                stk.push_back(c);
                break;
            }
            case OP_NEGATE:{
                Value v = stk.back();stk.pop_back();
                stk.push_back(-v);
                break;
            }
            case OP_ADD:BINARY_OP(+);break;
            case OP_SUBTRACT:BINARY_OP(-);break;
            case OP_MULTIPLY:BINARY_OP(*);break;
            case OP_DIVIDE:BINARY_OP(/);break;
            case OP_RETURN:{
                printValue(stk.back());stk.pop_back();
                printf("\n");
                return INTERPRET_OK;
            }
        }

    }
#undef BINARY_OP
}