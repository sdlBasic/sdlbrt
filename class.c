/*
    Name:       class.c
    Purpose:    wrappers to interface C++ classes to wxBasic
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/
#pragma GCC diagnostic ignored "-Wunused-result"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

/* hashVal: compute hash value for string */
unsigned int hashVal( char *str )
{
    unsigned int    h;
    unsigned char   *p;

    h = 0;
    for (p= (unsigned char *) str; *p != '\0'; p++ ) {
        h = HASH_MULTIPLIER * h + *p;
    }
    return h % HASH_NHASH;
}


/* findClass: return the index to the class; -1 on failure */
int findClass( char *name )
{
    int        i, nameHash;
    WrappedClass        *theClass;

    nameHash = hashVal( name );
    for ( i = nextClass-1; i >= 0; i-- ) {
        theClass = classList[i];
    if (strcmp( theClass->name, name ) == 0) {
            return i;
        }
    }
    return -1;
}

/* addClass: add a class, return the index */
int addClass( int superIndex, char *name )
{
    WrappedClass        *theClass;
    Symbol          *s;

    /* array size is static */
    if (nextClass > NCLASSES){
        ePrintf( Runtime, "addClass: reached class limit of %d", NCLASSES);
    }

    /* create class */
    theClass = (WrappedClass *)eMalloc( sizeof( WrappedClass ) );
    theClass->name          = eCopyString( name );
    theClass->super         = superIndex;
    theClass->lastMethod    = NULL;
    classList[nextClass]    = theClass;

    /* add to symbol table */
    s = addSymbol( name, NULL, SYM_CLASS );
    s->klass = nextClass;

    return nextClass++;
}

/* addMethod: add a method to a class */
void addMethod( int classIndex, char *name, void (*routine)(void),
                    int minArgs, int maxArgs )
{
    WrappedMethod        *theMethod;

    theMethod = (WrappedMethod *)eMalloc( sizeof( WrappedMethod ) );

    theMethod->name     = eCopyString( name );
    theMethod->hash     = hashVal( name );
    theMethod->routine  = routine;
    theMethod->minArgs  = minArgs;
    theMethod->maxArgs  = maxArgs;

    theMethod->prior = classList[classIndex]->lastMethod;
    classList[classIndex]->lastMethod = theMethod;
}

/* findClassMethod: search class for method */
WrappedMethod *findClassMethod( int classIndex, char *name, int hash )
{
    WrappedMethod        *theMethod;

    for ( theMethod = classList[classIndex]->lastMethod;
          theMethod != NULL;
          theMethod = theMethod->prior ) {
        if ( hash == theMethod->hash && strcmp( name, theMethod->name ) == 0 ) {
                return theMethod;
        }
    }
    return NULL;
}

/* findMethod: search inheritance tree for method, return NULL on failure */
WrappedMethod *findMethod( int classIndex, char *name )
{
    int hash;
    WrappedMethod        *theMethod;

    /* name hash for speed */
    hash = hashVal( name );

    /* search for match */
    for ( ; classIndex != 0; classIndex = classList[classIndex]->super ) {
    theMethod = findClassMethod( classIndex, name, hash );
        if (theMethod != NULL) {
            return theMethod;
        }
    }
    return NULL;
}


/* getObject: get pointer */
int getObject( Number objectIndex )
{

    /* null is a special case */
    if (objectIndex == 0) {
        return 0;
    }

    if (objectIndex < 0 || objectIndex >= nextObject
            || objectIndex != (int)objectIndex ) {
        ePrintf( Runtime, "getObject: %lf is not a valid handle", objectIndex );

    } else if (objectList[(int)objectIndex] == NULL) {
        ePrintf( Runtime, "getObject: %d is null (possibly destroyed)", (int)objectIndex );
    }

    return objectList[(int)objectIndex]->pointer;
}

/* popStringList: pop a delimited list off the stack, returns pointer */
char **popStringList()
{
    int     i, items, atChar, atWord;
    char    buffer[128];
    char    *text, *word;
    char    **list;

    text = popString();

    /* count the number of items */
    items = 1;
    for( i = 0; text[i] != '\0'; i++ ) {
        if (text[i] == '|') {
            items++;
        }
    }

    /* allocate space for the string list */
    list = (char **)eMalloc( sizeof( char *) * (items + 1) );

    /* build the words */
    atChar = 0;
    atWord = 0;
    for ( i=0; ; i++ ) {
        /* seperator? */
        if (text[i] == '|' || text[i] == '\0' ) {
                        buffer[atChar] = '\0';
            /* allocate buffer for word */
            word = (char *)eMalloc( sizeof( char ) * (atChar + 1) );
            strcpy( word, buffer );

            /* add to list */
            list[atWord++] = word;
            atChar = 0;
        } else {
            /* add char to buffer */
            buffer[atChar++] = text[i];
        }
        /* end of list? */
        if (text[i] == '\0') {
            break;
        }
    }
    list[atWord] = NULL;
    return list;
}

