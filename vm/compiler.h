#ifndef __COMPILER__
#define __COMPILER__

#include"common.h"
#include"scanner.h"
struct Chunk;
bool compile(string& source,Chunk*);
#endif