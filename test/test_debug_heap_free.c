#include <stddef.h>
#include <stdlib.h>
#include "unity.h"

// mock our stub
#include "mock_stdio_stub.h"

// code under test
#include "debug_heap.h"

void* allocated_ptr = NULL;

void check_func(unsigned int line, char* msg)
{
    printf("HeapCheck on line %d: %s\n", line, msg);
}

void setUp()
{
    allocated_ptr = debug_heap_malloc(10, malloc, __LINE__);
}

void tearDown()
{
}

/**
  Test that we can free memory from the debug heap allocator
  */
void testDebugHeapFree()
{
    stub_free_Expect((char*)allocated_ptr - sizeof(heap_meta_t));
    debug_heap_free(allocated_ptr, stub_free, check_func);
}
