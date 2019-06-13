#include <stddef.h>
#include <stdlib.h>
#include "unity.h"

// mock our stub
#include "mock_stdio_stub.h"
#include "mock_list.h"

// code under test
#include "debug_heap.h"

void*   allocated_ptr = NULL;
list_t* list          = NULL;

void check_func(unsigned int line, char* msg)
{
    printf("HeapCheck on line %d: %s\n", line, msg);
}

void setUp()
{
    list       = malloc(sizeof(list_t));
    list->head = NULL;

    list_init_ExpectAndReturn(malloc, list);
    list_add_IgnoreAndReturn(1);
    allocated_ptr = debug_heap_malloc(10, malloc, __LINE__);
}

void tearDown()
{
    free(list);
}

/**
  Test that we can free memory from the debug heap allocator
  */
void testDebugHeapFree()
{
    list_remove_ExpectAndReturn(
        list, (char*)allocated_ptr - sizeof(heap_meta_t), stub_free, 1);
    list_destroy_Expect(list, stub_free);
    stub_free_Expect((char*)allocated_ptr - sizeof(heap_meta_t));
    debug_heap_free(allocated_ptr, stub_free, check_func);
}
