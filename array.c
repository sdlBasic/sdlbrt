/*
    Name:       array.c
    Purpose:    array structures for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/


/* createStaticArray: create an array; indexes are on stack */
Array *createStaticArray( Symbol *s )
{

    int     indexes, i, arraySize, stackPos;
    int     indexSize[NINDEX], lower[NINDEX], upper[NINDEX];
    Array   *array;

    /* stack holds:
            index count (on top)
            lower range of index 1
            upper range of index 1
            lower range of index 2
            upper range of index 2
            ...
            lower range of index n
            upper range of index n
    */


    /* paranoia */
    eMemTest( "createStaticArray: symbol", s );

    /* get the index */
    indexes = (int)popNumber();
    if (indexes > NINDEX) {
        ePrintf( Runtime, "array %s has %d dimensions, maximum is %d",
                    s->name, indexes, NINDEX );
    }

    /* get the ranges */
    arraySize = 1;
    for (i=0; i < indexes; i++) {
        lower[i] = (int)popNumber();
        upper[i] = (int)popNumber();

        if (lower[i] > upper[i]) {
            ePrintf( Runtime, "index %d of array %s: lower index (%d) greater than upper(%d) index",
                i+1, lower[i], upper[i] );
        }

        indexSize[i] = (upper[i]-lower[i])+1;
        arraySize *= indexSize[i];
    }

    /* allocate space for structure */
    array = (Array *)eMalloc(sizeof(Array));
    array->isDynamic = 0;
    array->data.item = (Variant *)eMalloc(arraySize * sizeof(Variant)) ;

    /* initialize array */
    for (i=0; i < arraySize; i++){
        array->data.item[i].datatype = DATA_NUMBER;
        array->data.item[i].value.number = 0;
    }

    /* store values in structure */
    array->indexes = indexes;
    array->elements = arraySize;
    for (i=0; i<indexes; i++) {
        array->lower[i] = lower[i];
        array->upper[i] = upper[i];
        arraySize = arraySize/indexSize[i];
        array->offset[i] = arraySize;
    }

    /* store pointer in variable */
    stackPos = varStackPos( s );
    stack[stackPos].datatype = DATA_ARRAY;
    stack[stackPos].value.array = array;

    return array;
}

/* createDynamicArray: create a dynamic array */
Array *createDynamicArray( Symbol *s )
{

    int     i, arraySize, stackPos;
    Array   *array;

    /* paranoia */
    eMemTest( "createDynamicArray: symbol", s );

    /* allocate space for structure */
    array = (Array *)eMalloc(sizeof(Array));
    array->isDynamic = 1;

    /* get the ranges */
    arraySize = 32;
    array->lower[0]        = 0;         /* count of used cells */
    array->upper[0]        = 32;        /* count of free cells */

    array->data.cell = (ArrayCell *)eMalloc(arraySize * sizeof(ArrayCell)) ;

    /* initialize array */
    for (i=0; i < arraySize; i++){
        array->data.cell[i].key = NULL;
        array->data.cell[i].data.datatype = DATA_UNDEFINED;
    }

    /* store pointer in variable */
    stackPos = varStackPos( s );
    stack[stackPos].datatype = DATA_ARRAY;
    stack[stackPos].value.array = array;

    return array;
}



/* createArraySymbol: create an array symbol */
Symbol *createArraySymbol( char *name, int args )
{
    Symbol  *s = NULL;

    /* already exists in scope? */
    s = findSymbol( name, currentScope );
    if (s != NULL) {
        if (s->symboltype != SYM_ARRAY) {
            ePrintf( Syntax, "%s is already defined as %s",
                s->name, datumName[s->symboltype] );
        } else {
            return s;
        }
    }

    s = addSymbol( name, currentScope, SYM_ARRAY );

    /* how many args? */
    if (args == 0) {
        /* dynamic */
        s->args = 1;
        s->optargs = NINDEX;
    } else {
        s->args = args;
    }

    if (currentScope==NULL) {
        /* create as global */
        s->stackPos = addGlobalToStack();
        stack[s->stackPos].datatype = DATA_ARRAY;
        stack[s->stackPos].value.array = NULL;

    } else {
        /* create as local */
        currentScope->locals++;
        s->stackPos = currentScope->locals;
    }

    return s;
}

