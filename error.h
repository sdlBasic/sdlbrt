/*
    Name:       error.h
    Purpose:    error support routines
    Author:     David Cuny
                Partially derived from Brian Kernighan and Rob Pike
                The Practice of Programming
*/


typedef struct MemLink MemLink;


struct MemLink {
    int     start;     /* start of allocated block */
    int     end;       /* end of allocated block */
    MemLink * next;      /* in list */
};

extern MemLink *lastMemLink ;//=NULL

enum {
    Init,       /* initialization error */
    Syntax,     /* syntax error */
    Runtime     /* runtime error */
};

//static char *eprogname = NULL;          /* program name for messages    */

extern void eShutdown( int errorlevel );
extern void ePrintf( int errType, char *fmt, ... );
extern void eConsole( char *fmt, ... );
extern void eAddMemLinkDebug( void *p, int n );
extern void eRemoveMemLinkDebug( void *address );
extern MemLink *lookupMemLink( void *p );
extern void eMemTestDebug( char *message, void *address );
extern void freeMemLinksDebug( void );
extern char *eCopyString(char *s);
extern void expected( char *expect );
extern void *eMalloc(size_t size);
extern void *eRealloc( void *old, size_t size);
extern void eFreeDebug( void *address );
extern void screendebug();
