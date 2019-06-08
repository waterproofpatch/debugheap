#include <stddef.h>
#include <stdlib.h>
#include "unity.h"

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
    char* p = debug_heap_malloc(10);
    TEST_ASSERT_NOT_NULL(p);
}

