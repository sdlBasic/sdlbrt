/*
    Name:       var.h
    Purpose:    wxBasic simple variables
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/


Symbol *returnVar( char *name, int symType, int create );
Symbol *createConst( char *name );
Symbol *createParm( char *name, int symType );
int varStackPos( Symbol *s );
void setStack( int index );
void setVar( Symbol *s );
void setReturn();
Number fetchNumber( int index );
char *fetchString( int index );
void getVar( Symbol *s );
