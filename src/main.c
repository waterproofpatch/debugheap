#include <stdio.h>
#include <assert.h>

#include "debug_heap.h"

void check_func(unsigned int line, char* msg)
{
    printf("HeapCheck on line %d: %s\n", line, msg);
}

void check_outstanding_alloc(unsigned line, unsigned int size)
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
    assert(0 == debug_heap_check_outstanding_allocs(check_outstanding_alloc));
    unsigned char* ptr1 = malloc(sizeof(unsigned char));
    unsigned char* ptr2 = malloc(sizeof(unsigned char));
    assert(2 == debug_heap_check_outstanding_allocs(check_outstanding_alloc));
    free(ptr1);
    assert(1 == debug_heap_check_outstanding_allocs(check_outstanding_alloc));
    free(ptr2);
    assert(0 == debug_heap_check_outstanding_allocs(check_outstanding_alloc));
    return 0;
}
