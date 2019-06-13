# Heap Debugger

Library for detecting heap corruption during _free_ operations and troubleshooting memory leaks. Works as a shim layer between malloc/free.

## Prerequisites

- gcovr
- ruby
- cmock

## Usage

Put the `src/debug_heap` and `src/linked_list` directories in a location where
your build system will find them.

This library is _not_ thread safe.

To debug heap usage in a file, include code like the following:

```c
#define DEBUG_HEAP
#ifdef DEBUG_HEAP
#define malloc(s) debug_heap_malloc(s, malloc, __LINE__)
#define free(p) debug_heap_free(p, free, check_func)
#endif
```

An additional API, `debug_heap_check_outstanding_allocs`, has been defined to aid in troubleshooting memory leaks. At any point in your program, call this function and supply a user-defined checker function to be called for all allocations that have not been free'd.

See the `src/main.c` driver for an example of how to use this library.

## Build and run the code

```bash
make && make run
```

## Run the tests

```bash
make test
```
