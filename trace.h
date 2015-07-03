/*
    Name:       trace.h
    Purpose:    Code tracing for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

typedef struct SourceCode SourceCode;

struct SourceCode {
    int         id;         /* unique identifier */
    int         fileNum;    /* file the source line came from */
    int         lineNum;    /* line number from the file */
    char        *text;      /* line of code */
    SourceCode  *prior;     /* link to prior line of code */
};

int sourceLineCounter = 0;  /* value of next SourceCode->id */

SourceCode  *lastSourceLink = NULL;     /* linked list of source code   */

int eAddSourceCode( int theFileNum, int theLineNum, char *text );
SourceCode *eFindSource( int id );
