#pragma once
#include <cstdlib>
#include <iostream> 

void makeAllocator(size_t maxSize);
char* alloc(size_t size);
void reset();
