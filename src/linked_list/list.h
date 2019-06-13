#ifndef _LIST_H
#define _LIST_H

#include <stdio.h>

typedef struct _node_t
{
    struct _node_t* next;
    void*           data;
} node_t;

typedef struct _list_t
{
    node_t* head;
    void*   data;
} list_t;

list_t*      list_init(void* (*malloc_fptr)(size_t size));
unsigned int list_foreach(list_t* list,
                          void*   context,
                          char (*proc_fptr)(void* context, void* data));
char list_add(list_t* list, void* data, void* (*malloc_fptr)(size_t size));
char list_remove(list_t* list, void* data, void (*free_fptr)(void* ptr));
void list_destroy(list_t* list, void (*free_fptr)(void* ptr));

#endif