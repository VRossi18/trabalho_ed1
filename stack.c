#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef struct list_node list_node;
struct list_node
{
    struct Ponto data;
    list_node *next;
};

struct Stack
{
    list_node *begin;
    int size;
    int inf;
};

Stack *create_stack()
{
    Stack *fl;
    fl = malloc(sizeof(Stack));
    if (fl == NULL)
    {
        return fl;
    }
    fl->begin = NULL;
    fl->size = 0;

    return fl;
}

int stack_free(Stack *fl)
{
    if (fl == NULL)
    {
        return INVALID_NULL_POINTER;
    }
    else
    {
        list_node *aux = fl->begin;
        while (fl->size != 0)
        {
            fl->begin = aux->next;
            free(aux);
            aux = fl->begin;
            fl->size--;
        }
        free(fl);
        return SUCCESS;
    }
}

int stack_push(Stack *fl, struct Ponto al)
{
    if (fl == NULL)
    {
        return INVALID_NULL_POINTER;
    }
    else
    {
        list_node *node;
        node = malloc(sizeof(list_node));
        if (node == NULL)
        {
            return INVALID_NULL_POINTER;
        }
        node->data = al;
        node->next = fl->begin;
        fl->begin = node;
        fl->size++;
        return SUCCESS;
    }
}

int stack_pop(Stack *fl)
{
    if (fl == NULL)
    {
        return INVALID_NULL_POINTER;
    }
    if (fl->size == 0)
    {
        return OUT_OF_RANGE;
    }
    list_node *aux = fl->begin;
    fl->begin = aux->next;

    free(aux);
    fl->size--;

    return SUCCESS;
}

int stack_size(Stack *fl)
{
    if (fl == NULL)
    {
        return INVALID_NULL_POINTER;
    }
    else
    {
        return fl->size;
    }
}

int stack_find(Stack *fl, struct Ponto *al)
{
    if (fl == NULL)
    {
        return INVALID_NULL_POINTER;
    }
    if (fl->size == 0)
    {
        return OUT_OF_RANGE;
    }
    else
    {
        list_node *aux = fl->begin;
        *al = aux->data;
    }
    return SUCCESS;
}