all:token.o error.o scanner.o parser.o main.o ast.o astPrinter.o Environment.o Interpreter.o loxobject.o
	g++ token.o error.o scanner.o ast.o astPrinter.o main.o Interpreter.o Environment.o loxobject.o parser.o -o loxc
scanner.o:Scanner.cc Scanner.h
	g++ Scanner.cc -c -std=c++17 -o scanner.o
token.o:Token.cc Token.h
	g++ Token.cc -c -std=c++17 -o token.o
error.o:Error.cc Error.h
	g++ Error.cc -c -std=c++17 -o error.o
main.o:main.cc 
	g++ main.cc -c -std=c++17 -o main.o
parser.o:Parser.cc Parser.h
	g++ Parser.cc -c -std=c++17 -o parser.o
ast.o:Ast.cc Ast.h
	g++ Ast.cc -c -std=c++17 -o ast.o
astPrinter.o:AstPrinter.cc AstPrinter.h
	g++ AstPrinter.cc -c -std=c++17 -o astPrinter.o
loxobject.o:LoxObject.cc LoxObject.h
	g++ LoxObject.cc -c -std=c++17 -o loxobject.o
Interpreter.o:Interpreter.cc Interpreter.h
	g++ Interpreter.cc -c -std=c++17 -o Interpreter.o
Environment.o:Environment.cc Environment.h 
	g++ Environment.cc -c -std=c++17 -o Environment.o
clean:
	rm *.o
