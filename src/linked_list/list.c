#include <stddef.h>

#include "list.h"

unsigned int list_foreach(list_t* list,
                          void*   context,
                          char (*proc_fptr)(void* context, void* data))
{
    unsigned int num_processed = 0;
    node_t*      cur           = list->head;
    while (cur)
    {
        num_processed++;
        if (!proc_fptr(context, cur->data))
        {
            return num_processed;
        }
        cur = cur->next;
    }
    return num_processed;
}

list_t* list_init(void* (*malloc_fptr)(size_t size))
{
    list_t* new_list = malloc_fptr(sizeof(list_t));
    if (!new_list)
    {
        return NULL;
    }
    new_list->head = NULL;
    return new_list;
}

char list_add(list_t* list, void* data, void* (*malloc_fptr)(size_t size))
{
    if (!list->head)
    {
        list->head = malloc_fptr(sizeof(node_t));
        if (!list->head)
        {
            return 0;
        }
        list->head->next = NULL;
        list->head->data = data;
        return 1;
    }
    node_t* cur = list->head;
    while (cur->next)
    {
        cur = cur->next;
    }
    cur->next = malloc_fptr(sizeof(node_t));
    if (!cur->next)
    {
        return 0;
    }
    cur       = cur->next;
    cur->next = NULL;
    cur->data = data;
    return 1;
}

char list_remove(list_t* list, void* data, void (*free_fptr)(void* ptr))
{
    node_t* cur  = list->head;
    node_t* prev = NULL;
    while (cur)
    {
        if (cur->data == data)
        {
            if (cur == list->head)
            {
                list->head = list->head->next;
            }
            if (prev)
            {
                prev->next = cur->next;
            }
            free_fptr(cur);
            return 1;
        }
        prev = cur;
        cur  = cur->next;
    }
    return 0;
}

void list_destroy(list_t* list, void (*free_fptr)(void* ptr))
{
    node_t* cur = list->head;
    while (cur)
    {
        node_t* tmp = cur;
        cur         = cur->next;
        free_fptr(tmp);
    }
    free_fptr(list);
}
