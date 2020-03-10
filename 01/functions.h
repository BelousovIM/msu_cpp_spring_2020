#pragma once
#include <cstdlib>
#include <iostream> 
#include <cmath> 

void makeAllocator(size_t maxSize);
char* alloc(size_t size);
void reset();
