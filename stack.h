#define SUCCESS 0 
#define INVALID_NULL_POINTER -1 
#define OUT_OF_RANGE -3 
#define ELEM_NOT_FOUND -4
#define ERRO_SORTED -5

typedef struct Stack Stack;
#include "Ponto.h"

Stack *create_stack();
int stack_free(Stack *st);
int stack_push(Stack *st, struct Ponto al);
int stack_pop(Stack *st);
int stack_size(Stack *st);
int stack_find(Stack *st,struct Ponto *al);