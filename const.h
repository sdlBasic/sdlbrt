/*
    Name:       const.h
    Purpose:    Builtin constants for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

void addConst( char *name, int value );
void addStrConst( char *name, char *value );
void addConstPtr( char *name, int classIndex, int pointer );
void initConsts( void );
