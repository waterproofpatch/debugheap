#include <stddef.h>
#include <stdlib.h>
#include "unity.h"

// mock our stub
#include "mock_stdio_stub.h"
#include "mock_list.h"

// code under test
#include "debug_heap.h"

extern heap_info_t g_heap_info;

char was_called = 0;
void check_func(unsigned int line, unsigned int size)
{
    TEST_ASSERT_EQUAL(line, 1);
    TEST_ASSERT_EQUAL(size, 10);
    was_called = 1;
}

unsigned int list_foreach_stub(list_t* list,
                               void*   context,
                               char (*check_fptr)(void* context, void* data),
                               unsigned int num_calls)
{
    TEST_ASSERT_EQUAL(list, g_heap_info.outstanding_allocations);
    TEST_ASSERT_EQUAL(check_func, context);
    return 2;
}

void setUp()
{
}

void tearDown()
{
    was_called = 0;
}

/**
  Test that we don't call foreach when there are no outstanding allocs
  */
void testDebugHeapCheckNoOutstandingAllocs()
{
    TEST_ASSERT_EQUAL(debug_heap_check_outstanding_allocs(check_func), 0);
    TEST_ASSERT_FALSE(was_called);
}

/**
  Test that we call foreach when there are outstanding allocs
  */
void testDebugHeapCheckOutstandingAllocs()
{
    g_heap_info.outstanding_allocations = malloc(sizeof(list_t));
    list_foreach_StubWithCallback(
        (CMOCK_list_foreach_CALLBACK)list_foreach_stub);
    TEST_ASSERT_EQUAL(debug_heap_check_outstanding_allocs(check_func), 2);
    TEST_ASSERT_FALSE(was_called);
    free(g_heap_info.outstanding_allocations);
}