#include<iostream>
#include<string>
#include"Scanner.h"
#include<vector>
#include<fstream>
#include"Parser.h"
#include<sstream>
#include"AstPrinter.h"
#include"Interpreter.h"
using namespace std;

ostream& operator<<(ostream& os,const Token& tk){
    os << "{type:" << tk.type;
    if(tk.type == IDENTIFIER || tk.type == STRING){
        os << ",value:\"" << tk.str <<"\"}" << endl;
    }else if(tk.type == NUMBER)
        os << ",value:"<<tk.num<<"}" << endl;
    else
        os <<  "}"<<endl;
    return os;
}


void run(const string& source,Interpreter& inter){
    Scanner scanner{source};
    //cout << source << endl;
    auto tokens = scanner.scanTokens();

    Parser parser(tokens);
    auto ast = parser.parse();
    if(Error::errorNum) return;
    
    inter.interpret(ast);
    //cout << ast->print() << endl;
}

void runPrompt(){
    string s;
    Interpreter inter;
    for(;;){
        printf("> ");
        getline(cin,s);
        run(s,inter);
    }
}
void runFile(const char* file){
    ifstream f(file);
    stringstream ss;
    ss << f.rdbuf();
    Interpreter inter;
    run(string{ss.str()},inter);
}
int main(int argc,char** argv){
    if(argc == 1){
        runPrompt();
    }else if(argc == 2){
        runFile(argv[1]);
    }

    
    // Expr* e = new Binary(                     
    //     new Unary(                                    
    //         Token{MINUS, "-", "", 1},      
    //         new Literal(123)),                        
    //     Token(STAR, "*", "", 1),           
    //     new Grouping(                                 
    //         new Literal(45.67)));
    //Expr* e = new Binary(new Literal(3),Token(PLUS,"+","",1),new Literal(5));
    //Interpreter inter;
    //inter.interpret(e);
    //cout << e->print();
}