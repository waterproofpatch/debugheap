#ifndef _DEBUG_HEAP_H
#define _DEBUG_HEAP_H

#include <stdlib.h>

void* debug_heap_malloc(size_t size);
void  debug_heap_free(void* ptr);

#endif
