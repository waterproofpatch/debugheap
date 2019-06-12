#ifndef _STDIO_STUB_H
#define _STDIO_STUB_H

#include <stdio.h>

void* stub_malloc(size_t size);
void  stub_free(void* ptr);
void  stub_check_func(unsigned int line, char* msg);

#endif
