/*
    node.h
    parse tree data structure for wxScript
    (c) 2001 David Cuny
    dcuny@lanset.com
*/

struct Node {
    int     op;             /* operation */
    union {
        int     iValue;     /* integer data */
        Number  fValue;     /* float data */
        char    *string;    /* string */
        Symbol  *symbol;    /* symbol */
    } value;
    int     trace;
    Node    *left;
    Node    *right;
    Node    *next;
};

Node *opNode( int op, Node *left, Node *right );
Node *intNode( int op, int value, Node *left, Node *right );
Node *floatNode( int op, Number value, Node *left, Node *right );
Node *stringNode( int op, char *string, Node *left, Node *right );
Node *symbolNode( int op, Symbol *symbol, Node *left, Node *right );
void freeNode( Node *node );
