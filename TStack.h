#define SUCCESS 0 
#define INVALID_NULL_POINTER -1 
#define OUT_OF_MEMORY -2
#define OUT_OF_RANGE -3
#include "Ponto.h"

typedef struct TStack TStack;


TStack *create_stack();
int stack_free(TStack *st);
int stack_push(TStack *st, struct Ponto al);
int stack_pop(TStack *st);
int stack_size(TStack *st);
int stack_top(TStack *st, struct Ponto *al);
int stack_empty(TStack *st);