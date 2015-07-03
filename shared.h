/*
    Name:       shared.h
    Purpose:    Forward declarations for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/
#if !defined(WIN32) && !defined(__APPLE__)
    typedef long double Number;    /* internal value numbers are stored as */
#else
    typedef double Number;    /* internal value numbers are stored as */
#endif

#define NUMBER_FLOAT_FORMAT "%Lf"
#define NUMBER_INT_FORMAT "%.0Lf"
#define ALLOWABLE_ERROR DBL_EPSILON

typedef struct Stack Stack;     /* integer stack, for misc. tasks       */
typedef union Value Value;      /* union of types data stack can hold   */
typedef struct Variant Variant; /* type + value                         */
typedef struct ArrayCell ArrayCell; /* cell of associative array        */
typedef struct Array Array;     /* array                                */
typedef struct Symbol Symbol;   /* token descriptor                     */
typedef struct Node Node;       /* parse tree node                      */
typedef struct Type Type;       /* core datatypes                       */

#define NINDEX 4                /* number of indexes allowed            */
#define NOPTARGS 8              /* max number of optional args          */
#define INCLUDE_MAX 32          /* maximum number of include files */
#define INCLUDE_MAXDEPTH 16     /* maximum nesting of include files */
#define MAX_CONSOLE_LINES 256   /* maximum number of lines shown in console */
#define EXTRA_CONSOLE_LINES 64  /* amount to remove at a time */


extern int     cmdArgc;                /* argc from command line */
extern char    *cmdArgv[32];           /* argv from command line */
extern FILE    *inFile;                /* handle to file being parsed */
extern char    *cwd;            /* current working directory */
extern char    currtok[256];           /* current token */
extern int     errFlag;            /* set by yyerror */
extern int     consoleFlag;        /* if false, supress console */
extern int     explicitFlag;       /* Option Explicit */
extern int     commonFlag;         /* common declaration */
extern int     qBasicFlag;         /* Option QBasic */
extern int     fileNum;            /* current file number */
extern int     lineNum;            /* current line number of current file */
extern int     parseLineId;        /* id of line being parsed */
extern int     runLineId;          /* id of line being run */
extern int     includeCount;       /* number of source files read */
extern char    *includeList[INCLUDE_MAX];      /* names of files included */
extern int     visibleWindow;      /* true if any window is visible */
extern int     argCount;           /* count of args being passed on stack */
extern Symbol  *currentScope;          /* routine being defined */
extern Symbol  *oldScope[255];		/* old currentScope */
extern int 	oldScopeP;		/* pointer of last oldscope */
extern Symbol  *currentTypeDef;        /* type being defined */
extern Symbol  *currentType;           /* type being referenced */
extern int     me;                     /* pointer to object for current method */
extern int     wxAppIndex;         /* handle to wxApp */

extern int 	nodebug;			/* disable debugger, for production code */
extern int 	debug;			/* step mode */

extern Stack *argCountStack;           /* arg count in parser */
extern Stack *blockStack;              /* block type */
extern Stack *lineStack;               /* line number */
extern Stack *sharedStack;             /* shared symbols */
extern Node *deferredCode;      /* deferred code */

