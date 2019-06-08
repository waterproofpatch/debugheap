#include <stdio.h>
#include <assert.h>
#include "debug_heap.h"

#define malloc debug_heap_malloc
#define free debug_heap_free

int main(int argc, char** argv)
{
    char* ptr = malloc(sizeof(char));
    assert(NULL != ptr);
    ptr[0] = 'c';
    printf("%p %p\n", ptr, ptr - 1);
    *(char*)(ptr - 1) = 'd';
    assert(ptr[-1] == 'd');
    assert(ptr[0] == 'c');
    free(ptr);
    return 0;
}
