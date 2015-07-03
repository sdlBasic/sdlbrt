/*
    Name:       stack.h
    Purpose:    Integer stacks for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

struct Stack {
    int     tos;        /* top of stack */
    int     size;       /* size of stack */
    int     data[1];    /* stack data */
};

Stack *newStack( int size );
void pushStack( Stack *stack, intptr_t value );
void incrStack( Stack *stack, intptr_t value );
void decrStack( Stack *stack, intptr_t value );
void swapStack( Stack *stack  );
void dupStack( Stack *stack  );
intptr_t peekStack( Stack *stack  );
intptr_t popStack( Stack *stack  );
int isEmptyStack( Stack *stack  );
intptr_t inStack( Stack *stack, int val  );
void clearStack( Stack *stack  );
void freeStack( Stack *stack );
