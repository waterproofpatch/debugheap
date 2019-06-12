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

/**
  Test that we detect footer corruption in a block
  */
void testDebugHeapAllocCorruptFooter()
{
    heap_meta_t* meta = malloc(sizeof(heap_meta_t) + 10);
    stub_malloc_ExpectAndReturn(sizeof(heap_meta_t) + 10 + sizeof(unsigned int),
                                meta);
    stub_check_func_Expect(__LINE__ + 1, "Footer corrupted");
    char* p = debug_heap_malloc(10, stub_malloc, __LINE__);

    TEST_ASSERT_NOT_NULL(p);
    p[11] = 0xff;   // smash into footer

    debug_heap_free(p, stub_free, stub_check_func);
}

/**
  Test that we detect header corruption in a block
  */
void testDebugHeapAllocCorruptHeader()
{
    heap_meta_t* meta = malloc(sizeof(heap_meta_t) + 10);
    stub_malloc_ExpectAndReturn(sizeof(heap_meta_t) + 10 + sizeof(unsigned int),
                                meta);
    stub_check_func_Expect(__LINE__ + 1, "Header corrupted");
    char* p = debug_heap_malloc(10, stub_malloc, __LINE__);

    TEST_ASSERT_NOT_NULL(p);
    p[-1] = 0xff;   // smash into footer

    debug_heap_free(p, stub_free, stub_check_func);
}