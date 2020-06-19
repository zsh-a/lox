#include"compiler.h"


bool compile(string& source,Chunk* chunk){
    Scanner scanner(source);
    int line = -1;
    for(;;){
        Token token = scanner.scanToken();
        if (token.line != line) {
            printf("%4d ", token.line);
            line = token.line;
        } else {
            printf("   | ");
        }
        //cout << token.length << endl;
        printf("%2d '%.*s'\n", token.type, token.length, token.start); 

        if (token.type == TOKEN_EOF) break;
    }

}