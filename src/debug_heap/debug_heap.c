#include <stdlib.h>
#include <string.h>

#include "debug_heap.h"
#include "list.h"

heap_info_t g_heap_info = {.num_allocs              = 0,
                           .num_frees               = 0,
                           .cur_alloc               = 0,
                           .outstanding_allocations = NULL};

static char debug_heap_check_proxy(void* context, void* data)
{
    void (*check_alloc_fptr)(unsigned int, unsigned int) = context;
    heap_meta_t* meta                                    = (heap_meta_t*)data;
    check_alloc_fptr(meta->line, meta->size);
    return 1;
}

unsigned int debug_heap_check_outstanding_allocs(
    void (*check_alloc_fptr)(unsigned int line, unsigned int size))
{
    if (!g_heap_info.outstanding_allocations)
    {
        return 0;
    }
    list_foreach(g_heap_info.outstanding_allocations, (void*)check_alloc_fptr,
                 debug_heap_check_proxy);
    return 0;
}

void* debug_heap_malloc(size_t size,
                        void* (*malloc_fptr)(size_t size),
                        unsigned int line)
{
    if (!g_heap_info.outstanding_allocations)
    {
        g_heap_info.outstanding_allocations = list_init(malloc_fptr);
    }
    heap_meta_t* meta =
        malloc_fptr(sizeof(heap_meta_t) + size + sizeof(unsigned int));
    if (!meta)
    {
        return NULL;
    }
    memset(meta, 0, sizeof(heap_meta_t));
    meta->size          = size;
    meta->line          = line;
    meta->alloc_num     = ++g_heap_info.num_allocs;
    meta->header_cookie = DEBUG_HEAP_HEADER_COOKIE;
    *(unsigned int*)((unsigned char*)meta + sizeof(heap_meta_t) + size) =
        DEBUG_HEAP_FOOTER_COOKIE;
    list_add(g_heap_info.outstanding_allocations, meta, malloc_fptr);
    return meta->payload;
}

void debug_heap_free(void* ptr,
                     void (*free_fptr)(void* ptr),
                     void (*check_fptr)(unsigned int line, char* msg))
{
    heap_meta_t* meta =
        (heap_meta_t*)((unsigned char*)ptr - sizeof(heap_meta_t));
    if (!(meta->header_cookie == DEBUG_HEAP_HEADER_COOKIE))
    {
        check_fptr(meta->line, "Header corrupted");
        return;
    }
    if (!(*(unsigned int*)((unsigned char*)meta + meta->size +
                           sizeof(heap_meta_t)) == DEBUG_HEAP_FOOTER_COOKIE))
    {
        check_fptr(meta->line, "Footer corrupted");
        return;
    }
    g_heap_info.num_frees++;
    list_remove(g_heap_info.outstanding_allocations, meta, free_fptr);
    if (g_heap_info.num_frees == g_heap_info.num_allocs)
    {
        if (g_heap_info.outstanding_allocations)
        {
            list_destroy(g_heap_info.outstanding_allocations, free_fptr);
            g_heap_info.outstanding_allocations = NULL;
        }
    }
    return free_fptr(meta);
}
