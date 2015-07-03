/*
    Name:       trace.c
    Purpose:    Code tracing for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

/* add a line of source code to the linked list */
int eAddSourceCode( int theFileNum, int theLineNum, char *text )
{
    SourceCode  *link;

    /* fill in the link */
    link = (SourceCode *)eMalloc( sizeof( SourceCode ) );
    link->id = sourceLineCounter;
    link->fileNum = theFileNum;
    link->lineNum = theLineNum;
    link->text = eCopyString( text );
    link->prior = lastSourceLink;
    lastSourceLink = link;
    return sourceLineCounter++;
}

/* search source for line of text */
SourceCode *eFindSource( int id )
{
    SourceCode  *code;
    code = lastSourceLink;
    while (code != NULL) {
        if (code->id == id) {
            return code;
        }
        code = code->prior;
    }
    return NULL;
}

