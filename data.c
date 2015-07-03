/*
    Name:       data.c
    Purpose:    builtin types in wxBasic
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

/* formatNumber: format number in buffer, remove trailing zeros */
void formatNumber( char *buffer, Number n )
{
    int     i;

    /* no floating point? */
    if (floor(n) == n) {
        sprintf( buffer, NUMBER_INT_FORMAT, n );

    } else {
        /* format with floating point */
        sprintf( buffer, NUMBER_FLOAT_FORMAT,n );

        /* search for non-zero */
        for( i = strlen(buffer)-1; i > 0; i-- ) {
            if (buffer[i] != '0') {
                break;
            } else if (buffer[i-1] != '.') {
                buffer[i] = '\0';
            }
        }
    }



}



/* addGlobalToStack: return index for global on stack */
int addGlobalToStack()
{
    globals++;
    stackMax--;
    if (tos == stackMax) {
        ePrintf( Runtime, "addGlobalToStack: out of stack space");
    }
    return stackMax+1;
}

/* pushNumber: push a number onto the stack */
void pushNumber( Number value )
{
    if (tos == stackMax) {
        ePrintf( Runtime, "pushNumber: stack overflow" );
    }

    tos++;
    stack[tos].datatype = DATA_NUMBER;
    stack[tos].value.number = value;


}

/* getStackPointer: return pointer from stack */
Variant *getStackPointer( int index )
{
    /* indirected? */
    if (stack[index].datatype == DATA_REF) {
        return stack[index].value.ref;
    } else {
        return &stack[index];
    }
}


/* dropTos: remove top of stack and discard */
void dropTos()
{
    /* need to free? */
    if (stack[tos].datatype == DATA_STRING) {
        free( stack[tos].value.string );
    }
    stack[tos--].datatype = DATA_UNDEFINED;
}

/* popNumber: pop a number off the stack */
Number popNumber()
{
    Number  result;
    Variant *v;

    if (tos==0) {
        ePrintf( Runtime, "popNumber: stack underflow" );
    }

    v = getStackPointer( tos );
    switch (v->datatype) {
    case DATA_NUMBER:
    case DATA_OBJECT:
        tos--;
        return v->value.number;

    case DATA_STRING:
        result = (Number)atof(v->value.string);

        /* need to free? */
        if (stack[tos].datatype == DATA_STRING) {
            free( stack[tos].value.string );
            stack[tos].datatype = DATA_UNDEFINED;
        }
        tos--;
        return result;

    default:
        /* silently fail... */
        tos--;
        return 0;
    }
}


/* pushStringCopy: push a copy of a string onto the stack */
void pushStringCopy( char *string )
{
    if (tos == stackMax) {
        ePrintf( Runtime, "pushStringCopy: stack overflow" );
    }

    tos++;
    stack[tos].datatype = DATA_STRING;
    if (string==NULL) {
        stack[tos].value.string = eCopyString("");
    } else {
        stack[tos].value.string = eCopyString( string );
    }

}

/* pushString: push a String onto the stack */
void pushString( char *string )
{

    if (tos==stackMax) {
        ePrintf( Runtime, "PushString: stack overflow" );
    }

    tos++;
    stack[tos].datatype = DATA_STRING;
    if (string==NULL) {
        stack[tos].value.string = eCopyString("");
    } else {
        stack[tos].value.string = eCopyString(string);
    }

}


/* popString: pop a string off the stack */
char *popString()
{
    char    *string;
    Variant *v;
    char    buffer[32];

    if (tos==0) {
        ePrintf( Runtime, "PopString: stack underflow" );
    }

    v = getStackPointer( tos );
    if (stack[tos].datatype == DATA_STRING) {
        /* string on stack */
        string = v->value.string;
        v->datatype = DATA_UNDEFINED;

    } else if (v->datatype == DATA_STRING) {
        /* copy from ref */
        string = eCopyString( v->value.string );

    } else if (v->datatype == DATA_NUMBER) {
        formatNumber( buffer, v->value.number );
        string = eCopyString( buffer );

    } else {
        /* create an empty string */
        string = eCopyString("");
    }
    tos--;
    return string;
}

/* copyStackItem: copy stack item to top of stack */
void copyStackItem( int index )
{

    if (tos == stackMax) {
        ePrintf( Runtime, "copyStackItem: stack overflow" );
    }
    tos++;

    switch (stack[index].datatype) {
    case DATA_UNDEFINED:
        stack[tos].datatype = DATA_UNDEFINED;
        break;

    case DATA_REF:
        stack[tos].datatype = DATA_REF;
        stack[tos].value.ref = stack[index].value.ref;
        break;

    case DATA_NUMBER:
    case DATA_STRING:
    case DATA_OBJECT:
        stack[tos].datatype = DATA_REF;
        stack[tos].value.ref = getStackPointer( index );
        break;

    case DATA_ARRAY:
        stack[tos].datatype = stack[index].datatype;
        stack[tos].value.array = stack[index].value.array;
        break;

    default:
        ePrintf( Runtime, "copyStackItem: unknown data type: %s",
            datumName[ stack[index].datatype ] );
    }
}


/* getStackType: return datatype of item on stack */
int getStackType( int index )
{
    Variant *v;
    v = getStackPointer( index );
    return v->datatype;
}


/* printTos: print top of stack item, core of print routine */
void printTos()
{
    char    *string;
    char    buffer[32];
    int     typeOf;

    typeOf = getStackType( tos );
    switch (typeOf) {
    case DATA_NUMBER:
        formatNumber( buffer, popNumber() );
        eConsole( "%s", buffer );
        break;

    case DATA_STRING:
        string = popString();
        eConsole( "%s", string );
        free( string );
        break;

    case DATA_OBJECT:
        eConsole( "%d", (int)popNumber() );

    default:
        ePrintf( Runtime, "printTos: can't print %s", datumName[typeOf] );
    }
}

/* printStack: display stack for debugging */
void printStack()
{
    int     i;
    char    flag;
    Variant *v;

    for ( i = 0; i <= tos; i++ ) {

        v = getStackPointer( i );
        if (stack[i].datatype == DATA_REF) {
            flag = '*';
        } else {
            flag = ' ';
        }

        switch (v->datatype) {
        case DATA_UNDEFINED:
            eConsole( "(%d)->undefined ", i );
            break;
        case DATA_NUMBER:
            eConsole( "(%d)->%c%Lf ", i, flag, v->value.number );
            break;
        case DATA_STRING:
            eConsole( "(%d)->%c%s ", i, flag, v->value.string );
            break;
        case DATA_ARRAY:
            eConsole( "(%d)->array ", i );
            break;
        case DATA_REF:
            eConsole( "(%d)->REF ", i );
        case DATA_OBJECT:
            eConsole( "(%d)->OBJ:%Lf ", i, v->value.number );
            break;
        default:
            eConsole( "(%d)->%s ", i, datumName[stack[i].datatype] );
            break;
        }
        if (i==localstart){
            eConsole("[LOCALS]");
        }
    }
    eConsole( "[TOS]\n" );
}

