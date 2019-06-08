#include <stddef.h>
#include <stdlib.h>
#include "unity.h"

// mock our stub
#include "mock_stdio_stub.h"

// code under test
#include "debug_heap.h"

// fake meta object we return from malloc
typedef struct _test_heap_meta_t
{
    heap_meta_t meta;
    char        payload[10];
} test_heap_meta_t;

test_heap_meta_t meta;
heap_info_t      heap;

void setUp()
{
}

void tearDown()
{
}

/**
  Test that we can allocate memory from the debug heap allocator
  */
void testDebugHeapAlloc()
{
    stub_malloc_ExpectAndReturn(sizeof(heap_info_t), &heap);
    stub_malloc_ExpectAndReturn(sizeof(heap_meta_t) + 10 + sizeof(unsigned int),
                                &meta);
    char* p = debug_heap_malloc(10);
    TEST_ASSERT_NOT_NULL(p);
    heap_meta_t* p_meta = (heap_meta_t*)((char*)p - sizeof(heap_meta_t));
    TEST_ASSERT_EQUAL(p_meta->size, 10);
    TEST_ASSERT_EQUAL(p_meta->alloc_num, 1);
}