/* getArray: return pointer to array */
Array *getArray( Symbol *s )
{
    int stackPos;

    /* position of pointer on stack */
    stackPos = varStackPos( s );

    /* verify the type */
    if (stack[stackPos].datatype != DATA_ARRAY) {
        ePrintf( Runtime, "getArray: %s is %s, not an Array",
            s->name, datumName[stack[stackPos].datatype] );
    }

    return stack[stackPos].value.array;
}


/* getStaticIndex: get the address of the data element */
int getStaticIndex( Array *array, Symbol *s )
{
    int     offset;
    int     indexes;
    int     i;
    int     index;
    int     base;

    /* paranoia */
    eMemTest( "getStaticIndex: symbol", s );

    /* paranoia */
    eMemTest( "getStaticIndex: array", array );

    indexes = (int)popNumber();
    if (indexes != array->indexes) {
        ePrintf( Runtime, "getStaticIndex: array %s expects %d indexes, not %d",
            s->name, array->indexes, indexes );
    }

    offset = 0;
    for ( i=0; i<indexes; i++ ) {
        index = (int)popNumber();
        if (index > array->upper[i]) {
            ePrintf( Runtime, "getStaticIndex: index %d of array %s above upper bounds (%d>%d)",
                i+1, s->name, index, array->upper[i] );

        } else if (index < array->lower[i]) {
            ePrintf( Runtime, "getStaticIndex: index %d of array %s under lower bounds (%d<%d)",
                i+1, s->name, index, array->lower[i] );
        }

        base = index-(array->lower[i]);
        offset += base * array->offset[i];
    }
    return offset;
}

/* buildKey: build key from stack data */
char *buildKey( Array *array, Symbol *s )
{
    int     args, i, keylen;
    char    *index, *buffer;

/* FIX: should eventually just realloc when size is exceeded */

    /* create a buffer */
    buffer = (char *)eMalloc( 256 );
    buffer[0] = '\0';

    /* check arg count */
    args = (int)popNumber();

    /* there must be at least one index */
    if (args == 0) {
        ePrintf( Runtime, "Array %s[]x expects at least 1 index, not 0" );
    }

    /* build the key backwards, for speed */
    keylen = 0;
    for ( i = 1; i <= args; i++ ) {

        /* get index */
        index = popString();

        /* make sure it fits in the buffer */
        keylen += strlen( index );
        if (keylen >= 256) {
            ePrintf( Runtime, "Array key exceeds 256 characters" );
        }

        /* append to key */
        strcat( buffer, index );

	/*
	ivanixcu: debug
	need free allocated memory of index!
	printf("ivanixdebug: freeing (index) (%d)\n", *index );
	*/
	if (*index != '\0' ){
	    eFree( index );
	}

        if (i < args) {
            /* add delimiter */
            keylen += 1;
            if (keylen >= 256) {
                ePrintf( Runtime, "Array key exceeds 256 characters" );
            }
            /* replace with ASCII 34 eventually */
            strcat( buffer, "," );
        }
    }

    /* resize the buffer */
    return (char *)eRealloc( buffer, keylen+1 );
}


/* findKey: return the index of cell with key, or -1 */
int findKey( Array *array, Symbol *s, char *key )
{
    int         hi, lo, mid, c;
    ArrayCell   *cell;

    /* binary search */
    lo = 0;
    hi = array->lower[0]-1;
    while (lo <= hi) {
        mid = floor( (lo + hi) / 2 );
        cell = array->data.cell+mid;

        c = strcmp( key, cell->key );
        if (c < 0) {
            hi = mid - 1;

        } else if (c > 0) {
            lo = mid + 1;

        } else {
            return mid;

        }
    }
    return -1;
}


/* getDynamicValue: push value of cell onto stack */
void getDynamicValue( Array *array, Symbol *s )
{
    int         index;
    char        *key;
    ArrayCell   *cell;

    /* create the key */
    key = buildKey( array, s );

    /* look for key */
    index = findKey( array, s, key );
    eFree( key );

    if (index == -1) {
        /* no item */
        pushStringCopy( "" );

    } else {
        /* address of the cell */
        cell = array->data.cell + index;

        tos++;
        stack[tos].datatype = cell->data.datatype;

        /* copy data to stack */
        switch (cell->data.datatype) {
        case DATA_NUMBER:
            stack[tos].value.number = cell->data.value.number;
            break;

        case DATA_STRING:
            stack[tos].value.string = eCopyString( cell->data.value.string );
            break;

        default:
            ePrintf( Runtime, "getDynamicElement: Array %s[%s] is corrupt",
                s->name, cell->key );
            break;

        }
    }
}

