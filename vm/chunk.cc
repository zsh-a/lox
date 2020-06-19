#include"chunk.h"

void Chunk::add(uint8_t byte,int line){
    code.push_back(byte);
    lines.push_back(line);
}

int Chunk::addConstant(Value v){
    constants.push_back(v);
    return constants.size() -1;
}
int Chunk::simpleInstruction(const string& name,int offset){
    cout << name << endl;
    return offset + 1;
}



int Chunk::constantInstruction(const string& name,int offset){
    uint8_t constant = code[offset + 1];
    printf("%-16s %4d '", name.c_str(), constant);
    printValue(constants[constant]);
    printf("\n");
    return offset + 2;
}
int Chunk::disassemble(int offset){
    printf("%04d ", offset);
    if (offset > 0 && lines[offset] == lines[offset - 1]) {
        printf("   | ");
    } else {
        printf("%4d ", lines[offset]);
    }
    uint8_t inst = code[offset];
    switch(inst){
        case OP_RETURN:
            return simpleInstruction("OP_RETURN",offset);
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT",offset);
        case OP_NEGATE:
            return simpleInstruction("OP_NEGATE",offset);
        case OP_ADD:
            return simpleInstruction("OP_ADD", offset);
        case OP_SUBTRACT:
            return simpleInstruction("OP_SUBTRACT", offset);
        case OP_MULTIPLY:
            return simpleInstruction("OP_MULTIPLY", offset);
        case OP_DIVIDE:
            return simpleInstruction("OP_DIVIDE", offset);
        default:
            printf("Unknown opcode %d\n", inst);
        return offset + 1;
    }
}

void Chunk::disassemble(const string& name){
    printf("== %s ==\n", name.c_str());
    for(int i = 0;i < code.size();){
        i = disassemble(i);
    }
}