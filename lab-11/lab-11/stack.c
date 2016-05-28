#include "stack.h"
#include <stdlib.h>

struct _stack
{
    int value;
    struct _stack* next;
};

Stack* push(Stack* stack, int value)
{
    if (!stack)
    {
        stack = malloc(sizeof(Stack));
        stack->next = NULL;
        stack->value = value;
        return stack;
    }
    else
    {
        Stack* newEl = malloc(sizeof(Stack));
        newEl->next = stack;
        newEl->value = value;
        return newEl;
    }
}

int pop(Stack** stack)
{
    Stack* tmpEl = *stack;
    int value = tmpEl->value;
    *stack = (*stack)->next;
    free(tmpEl);
    return value;
}