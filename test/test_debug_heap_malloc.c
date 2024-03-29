#include <stddef.h>
#include <stdlib.h>
#include "unity.h"

// mock our stub
#include "mock_stdio_stub.h"
#include "mock_list.h"

// code under test
#include "debug_heap.h"

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
    list_t       list;
    heap_meta_t* meta = malloc(sizeof(heap_meta_t) + 10);
    list_init_ExpectAndReturn(stub_malloc, &list);
    stub_malloc_ExpectAndReturn(sizeof(heap_meta_t) + 10 + sizeof(unsigned int),
                                meta);
    list_add_ExpectAndReturn(&list, meta, stub_malloc, 1);
    char* p = debug_heap_malloc(10, stub_malloc, __LINE__);

    TEST_ASSERT_NOT_NULL(p);

    heap_meta_t* p_meta = (heap_meta_t*)((char*)p - sizeof(heap_meta_t));

    TEST_ASSERT_EQUAL(p_meta->size, 10);
    TEST_ASSERT_EQUAL(p_meta->alloc_num, 1);

    free(meta);
}

/**
  Test that we get a null ptr back if we fail to allocate requisite memory
  */
void testDebugHeapAllocFail()
{
    stub_malloc_ExpectAndReturn(sizeof(heap_meta_t) + 10 + sizeof(unsigned int),
                                NULL);
    char* p = debug_heap_malloc(10, stub_malloc, __LINE__);

    TEST_ASSERT_NULL(p);
}