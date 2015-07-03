/*
    Name:       symbol.c
    Purpose:    Data structures for wxBasic symbols
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

/* maskIfHidden: mask if symbol is hidden */
Symbol *maskIfHidden( Symbol *s ) {

    /* only applies to variables and arrays */
    if (s->symboltype != SYM_VARIABLE &&
        s->symboltype != SYM_ARRAY ) {
            return s;
    }

    /* visible if in current scope or common */
    if (s->scope == currentScope || s->common ) {
        return s;
    }

    /* visible global? */
    if (currentScope != NULL) {
        /* can see if no explict option set */
        if (!explicitFlag) {
            return s;
        }

        /* visible if not shared */
        if (inStack(sharedStack, (intptr_t)s )) {
            return s;
        }
    }

    return NULL;

}

/* findSymbol: find symbol in symbol list */
Symbol *findSymbol( char *name, Symbol *scope )
{
    Symbol  *s;

    /* name isn't tested, because it can come from a static table */
    eMemTest( "findSymbol: scope", scope );

    for ( s = lastSymbol; s != NULL; s = s->prior ) {

        /* in scope or common? */
        if (s->scope == scope || s->common ) {
            /* same name? */
            if (strcmp( s->name, name ) == 0 ) {
                /* hidden? */
                return maskIfHidden(s);
            }
        }
    }
    return NULL;
}

/* addChildSymbol: add sibling to symbol */
void addChildSymbol( Symbol *s, Symbol *child )
{
    eMemTest( "addChildSymbol: parent", s );
    eMemTest( "addChildSymbol: child", child );

    /* first child? */
    if (s->child == NULL) {
        s->child = child;
        return;
    }

    /* walk to end of sibling chain */
    for ( s = s->child; s->sibling != NULL; s = s->sibling ) {
        eMemTest( "addChildSymbol: sibling", s );
    }
    s->sibling = child;
}


/* addSymbol: add symbol to symbol list */
Symbol *addSymbol( char *name, Symbol *scope, int symboltype )
{
    Symbol  *s;

    /* name isn't tested, because it can come from a static table */
    eMemTest( "addSymbol: scope", scope );

    s = findSymbol( name, scope );
    if (s != NULL) {
        ePrintf( Runtime, "addSymbol: %s %s is already defined as %s",
            symbolName[symboltype], name, symbolName[s->symboltype] );
    }

    s = (Symbol *)eMalloc( sizeof( Symbol ) );
    s->name = eCopyString( name );
    s->symboltype = symboltype;
    s->klass = 0;
    s->scope = scope;
    s->common = commonFlag;
    s->stackPos = 0;
    s->args = 0;
    s->optargs = 0;
    s->locals = 0;
    s->prior = lastSymbol;
    s->child = NULL;
    s->sibling = NULL;
    s->forward = 0;
    s->code = NULL;
    s->builtin = NULL;
    lastSymbol = s;

    return s;
}


/* findChildSymbol: find symbol in symbol list with given index */
Symbol *findChildSymbol( Symbol *parent, int index )
{

    Symbol  *child;

    eMemTest( "addChildSymbol: parent", parent );

    /* get child */
    index--;
    child = parent->child;
    eMemTest( "addChildSymbol: child", child );

    if (index==0) {
        return child;
    }

    while (index > 0) {
        index--;

        /* get next sibling */
        child = child->sibling;
        eMemTest( "addChildSymbol: sibling", child );

        /* end of chain? */
        if (child == NULL) {
            break;
        }
    }
    return child;
}



/* checkArgCount: aborts with error if arg count doesn't match */
void checkArgCount( Symbol *s, int args )
{
    int     minArgs = s->args,
            maxArgs = minArgs + s->optargs;

    eMemTest( "checkArgCount: s", s );

    if (s->optargs == 0) {
        if (args != s->args ) {
            ePrintf( Syntax, "%s %s expects %d args, not %d",
                symbolName[s->symboltype], s->name, s->args, args );
        }
    } else if (args < minArgs ) {
            ePrintf( Syntax, "%s %s expects at least %d args, not %d",
                symbolName[s->symboltype], s->name, minArgs, args );

    } else if (args > maxArgs ) {
            ePrintf( Syntax, "%s %s expects at most %d args, not %d",
                symbolName[s->symboltype], s->name, maxArgs, args );
    }
}