/* getDynamicKey: push key of cell onto stack */
int getDynamicKey( Array *array, int index )
{
    ArrayCell   *cell;

    if (index < 0 || index >= array->lower[0]) {
        /* failure */
        return 0;

    } else {
        /* address of the cell */
        cell = array->data.cell + index;

        /* copy string to stack */
        tos++;
        stack[tos].datatype = DATA_STRING;
        stack[tos].value.string = eCopyString( cell->key );

        /* success */
        return 1;
    }
}


/* resizeDynamicArray: resize array, if needed */
void resizeDynamicArray( Array *array )
{
    int         i, oldSize, newSize;

    oldSize = array->upper[0];

    /* out of room? */
    if (array->lower[0] >= oldSize-1) {

        /* double space */
        newSize = oldSize * 2;

        array->data.cell = (ArrayCell *)eRealloc(
            (void *)(array->data.cell),
            newSize * sizeof(ArrayCell) );

        /* initialize new area */
        for ( i = oldSize; i < newSize; i++ ) {
            array->data.cell[i].key = NULL;
            array->data.cell[i].data.datatype = DATA_UNDEFINED;
        }

        /* set size */
        array->upper[0] = newSize;

    }
}

/* insertDynamicCell: insert a new cell at location */
void insertDynamicCell( Array *array, int index )
{
    int         usedCells, bytes;
    ArrayCell   *cell;

    /* if needed */
    resizeDynamicArray( array );

    usedCells = array->lower[0];
    bytes = sizeof( ArrayCell ) * ((usedCells+1) - index);

    /* cell to start move from */
    cell = array->data.cell + index;

    /* move memory, overlapping */
    memmove( (void *)(cell+1), (void *)cell, bytes );

    /* kill prior value */
    cell->key = NULL;
    cell->data.datatype = DATA_UNDEFINED;

    /* increment cell count */
    array->lower[0] += 1;

}


/* setDynamicValue: set cell at index to value on stack */
void setDynamicValue( Array *array, Symbol *s )
{
    int         index, hi, lo, isNew, c;
    char        *key;
    Variant     *stackData;
    ArrayCell   *cell;

    /* make sure there is a value to set */
    if (tos == 0) {
        ePrintf( Runtime, "setDynamicValue: stack underflow" );
    }

    /* create the key */
    key = buildKey( array, s );

    /* assume it will be a new key */
    isNew = 1;

    /* binary search */
    lo = 0;
    hi = array->lower[0]-1;
    index = 0;
    while (lo <= hi) {
        index = floor((lo + hi) / 2);
        cell = array->data.cell+index;
        c = strcmp( key, cell->key );
        if (c < 0) {
            hi = index - 1;
        } else if (c > 0) {
            lo = index + 1;
        } else {
            /* found prior key */
            isNew = 0;
            break;
        }
    }

    /* no prior key? */
    if (isNew) {
        /* create empty cell */
        index = lo;
        insertDynamicCell( array, index );

    }

    /* address of cell */
    cell = array->data.cell + index;

    /* need to set key? */
    if (isNew) {
        /* use key (already unique copy) */
        cell->key = key;
    } else {
        /* don't need key */
        eFree( key );

        /* clean up old value */
        if (cell->data.datatype == DATA_STRING) {
            eFree( cell->data.value.string );
        }

    }

    /* resolve datatype */
    stackData = getStackPointer( tos );
    cell->data.datatype = stackData->datatype;

    if (stackData->datatype == DATA_STRING) {
        /* ref? */
        if (stack[tos].datatype == DATA_REF) {
            /* need to make a unique copy */
            cell->data.value.string = eCopyString( stackData->value.string );
        } else {
            /* use directly */
            cell->data.value.string = stackData->value.string;
        }

    } else if (stackData->datatype == DATA_NUMBER) {
            cell->data.value.number = stackData->value.number;

    } else {
        /* oops */
        ePrintf( Runtime, "Can't assign %s to a Dynamic Array",
            datumName[stackData->datatype] );

    }
    tos--;
}



