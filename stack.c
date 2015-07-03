/*
    Name:       stack.c
    Purpose:    Integer stacks for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

/* create a new stack */
Stack *newStack( int size )
{
    Stack *stack;

    /* allocate stack */
    stack = (Stack *)eMalloc( sizeof( Stack ) +
                (sizeof(intptr_t) * (size)) );

    stack->tos = -1;
    stack->size = size;
    return stack; 
}

/* push an item on the stack */
void pushStack( Stack *stack, intptr_t value )
{
    if (stack->tos == stack->size) {
        ePrintf( Runtime, "pushStack: stack overflow");
    }
    stack->tos++;
    stack->data[stack->tos] = value;
}

/* incrStack: increment the value on the stack */
void incrStack( Stack *stack, intptr_t value )
{
    stack->data[stack->tos] += value;
}

/* decrStack: decrement the value on the stack */
void decrStack( Stack *stack, intptr_t value )
{
    stack->data[stack->tos] -= value;
}


/* swapStack: swap top two stack items */
void swapStack( Stack *stack  )
{
    intptr_t tmp;

    if (stack->tos < 1) {
        ePrintf( Runtime, "swapStack: stack underflow");
    }

    tmp = stack->data[stack->tos];
    stack->data[stack->tos] = stack->data[stack->tos-1];
    stack->data[stack->tos-1] = tmp;
}

/* duplicate top stack item */
void dupStack( Stack *stack  )
{
    if (stack->tos < 0) {
        ePrintf( Runtime, "dupStack: underflow" );
    } else if (stack->tos == stack->size) {
        ePrintf( Runtime, "dupStack: overflow" );
    }
    stack->tos++;
    stack->data[stack->tos] = stack->data[stack->tos-1];
}


/* return copy of top stack item */
intptr_t peekStack( Stack *stack  )
{
    if (stack->tos < 0) {
        ePrintf( Runtime, "peekStack: underflow" );
    }
    return stack->data[stack->tos];
}


/* pop an item off the stack */
intptr_t popStack( Stack *stack  )
{
    if (stack->tos < 0) {
        ePrintf( Runtime, "popStack: underflow" );
    }
    stack->tos--;
    return stack->data[stack->tos+1];
}


/* return nonzero if stack is not empty */
int isEmptyStack( Stack *stack  )
{
    return (stack->tos == -1);
}

/* inStack: return true if item is in the stack */
intptr_t inStack( Stack *stack, int val  )
{
    int     i;
    for ( i = stack->tos; i > -1; i-- ) {
        if (stack->data[i] == val) {
            return 1;
        }
    }
    return 0;
}


/* pop all elements off the stack */
void clearStack( Stack *stack  )
{
    stack->tos = -1;
}


/* destroy a stack */
void freeStack( Stack *stack )
{
    free( stack );
}
