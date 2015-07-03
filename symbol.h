/*
    Name:       symbol.h
    Purpose:    Data structures for wxBasic symbols
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

/* types of symbols */
enum {
    SYM_KEYWORD = 1,        /* keyword                          */
    SYM_VARIABLE,           /* variable                         */
    SYM_ARRAY,              /* array                            */
    SYM_CONSTANT,           /* constant, variant                */
    SYM_BUILTIN,            /* builtin function                 */
    SYM_FUNCTION,           /* user defined function            */
    SYM_SUB,                /* user defined subroutine          */
    SYM_FORWARD_SUB,        /* forward reference to sub         */
    SYM_FORWARD_FUNCTION,   /* forward reference to function    */
    SYM_CLASS               /* wrapped c++ class                */
};

char *symbolName[] = {
    "undefined",
    "keyword",
    "variable",
    "array",
    "constant",
    "function",
    "function",
    "sub",
    "sub (forward referenced)",
    "function (forward referenced)",
    "class"
};

struct Symbol {
    char    *name;                  /* name */
    int     symboltype;             /* type */
    int     klass;                  /* used to differentiate classes */
    Symbol  *scope;                 /* if NULL, module level */
    int     common;                 /* if true, global in scope */
    int     stackPos;               /* position of variable on stack */
    int     args;                   /* required args */
    int     optargs;                /* optional args */
    int     locals;                 /* total count of variables */
    int     indexes;                /* count of indexes */
    Symbol  *prior;                 /* prior symbol */
    Symbol  *child;                 /* link to first child */
    Symbol  *sibling;               /* link to next sibling */
    Node    *code;                  /* bytecodes */
    int     forward;                /* forward reference, code undefined */
    void    (*builtin)(void);       /* builtin function */
};

Symbol *lastSymbol = NULL;


Symbol *maskIfHidden( Symbol *s );
Symbol *findSymbol( char *name, Symbol *scope );
void addChildSymbol( Symbol *s, Symbol *child );
Symbol *addSymbol( char *name, Symbol *scope, int symboltype );
Symbol *findChildSymbol( Symbol *parent, int index );
void checkArgCount( Symbol *s, int args );