/* getArrayElement: puts pointer to array element on stack */
void getArrayElement( Symbol *s )
{
    int         index;
    Array       *array;
    Variant     *v;

    eMemTest( "getArrayElement: symbol", s );
    array = getArray( s );

    /* dynamic or static? */
    if (array->isDynamic) {
        getDynamicValue( array, s );

    } else {
        /* static array */

        index = getStaticIndex( array, s );
        v = array->data.item+index;
        eMemTest( "getArrayElement: array element", v );

        tos++;
        stack[tos].datatype = DATA_REF;
        stack[tos].value.ref = v;

    }

}

/* setArrayElement: set an item in the array */
void setArrayElement( Symbol *s )
{
    int     offset, type;
    Array   *array;
    Variant *element;

    eMemTest( "setArrayElement: symbol", s );

    array = getArray( s );
    eMemTest( "setArrayElement: array", array );

    if (array->isDynamic) {
        setDynamicValue( array, s );


    } else {

/* this should be implemented as a seperate routine */

        offset = getStaticIndex( array, s );
        element = array->data.item+offset;
        eMemTest( "setArrayElement: array element", element );


        /* need to free string? */
        if (element->datatype == DATA_STRING) {
            eFree( element->value.string );
        }

        /* get the tos */
        type = getStackType( tos );
        switch (type) {
        case DATA_NUMBER:
            element->datatype = DATA_NUMBER;
            element->value.number = popNumber();
            break;

        case DATA_STRING:
            element->datatype = DATA_STRING;
            element->value.string = popString();
            break;

        default:
            ePrintf( Runtime, "setArrayElement: can't store %s %s into Array",
                datumName[type], s->name );
            break;
        }
    }
}

/* pushArray: push an array onto the stack */
void pushArray( Symbol *s )
{
    int stackPos, type;

    if (tos == stackMax) {
        ePrintf( Runtime, "pushArray: stack overflow" );
    }

    tos++;
    stackPos = varStackPos( s );
    type = getStackType( stackPos );
    if (type != DATA_ARRAY) {
        ePrintf( Runtime, "pushArray: %s %s is not an Array",
            datumName[type], s->name );
    }
    stack[tos].datatype = DATA_ARRAY;
    stack[tos].value.array = stack[stackPos].value.array;
}


/* inArray: Returns true if key is in array */
int inArray( Symbol *s )
{
    int         index;
    char        *key;
    Array       *array;

    /* get the array */
    array = getArray( s );

    eMemTest( "inArray: array", array );

    if (!array->isDynamic) {
        ePrintf( Runtime, "%s is a static array", s->name );
    }

    /* get key */
    key = popString();
    index = findKey( array, s, key );
    eFree( key );

    /* found key? */
    if (index == -1) {
        return 0;
    } else {
        return 1;
    }

}


/* eraseArrayElement: erase a single item from an array */
void eraseArrayElement( Symbol *s )
{
    int         index, usedCells, bytes;
    char        *key;
    Array       *array;
    ArrayCell   *cell;
    Variant     *element;

    /* get the array */
    array = getArray( s );

    eMemTest( "eraseArrayElement: array", array );

    /* dynamic or static array? */
    if (array->isDynamic) {

        /* get key */
        key = buildKey( array, s );
        index = findKey( array, s, key );
        eFree( key );

        /* found the key? */
        if (index != -1) {
            /* cell to delete */
            cell = array->data.cell+index;

            /* remove any string data */
            eFree( cell->key );
            if (cell->data.datatype == DATA_STRING) {
                eFree( cell->data.value.string );
            }

            /* calculate chunk of memory to move */
            usedCells = array->lower[0];
            bytes = sizeof( ArrayCell ) * ((usedCells) - index);

            /* move memory, overlapping */
            memmove( (void *)(cell), (void *)(cell+1), bytes );

            /* last cell is now redundant */
            cell = array->data.cell+usedCells;

            /* zap prior value */
            cell->key = NULL;
            cell->data.datatype = DATA_UNDEFINED;

            /* decrease count */
            (array->lower[0])--;

        }

    } else {

        /* get index */
        index = getStaticIndex( array, s );
        element = array->data.item+index;
        eMemTest( "eraseArrayElement: array element", element );

        /* need to free string? */
        if (element->datatype == DATA_STRING) {
            eMemTest( "eraseArrayElement: array element string", element->value.string );
            eFree( element->value.string );
        }

        /* set to zero */
        element->datatype = DATA_NUMBER;
        element->value.number = 0;

    }

}