/* free string in list */
void freeStringList( char **list )
{
        int i;

        for (i = 0; list[i] != NULL; i++ ) {
        eFree( list[i] );
        }
    eFree( list );
}

/* popPointer: pop object index off stack, and return pointer */
int popPointer( int matchClassIndex )
{
    /* at some point, it should verify the class */
    int     handle, objectIndex, classIndex, i;

    /* return the pointer; check range */
    objectIndex = (int)popNumber();
    if (objectIndex == 0 ){
        /* void */
        return 0;
    }
    handle = getObject( objectIndex );

    /* correct class? */
    classIndex = objectList[objectIndex]->classIndex;
    for( i = classIndex; i != 0; i = classList[i]->super ) {
        if (i == matchClassIndex) {
            break;
        }
    }
    if (i == 0) {
        ePrintf( Runtime, "popPointer: expected %s, not %s",
            classList[matchClassIndex]->name, classList[classIndex]->name );
    }
    return handle;
}


/* resolveMethod: determine class of method and run it */
void resolveMethod( int objectIndex, char *name )
{
    int             classIndex;

    /* get pointer, check range */
    me = getObject( objectIndex );

    /* null? */
    if (objectIndex == 0) {
        ePrintf( Runtime, "can't resolve method null.%s", name );
    }

    /* get the class */
    classIndex = objectList[objectIndex]->classIndex;

    /* run it */
    runMethod( classIndex, name );
}


/* runMethod: find and execute a method */
void runMethod( int classIndex, char *name )
{
    WrappedMethod   *method;

    /* find the method */
    method = findMethod( classIndex, name );
    if (method == NULL) {
        ePrintf( Runtime, "Can't find method %s.%s", classList[classIndex]->name, name );
    }

    /* check args */
    if (argCount < method->minArgs || argCount > method->maxArgs ) {
        if (method->minArgs == method->maxArgs) {
            ePrintf( Runtime, "Method %s.%s expected %d args, not %d args",
                classList[classIndex]->name, method->name,
                method->minArgs, argCount );

        } else {
            ePrintf( Runtime, "Method %s.%s expected %d to %d args, not %d args",
                classList[classIndex]->name, method->name,
                method->minArgs, method->maxArgs, argCount );
        }
    }

    /* execute, leave result on stack */
    (*method->routine)();
}


/* addObject: add an object of a given class */
Number addObject( int classIndex, int pointer )
{
    int             i, objectIndex;
    WrappedObject   *theObject;

    /* note objects start at 1, not 0 */
    objectIndex = 0;

    /* search for an empty slot to reuse */
    for ( i = 1; i < nextObject; i++ ) {
        if (objectList[i] == NULL) {
            objectIndex = i;
                break;
        }
    }
    /* no old slots free? */
    if (objectIndex == 0) {
        if (nextObject == NOBJECTS) {
            ePrintf( Runtime, "addObject: reached object limit of %d", NOBJECTS);
        }
        objectIndex = nextObject++;
    }

    theObject = (WrappedObject *)eMalloc( sizeof( WrappedObject ) );
    theObject->pointer      = pointer;
    theObject->classIndex   = classIndex;
    theObject->id           = 0;

    objectList[objectIndex] = theObject;
    return (Number)objectIndex;
}

/* runDestructor: run destructor */
void runDestructor( int objectIndex, int typeOf )
{
    WrappedObject   *object;
    WrappedMethod   *method=NULL;

    /* get pointer, check range */
    me = getObject( objectIndex );

    object = objectList[objectIndex];
    switch (typeOf) {
    case 0:
        /* don't run destructor */
        method = NULL;
        break;

    case OpDelete:
        method = findMethod( object->classIndex, "del" );
        if (method == NULL) {
            ePrintf( Runtime, "runDestructor: can't find %s.delete method",
                classList[object->classIndex]->name );
        }
        break;

    case OpDestroy:
        method = findMethod( object->classIndex, "dtor" );
        if (method == NULL) {
            ePrintf( Runtime, "runDestructor: can't find %s.destroy method",
                classList[object->classIndex]->name );
        }
        break;

    default:
        ePrintf( Runtime, "runDestructor: bad opcode of %d\n", typeOf );
        break;
    }

    /* execute */
    if (method != NULL) {
        (*method->routine)();
    }

    /* free */
    eFree( object );
    objectList[objectIndex] = NULL;

}

/* classSafeOnStack: returns true if safe to create on stack */
int classSafeOnStack( int classIndex )
{
    return 1;
}


/* pushCreateStack: add an object to the create stack */
void pushCreateStack( int i )
{
    createTos++;
    if (createTos >= NCREATE_STACK ) {
        ePrintf( Runtime, "pushCreateStack: limit of %d exceeded", NCREATE_STACK );
    }

    createStack[createTos] = i;
}

/* clearCreateStack: pop (and destroy) objects on create stack */
void clearCreateStack()
{
    /* destroy objects on stack */
    while (createStack[createTos]) {
        runDestructor( createStack[createTos], OpDelete );
        createTos--;
    }
    createTos--;
}

