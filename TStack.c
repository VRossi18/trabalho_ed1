#include <stdlib.h>
#include "TStack.h"
#include <stdio.h>

typedef struct list_node list_node;
struct list_node
{
    struct Ponto data;
    list_node *next;
};

struct TStack{
    list_node *begin;
    int size;
    int inf;
};

TStack *create_stack()
{
    TStack *st;
    st = malloc(sizeof(TStack));
    if (st == NULL)
    {
        return st;
    }
    st->begin = NULL;
    st->size = 0;

    return st;
}

int stack_free(TStack *st)
{
    if (st == NULL)
    {
        return INVALID_NULL_POINTER;
    }
    else
    {
        list_node *aux = st->begin;
        while (st->size != 0)
        {
            st->begin = aux->next;
            free(aux);
            aux = st->begin;
            st->size--;
        }
        free(st);
        return SUCCESS;
    }
}

int stack_push(TStack *st, struct Ponto al)
{
    if (st == NULL)
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
        node->next = st->begin;
        st->begin = node;
        st->size++;
        return SUCCESS;
    }
}

int stack_pop(TStack *st)
{
    if (st == NULL || st->size == 0)
    {
        return INVALID_NULL_POINTER;
    }
    list_node *aux = st->begin;
    st->begin = aux->next;

    free(aux);
    st->size--;

    return SUCCESS;
}

int stack_size(TStack *st)
{
    if (st == NULL)
    {
        return INVALID_NULL_POINTER;
    }
    else
    {
        return st->size;
    }
}

int stack_top(TStack *st, struct Ponto *al)
{
    if (st == NULL)
    {
        return INVALID_NULL_POINTER;
    }
    if (st->size == 0)
    {
        return OUT_OF_RANGE;
    }
    else
    {
        list_node *aux = st->begin;
        *al = aux->data;
    }
    return SUCCESS;
}