#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "debug_heap.h"

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
    unsigned int   size;
    unsigned int   alloc_num;
    unsigned int   header_cookie;
    unsigned char* payload[0];
} heap_meta_t;

heap_info_t* g_heap_info = NULL;

static void debug_heap_init()
{
    g_heap_info = malloc(sizeof(heap_info_t));
    if (g_heap_info)
    {
        memset(g_heap_info, 0, sizeof(heap_info_t));
    }
}

void* debug_heap_malloc(size_t size)
{
    if (!g_heap_info)
    {
        debug_heap_init();
    }
    heap_meta_t* meta =
        malloc(sizeof(heap_meta_t) + size + sizeof(unsigned int));
    if (!meta)
    {
        return NULL;
    }
    memset(meta, 0, sizeof(heap_meta_t));
    meta->size          = size;
    meta->alloc_num     = ++g_heap_info->num_allocs;
    meta->header_cookie = DEBUG_HEAP_HEADER_COOKIE;
    *(unsigned int*)((unsigned char*)meta + sizeof(heap_meta_t) + size) =
        DEBUG_HEAP_FOOTER_COOKIE;
    printf("total allocs: %u alloc num %u, size %u\n", g_heap_info->num_allocs,
           meta->alloc_num, meta->size);
    return meta->payload;
}

void debug_heap_free(void* ptr)
{
    heap_meta_t* meta =
        (heap_meta_t*)((unsigned char*)ptr - sizeof(heap_meta_t));
    g_heap_info->num_frees++;
    printf("heap header cookie is %p=0x%08x\n", &meta->header_cookie,
           meta->header_cookie);
    printf("payload begins at %p\n", meta->payload);
    printf("%p=0x%08x\n", meta->payload - 1,
           *(unsigned char*)meta->payload - 1);
    assert(meta->header_cookie == DEBUG_HEAP_HEADER_COOKIE);
    assert(*(unsigned int*)((unsigned char*)meta + meta->size +
                            sizeof(heap_meta_t)) == DEBUG_HEAP_FOOTER_COOKIE);
    printf("total frees: %u freeing %u, size %u\n", g_heap_info->num_frees,
           meta->alloc_num, meta->size);

    return free(meta);
}
