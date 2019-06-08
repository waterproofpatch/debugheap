#include <stddef.h>
#include <stdlib.h>
#include "unity.h"

// mock our stub
#include "mock_stdio_stub.h"

// code under test
#include "debug_heap.h"

void setUp()
{
}

void tearDown()
{
}

void testDebugHeapAlloc()
{
    char        ptr[10];
    heap_info_t heap;
    stub_malloc_ExpectAndReturn(sizeof(heap_info_t), &heap);
    stub_malloc_ExpectAndReturn(sizeof(heap_meta_t) + 10 + sizeof(unsigned int),
                                ptr);
    char* p = debug_heap_malloc(10);
    TEST_ASSERT_NOT_NULL(p);
}

