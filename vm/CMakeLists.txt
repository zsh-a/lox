cmake_minimum_required(VERSION 3.0.0)
project(vm VERSION 0.1.0)

include(CTest)
enable_testing()
add_definitions(-std=c++17)
add_executable(vm chunk.cc vm.cc common.cc compiler.cc scanner.cc error.cc main.cc)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
