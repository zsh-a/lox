#include"error.h"
#include"scanner.h"

bool Error::hasError = false;;

void Error::errorAtCurrent(Parser& parser,const string&msg){
    errorAt(parser,parser.current,msg);
}

void Error::errorAt(Parser& parser,Token& token,const string&msg){

    if(parser.panicMode) return;
    parser.panicMode = true;
    parser.hasError = true;

    fprintf(stderr, "[line %d] Error", token.line);
    if (token.type == TOKEN_EOF) {
        fprintf(stderr, " at end");
    } else if (token.type == TOKEN_ERROR) {
    // Nothing.
    } else {
        fprintf(stderr, " at '%.*s'", token.length, token.start);
    }
    fprintf(stderr, ": %s\n", msg);
    hasError = true;
}

void Error::error(Parser& parser,const string&msg){
    errorAt(parser,parser.previous,msg);
}