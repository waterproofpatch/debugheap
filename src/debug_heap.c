#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "debug_heap.h"

heap_info_t g_heap_info = {0};

void* debug_heap_malloc(size_t size, void* (*malloc_fptr)(size_t size))
{
    heap_meta_t* meta =
        malloc_fptr(sizeof(heap_meta_t) + size + sizeof(unsigned int));
    if (!meta)
    {
        return NULL;
    }
    memset(meta, 0, sizeof(heap_meta_t));
    meta->size          = size;
    meta->alloc_num     = ++g_heap_info.num_allocs;
    meta->header_cookie = DEBUG_HEAP_HEADER_COOKIE;
    *(unsigned int*)((unsigned char*)meta + sizeof(heap_meta_t) + size) =
        DEBUG_HEAP_FOOTER_COOKIE;
    printf("DEBUG_HEAP_MALLOC: total allocs: %u alloc num %u, size %u\n",
           g_heap_info.num_allocs, meta->alloc_num, meta->size);
    return meta->payload;
}

void debug_heap_free(void* ptr, void (*free_fptr)(void* ptr))
{
    heap_meta_t* meta =
        (heap_meta_t*)((unsigned char*)ptr - sizeof(heap_meta_t));
    g_heap_info.num_frees++;
    assert(meta->header_cookie == DEBUG_HEAP_HEADER_COOKIE);
    assert(*(unsigned int*)((unsigned char*)meta + meta->size +
                            sizeof(heap_meta_t)) == DEBUG_HEAP_FOOTER_COOKIE);
    printf("DEBUG_HEAP_FREE: total frees: %u freeing %u, size %u\n",
           g_heap_info.num_frees, meta->alloc_num, meta->size);

    return free_fptr(meta);
}
