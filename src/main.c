#include <stdio.h>
#include <assert.h>

#include "debug_heap.h"

void check_func(unsigned int line, char* msg)
{
    printf("HeapCheck on line %d: %s\n", line, msg);
}

void check_alloc_func(unsigned line, unsigned int size)
{
    printf("outstanding allocation from line %d, size %d\n", line, size);
}

#define DEBUG_HEAP
#ifdef DEBUG_HEAP
#define malloc(s) debug_heap_malloc(s, malloc, __LINE__)
#define free(p) debug_heap_free(p, free, check_func)
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
