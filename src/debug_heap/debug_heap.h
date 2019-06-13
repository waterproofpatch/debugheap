#ifndef _DEBUG_HEAP_H
#define _DEBUG_HEAP_H

#include <stdlib.h>

#include "list.h"

// cookies for heap metadata
#define DEBUG_HEAP_HEADER_COOKIE 0x11223344
#define DEBUG_HEAP_FOOTER_COOKIE 0x44332211

/**
 * @brief heap info capturing summary information
 * about the state of the heap.
 *
 */
typedef struct _heap_info_t
{
    unsigned int num_allocs;           // number of allocations made
    unsigned int num_frees;            // number of free's
    unsigned int cur_alloc;            // the current allocation number
    list_t* outstanding_allocations;   // list of allocations that have not been
                                       // free'd
} heap_info_t;

/**
 * @brief heap chunk metadata describing the chunk.
 *
 */
typedef struct _heap_meta_t
{
    unsigned int  size;            // size of the usable part of this allocation
    unsigned int  alloc_num;       // the number of the allocation
    unsigned int  line;            // line the allocation was made
    unsigned int  header_cookie;   // the header cookie value
    unsigned char payload[0];      // pointer to the usable payload
} heap_meta_t;

/**
 * @brief call a user supplied function for each allocation that
 * has not been free'd.
 *
 * @param check_alloc_ptr: callback function taking the line number and
 * allocations size for the unfree'd allocation.
 *
 * @return: number of outstanding allocations.
 */
unsigned int debug_heap_check_outstanding_allocs(
    void (*check_alloc_fptr)(unsigned int line, unsigned int size));

/**
 * @brief wrapper for allocator function.
 *
 * @param size: the size of the requested allocation.
 * @param malloc_fptr: function to allocate memory.
 * @param line: the line the allocation is being made on.
 *
 * @return: ptr to the allocation, or NULL if no allocation is possible.
 */
void* debug_heap_malloc(size_t size,
                        void* (*malloc_fptr)(size_t size),
                        unsigned int line);

/**
 * @brief wrapper for free function.
 *
 * @param ptr: the ptr to free.
 * @param free_fptr: the function to free memory.
 * @param check_fptr: the callback to invoke in case a heap header or
 * footer is corrupted.
 *
 */
void debug_heap_free(void* ptr,
                     void (*free_fptr)(void* ptr),
                     void (*check_fptr)(unsigned int line, char* msg));

#endif
