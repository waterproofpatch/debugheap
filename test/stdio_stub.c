#include <stdlib.h>

#include "stdio_stub.h"

void* stub_malloc(size_t size)
{
    return malloc(size);
}

void stub_free(void* ptr)
{
    free(ptr);
}

void stub_check_func(unsigned int line, char* msg)
{
    return;
}