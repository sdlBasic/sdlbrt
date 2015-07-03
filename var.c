/*
    Name:       var.c
    Purpose:    wxBasic simple variables
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/



/* returnVar: return symbol for var, can optionally create it. */
Symbol *returnVar( char *name, int symType, int create )
{

    Symbol  *s;

    /* look in scope */
    s = findSymbol( name, currentScope );

    /* global? */
    if (s==NULL && currentScope != NULL && !create) {
        s = findSymbol( name, NULL );
    }

    /* create request, but already exists? */
    if (create && s != NULL) {
        ePrintf( Syntax, "%s already exists as %s",
            name, symbolName[s->symboltype]);
            
    }

    /* validate before passing back */
    if (s != NULL) {
        if (s->symboltype != symType) {
            ePrintf( Syntax, "%s is a %s, not a %s",
                s->name, symbolName[s->symboltype], symbolName[symType] );
        } else {
            return s;
        }
    }

    /* can't implicitly create it? */
    if (!create && explicitFlag) {
        ePrintf( Syntax, "%s has not been declared\n", name );
    }

    s = addSymbol( name, currentScope, symType );

    if (currentScope==NULL) {
        /* create as global */
        s->stackPos = addGlobalToStack();
        stack[s->stackPos].datatype = DATA_UNDEFINED;

    } else {
        /* create as local */
        currentScope->locals++;
        s->stackPos = currentScope->locals + currentScope->optargs;
        /* set as child */
        addChildSymbol( currentScope, s );
    }

    return s;
}

/* createConst: create constant */
Symbol *createConst( char *name )
{
    Symbol  *s = NULL;

    s = addSymbol( name, currentScope, SYM_CONSTANT );

    /* create as global */
    s->stackPos = addGlobalToStack();

    stack[s->stackPos].datatype = DATA_NUMBER;
    stack[s->stackPos].value.number = 0;

    return s;
}


/* createParm: create a parameter */
Symbol *createParm( char *name, int symType )
{
    Symbol  *s;

    s = returnVar( name, symType, 1 );
    if (symType == SYM_ARRAY) {
        s->args = 1;
        s->optargs = NINDEX;
    }

    currentScope->args++;
    currentScope->locals = currentScope->args;

    return s;
}


/* varStackPos: return position of var on stack */
int varStackPos( Symbol *s )
{
    /* function return values are at the start of locals */
    if (s->symboltype == SYM_FUNCTION) {
        return localstart;
    }

    if (s->scope == NULL) {
        /* absolute position */
        return s->stackPos;
    } else {
        /* relative position */
        return localstart+(s->stackPos);
    }
}

/* setStack: store tos value at index */
void setStack( int index )
{
    Variant *source, *dest;

    /* should not happen */
    if (index<0) {
        ePrintf( Runtime, "setStack: stack error" );
    }

    source = getStackPointer( tos );
    dest = getStackPointer( index );

    /* free string currently stored? */
    if (dest->datatype == DATA_STRING) {
        free( dest->value.string );
    }

    if (source->datatype == DATA_STRING) {
        dest->datatype= DATA_STRING;
        dest->value.string = popString();

    } else if (source->datatype == DATA_NUMBER) {
        dest->datatype= DATA_NUMBER;
        dest->value.number = popNumber();

    } else if (source->datatype == DATA_OBJECT) {
        dest->datatype= DATA_OBJECT;
        dest->value.number = popNumber();

    } else {
        ePrintf( Runtime, "setStack: can't fetch %s", datumName[dest->datatype] );
    }
}

/* setVar: store tos in local variable */
void setVar( Symbol *s )
{
    setStack( varStackPos( s ) );
}

/* setReturn: store tos in return */
void setReturn()
{
    setStack( localstart-1 );
}

/* getVar: push variable pointer or value onto stack */
void getVar( Symbol *s )
{
    copyStackItem( varStackPos( s ) );
}

