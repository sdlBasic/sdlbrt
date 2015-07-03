/*
    Name:       array.h
    Purpose:    array structures for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

struct ArrayCell {
    char    *key;               /* key */
    Variant data;               /* data stored in cell */
};

struct Array {
    int     indexes;            /* count of indexes */
    int     elements;           /* total number of elements */
    int     lower[NINDEX];      /* lower range of index */
    int     upper[NINDEX];      /* upper range of index */
    int     offset[NINDEX];     /* offset per index */
    int     isDynamic;          /* if true, it's a dynamic array */
    union {
        Variant     *item;      /* variant static data array */
        ArrayCell   *cell;      /* dynamic data array */
    } data;
};


Array *createStaticArray( Symbol *s );
Array *createDynamicArray( Symbol *s );
Symbol *createArraySymbol( char *name, int args );
Array *getArray( Symbol *s );
int getStaticIndex( Array *array, Symbol *s );
char *buildKey( Array *array, Symbol *s );
int findKey( Array *array, Symbol *s, char *key );
void getDynamicValue( Array *array, Symbol *s );
int getDynamicKey( Array *array, int index );
void resizeDynamicArray( Array *array );
void insertDynamicCell( Array *array, int pos );
void setDynamicValue( Array *array, Symbol *s );
void getArrayElement( Symbol *s );
void setArrayElement( Symbol *s );
void pushArray( Symbol *s );
void eraseArrayElement( Symbol *s );
void eraseArray( Symbol *s );
void freeArray( Array *array );
int getArrayIndexes( void );
int getArrayBound( int index, int upper );
