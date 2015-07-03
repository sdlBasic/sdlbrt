/*
    Name:       node.c
    Purpose:    Parse tree data structure for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

Node *opNode( int op, Node *left, Node *right )
{
    Node    *node;

    node = (Node *) eMalloc( sizeof( Node ) );
    node->op = op;
    node->left = left;
    node->right = right;
    node->next = NULL;
    node->trace = -1;    
    return node;
}

Node *intNode( int op, int value, Node *left, Node *right )
{
    Node    *node;

    node = opNode( op, left, right );
    node->value.iValue = value;
    return node;
}

Node *floatNode( int op, Number value, Node *left, Node *right )
{
    Node    *node;

    node = opNode( op, left, right );
    node->value.fValue = value;
    return node;
}


Node *stringNode( int op, char *string, Node *left, Node *right )
{
    Node    *node;

    node = opNode( op, left, right );
    node->value.string = string;
    return node;
}


Node *symbolNode( int op, Symbol *symbol, Node *left, Node *right )
{
    Node    *node;

    node = opNode( op, left, right );
    node->value.symbol = symbol;
    return node;
}


void freeNode( Node *node )
{
    if (node != NULL) {
        freeNode( node->left );
        freeNode( node->right );
    }
    free( node );
}
