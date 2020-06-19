#include"chunk.h"

#include<iostream>
#include<string>
#include"vm.h"
#include<fstream>
#include<sstream>
#include"compiler.h"
// int main(){
//     VM vm;
//     Chunk chunk;
//     chunk.add(OP_CONSTANT,123);
//     int c = chunk.addConstant(1.2);
//     chunk.add(c,123);
//     chunk.add(OP_CONSTANT,123);
//     c = chunk.addConstant(3.4);
//     chunk.add(c,123);
//     chunk.add(OP_ADD,123);
//     chunk.add(OP_CONSTANT,123);
//     c = chunk.addConstant(5.6);
//     chunk.add(c,123);
//     chunk.add(OP_DIVIDE,123);

//     chunk.add(OP_NEGATE,123);
//     chunk.add(OP_RETURN,123);
//     vm.interpret(&chunk);
// }
VM vm;
InterpretResult interpret(string& source){
    Chunk chunk;

    if(!compile(source,&chunk)) return INTERPRET_COMPILE_ERROR;

    vm.chunk = &chunk;

    InterpretResult result = vm.run();

    return result;
}
void repl(){
    string s;
    for(;;){
        printf("> ");
        getline(cin,s);
        interpret(s);
    }
}

void runFile(const char* path){
    ifstream f(path);
    stringstream ss;
    ss << f.rdbuf();

}


int main(int argc,char** argv){
    if(argc == 1)
        repl();
    else if(argc == 2){
        runFile(argv[1]);
    }


}