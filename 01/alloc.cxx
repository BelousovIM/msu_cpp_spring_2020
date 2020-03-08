#include "functions.h"

static char* s_head;
static int s_tail = 0, s_maxSize;

void makeAllocator(size_t maxSize)
{
	s_head = (char*) malloc(maxSize);
	s_maxSize = maxSize;
}

char* alloc(size_t size)
{
	if (s_tail + size > s_maxSize)
		return nullptr;
	s_tail += size;
	return s_head + (s_tail - size);
}

void reset()
{
	s_tail = 0;
}

