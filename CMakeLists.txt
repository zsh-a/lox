cmake_minimum_required(VERSION 3.0.0)
project(lox VERSION 0.1.0)

include(CTest)
enable_testing()
add_definitions(-std=c++17)
add_executable(loxc Ast.cc AstPrinter.cc Environment.cc Error.cc Interpreter.cc LoxObject.cc main.cc Parser.cc Scanner.cc Token.cc LoxFunction.cc)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
