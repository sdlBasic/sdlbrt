/*
    Name:       class.h
    Purpose:    wrappers to interface C++ classes to wxBasic
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

typedef struct WrappedMethod WrappedMethod;
struct WrappedMethod {
    char            *name;              /* name of method */
    int             hash;               /* hashed method name value */
    int             minArgs;            /* minimum number of args */
    int             maxArgs;            /* maximum number of args */
    void            (*routine)(void);   /* wrapped method */
    WrappedMethod   *prior;             /* prior method in chain */
};

typedef struct WrappedClass WrappedClass;
struct WrappedClass {
    char            *name;          /* class name */
    int             super;          /* superclass index */
    WrappedMethod   *lastMethod;    /* pointer to last method */
};
                
typedef struct WrappedObject WrappedObject;
struct WrappedObject {
    int         pointer;        /* pointer */
    int         classIndex;     /* index to classList */
    int         id;             /* wxWindows identifier */
};

#define         NCLASSES 256
#define         NOBJECTS 1024
#define         NCREATE_STACK 256

WrappedClass    *classList[NCLASSES];       /* builtin classes */
WrappedObject   *objectList[NOBJECTS];      /* objects */
int             createStack[NCREATE_STACK]; /* objects created 'on stack' */

int             nextClass = 1;          /* index of next class */
int             nextObject = 1;         /* index of next object */
int             createTos = 0;          /* top of createdStack */
int             wxObjectIndex = 0;      /* value of _wxObject */
#define HASH_MULTIPLIER 31
#define HASH_NHASH      1024


unsigned int hashVal( char *str );
int findClass( char *name );
int addClass( int superIndex, char *name );
void addMethod( int classIndex, char *name, void (*routine)(void), int minArgs, int maxArgs );
WrappedMethod *findClassMethod( int classIndex, char *name, int hash );
WrappedMethod *findMethod( int classIndex, char *name );
int getObject( Number objectIndex );
char **popStringList(void);
void freeStringList( char **list );
int popPointer( int matchIndex );
void resolveMethod( int objectIndex, char *name );
void runMethod( int classIndex, char *name );
Number addObject( int classIndex, int pointer );
void runDestructor( int objectIndex, int typeOf );
int classSafeOnStack( int classIndex );
void pushCreateStack( int i );
void clearCreateStack();

