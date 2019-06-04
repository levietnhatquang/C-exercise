#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h>
#include "stack.h"
#include "linkedList.h"


#ifdef __STACK_ARRAY_BASE__
  
struct Stack* createStack(unsigned capacity) 
{ 
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack)); 
    stack->capacity = capacity; 
    stack->top = -1; 
    stack->array = (int*) malloc(stack->capacity * sizeof(int)); 
    return stack; 
} 

int isFull_s(struct Stack* stack) 
{   return stack->top == stack->capacity - 1; } 
 
int isEmpty_s(struct Stack* stack)
{   return stack->top == -1;  } 
 
void push_s(struct Stack* stack, int item) 
{ 
    if (isFull_s(stack)) 
        return; 
    stack->array[++stack->top] = item; 
    printf("%d pushed to stack\n", item); 
} 
  
int pop_s(struct Stack* stack) 
{ 
    if (isEmpty_s(stack)) 
        return INT_MIN; 
    return stack->array[stack->top--]; 
}

#endif

#ifdef __STACK_LINKED_LIST_BASE__

struct Stack* createStack(unsigned capacity) 
{ 
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->size = 0;
    stack->capacity = capacity; 
    return stack; 
} 

int isFull_s(struct Stack* stack) 
{   return stack->size == stack->capacity; } 
 
int isEmpty_s(struct Stack* stack)
{   return stack->size == 0;  } 
 
void push_s(struct Stack* stack, int item) 
{ 
    if (isFull_s(stack)) 
        return; 
    Push(&(stack->head), item);
    stack->size++;
    printf("%d pushed to stack\n", item); 
} 
  
int pop_s(struct Stack* stack) 
{ 
    if (isEmpty_s(stack)) 
        return INT_MIN;
    int item = stack->head->data;
    Deletenode(&(stack->head), item);
    stack->size--;
    return item; 
}

#endif