#include <stdio.h>
#include <assert.h>
#include "debug_heap.h"

#define DEBUG_HEAP

#ifdef DEBUG_HEAP
#define malloc(s) debug_heap_malloc(s, malloc)
#define free(p) debug_heap_free(p, free)
#endif

int main(int argc, char** argv)
{
    unsigned char* ptr = malloc(sizeof(unsigned char));
    assert(NULL != ptr);
    ptr[0] = 'c';
    assert(ptr[0] == 'c');
    free(ptr);
    return 0;
}
