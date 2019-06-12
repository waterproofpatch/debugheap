#ifndef _DEBUG_HEAP_H
#define _DEBUG_HEAP_H

#include <stdlib.h>

#define DEBUG_HEAP_HEADER_COOKIE 0x11223344
#define DEBUG_HEAP_FOOTER_COOKIE 0x44332211

typedef struct _heap_info_t
{
    unsigned int num_allocs;
    unsigned int num_frees;
    unsigned int cur_alloc;
} heap_info_t;

typedef struct _heap_meta_t
{
    unsigned int  size;
    unsigned int  alloc_num;
    unsigned int  header_cookie;
    unsigned char payload[0];
} heap_meta_t;

void* debug_heap_malloc(size_t size, void* (*malloc_fptr)(size_t size));
void  debug_heap_free(void* ptr, void (*free_fptr)(void* ptr));

#endif
