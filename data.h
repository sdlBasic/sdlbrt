/*
    Name:       data.h
    Purpose:    builtin types in wxBasic
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

union Value {
    Number  number;         /* number */
    char    *string;        /* pointer to string */
    Array   *array;         /* address of array */
    Variant *ref;           /* pointer to variant */
};

struct Variant {
    int  datatype;          /* number, string or array */
    Value value;            /* actual data value */
};

/* data types */
enum {
    DATA_UNDEFINED = 0, /* undefined, error */
    DATA_REF,           /* pointer to variant */
    DATA_NUMBER,        /* number */
    DATA_STRING,        /* pointer to string */
    DATA_ARRAY,         /* pointer to array */
    DATA_OBJECT         /* index to wrapped object */
};

char *datumName[] = {
    "Undefined",
    "Reference",
    "Number",
    "String",
    "Array",
    "Object"
};

/* the stack */
#define NSTACK (int) 4096       /* maximum stack size */
Variant stack[NSTACK];          /* stack, also holds locals */
int     tos = 0;                /* top of stack */
int     globals = 0;            /* count of global variables */
int     localstart = 0;         /* position of first local in stack */
int     stackMax = NSTACK-2;    /* maximum stack height */

void formatNumber( char *buffer, Number n );
int addGlobalToStack(void);
void pushNumber( Number value );
Variant *getStackPointer( int index );
void dropTos(void);
Number popNumber(void);
void pushStringCopy( char *string );
void pushString( char *string );
char *popString(void);
void copyStackItem( int index );
int getStackType( int index );
void printTos(void);
void printStack(void);