/* eraseArray: erase an entire array */
void eraseArray( Symbol *s )
{
    int         i;
    char        *string;
    Array       *array;
    Variant     *item;
    ArrayCell   *cell;

    /* get the array */
    array = getArray( s );

    eMemTest( "eraseArray: array", array );

    /* dynamic or static array? */
    if (array->isDynamic) {

        /* free the strings */
        for ( i = 0; i < array->upper[0]; i++ ) {
            cell = array->data.cell + i;
            eMemTest( "eraseArray: cell[]", cell );

            /* free the key */
            eFree( cell->key );
            cell->key = NULL;

            /* free the data */
            if (cell->data.datatype == DATA_STRING) {
                string = cell->data.value.string;
                if (string != NULL) {
                    eFree( string );
                }
            }
            cell->data.datatype = DATA_UNDEFINED;
        }

        /* reset count */
        array->lower[0] = 0;

        /* perhaps this should free allocated memory, too */

    } else {


        /* examine each element */
        for ( i = 0; i < array->elements; i++ ) {
            item = array->data.item+i;
            eMemTest( "freeArray: item[]", item );

            /* free the strings */
            if (item->datatype == DATA_STRING) {
                string = item->value.string;
                if (string != NULL) {
                    eFree( string );
                }
            }
            /* set element value to zero */
            item->datatype = DATA_NUMBER;
            item->value.number = 0;
        }
    }
}


/* freeArray: free an array, if local to routine */
void freeArray( Array *array )
{
    int         i;
    char        *string;
    Variant     *item;
    ArrayCell   *cell;

    eMemTest( "freeArray: array", array );

    /* dynamic or static array? */
    if (array->isDynamic) {

        /* free the strings */
        for ( i = 0; i < array->upper[0]; i++ ) {
            cell = array->data.cell + i;
            eMemTest( "freeArray: cell[]", cell );

            /* free the key */
            eFree( cell->key );
            if (cell->data.datatype == DATA_STRING) {
                string = cell->data.value.string;
                if (string != NULL) {
                    eFree( string );
                }
            }
        }
    /*
    ivanixcu: debug mem leak
    should free  cell struct allocated in createDynamicArray()
    */
    eFree( array->data.cell);

    } else {


        /* free the strings */
        for ( i = 0; i < array->elements; i++ ) {
            item = array->data.item+i;
            eMemTest( "freeArray: item[]", item );
            if (item->datatype == DATA_STRING) {
                string = item->value.string;
                if (string != NULL) {
                    eFree( string );
                }
            }
        }
    }
    eFree( array );

}

/* getArrayIndexes: return number of indexes */
int getArrayIndexes()
{
    int     datatype;
    Array   *array;

    datatype = stack[tos].datatype;
    if (datatype != DATA_ARRAY) {
        ePrintf( Runtime, "First argument must be an array, not %s",
            datumName[datatype] );
    }

    array = stack[tos].value.array;

    if (array->isDynamic) {
        return 1;
    } else {
        return array->indexes;
    }

}


/* getArrayBound: return upper bound of index */
int getArrayBound( int index, int upper )
{
    int     datatype;
    Array   *array;

    datatype = stack[tos].datatype;
    if (datatype != DATA_ARRAY) {
        ePrintf( Runtime, "First argument must be an array, not %s",
            datumName[datatype] );
    }

    array = stack[tos].value.array;

    /* dynamic array? */
    if (array->isDynamic) {
        if (index < 1 || index > 1) {
            ePrintf( Runtime, "Subscript out of range" );
        }
        if (upper) {
            /* used count stored in lower bound */
            return array->lower[index-1];
        } else {
            return 1;
        }
    }


    if (index < 1 || index > array->indexes) {
        ePrintf( Runtime, "Subscript out of range" );
    }

    if (upper) {
        return array->upper[index-1];
    } else {
        return array->lower[index-1];
    }
}
