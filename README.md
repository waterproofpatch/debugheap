# Heap Debugger
Library for detecting heap corruption during *free* operations. Works as a shim layer between 
malloc/free.

## Usage
Put the debug_heap.h/c files in the includes path for your project. Include them conditionally 
to stub out malloc/free.


