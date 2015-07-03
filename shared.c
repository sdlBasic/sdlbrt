/*
    Name:       shared.h
    Purpose:    Forward declarations for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/


#define NUMBER_FLOAT_FORMAT "%Lf"
#define NUMBER_INT_FORMAT "%.0Lf"
#define ALLOWABLE_ERROR DBL_EPSILON


#define NINDEX 4                /* number of indexes allowed            */
#define NOPTARGS 8              /* max number of optional args          */
#define INCLUDE_MAX 32          /* maximum number of include files */
#define INCLUDE_MAXDEPTH 16     /* maximum nesting of include files */
#define MAX_CONSOLE_LINES 256   /* maximum number of lines shown in console */
#define EXTRA_CONSOLE_LINES 64  /* amount to remove at a time */


int     cmdArgc;                /* argc from command line */
char    *cmdArgv[32];           /* argv from command line */
FILE    *inFile;                /* handle to file being parsed */
char    *cwd = NULL;            /* current working directory */
char    currtok[256];           /* current token */
int     errFlag = 0;            /* set by yyerror */
int     consoleFlag = 1;        /* if false, supress console */
int     explicitFlag = 0;       /* Option Explicit */
int     commonFlag = 0;         /* common declaration */
int     qBasicFlag = 0;         /* Option QBasic */
int     fileNum = 0;            /* current file number */
int     lineNum = 0;            /* current line number of current file */
int     parseLineId = 0;        /* id of line being parsed */
int     runLineId = 0;          /* id of line being run */
int     includeCount = 0;       /* number of source files read */
char    *includeList[INCLUDE_MAX];      /* names of files included */
int     visibleWindow = 0;      /* true if any window is visible */
int     argCount = 0;           /* count of args being passed on stack */
Symbol  *currentScope;          /* routine being defined */
Symbol  *oldScope[255];		/* old currentScope */
int 	oldScopeP;		/* pointer of last oldscope */
Symbol  *currentTypeDef;        /* type being defined */
Symbol  *currentType;           /* type being referenced */
int     me;                     /* pointer to object for current method */
int     wxAppIndex = 0;         /* handle to wxApp */

int 	debug;			/* step mode */
int 	nodebug=0;			/* disable debugger screen for prod code */

Stack *argCountStack;           /* arg count in parser */
Stack *blockStack;              /* block type */
Stack *lineStack;               /* line number */
Stack *sharedStack;             /* shared symbols */
Node *deferredCode = NULL;      /* deferred code */

