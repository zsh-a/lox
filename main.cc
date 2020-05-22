#include<iostream>
#include<string>
#include"Scanner.h"
#include<vector>
#include<fstream>
#include"Parser.h"
#include<sstream>
#include"AstPrinter.h"
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


void run(const string& source){
    Scanner scanner{source};
    auto& tokens = scanner.scanTokens();


    for(auto& it:tokens){
        cout << it << endl;
    }
    Parser parser(tokens);
    auto ast = parser.parse();
    if(Error::errorNum) return;
    AstPrinter p;
    ast->accept(&p);
    //cout << ast->print() << endl;
}

void runPrompt(){
    string s;
    for(;;){
        printf("> ");
        getline(cin,s);
        run(s);
    }
}
void runFile(const char* file){
    ifstream f(file);
    stringstream ss;
    ss << f.rdbuf();
    run(string{ss.str()});
}
int main(int argc,char** argv){
    // if(argc == 1){
    //     runPrompt();
    // }else if(argc == 2){
    //     runFile(argv[1]);
    // }

    
    Expr* e = new Binary(                     
        new Unary(                                    
            Token{MINUS, "-", "", 1},      
            new Literal(123)),                        
        Token(STAR, "*", "", 1),           
        new Grouping(                                 
            new Literal(45.67)));
    //Expr* e = new Binary(new Literal(3),Token(PLUS,"+","",1),new Literal(5));
    AstPrinter p;
    cout << e->accept(&p).str;
    //cout << e->print();
}