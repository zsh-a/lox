all:token.o error.o scanner.o parser.o main.o ast.o astPrinter.o loxobject.o
	g++ token.o error.o scanner.o ast.o astPrinter.o main.o loxobject.o parser.o -o loxc
scanner.o:Scanner.cc
	g++ Scanner.cc -c -std=c++17 -o scanner.o
token.o:Token.cc
	g++ Token.cc -c -std=c++17 -o token.o
error.o:Error.cc
	g++ Error.cc -c -std=c++17 -o error.o
main.o:main.cc 
	g++ main.cc -c -std=c++17 -o main.o
parser.o:Parser.cc
	g++ Parser.cc -c -std=c++17 -o parser.o
ast.o:Ast.cc
	g++ Ast.cc -c -std=c++17 -o ast.o
astPrinter.o:AstPrinter.cc
	g++ AstPrinter.cc -c -std=c++17 -o astPrinter.o
loxobject.o:LoxObject.cc
	g++ LoxObject.cc -c -std=c++17 -o loxobject.o
clean:
	rm *.o
