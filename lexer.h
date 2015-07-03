/*
    Name:       lexer.h
    Purpose:    Convert source wxBasic code into tokens
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

int pushIncludeFile( char *s, long offset );
int pushZipIncludeFile(char *zipfile, char *s, long offset );
void popIncludeFile();
void fixEol();
char getChar();
void ungetChar();
int nextTokenIsSep();
int lexDigits();
int lexHexDigits();
int lexBackquotedChar();
void lexString();
int isNonBreakingChar( char c );
void lexIdentifier( int c );
int identifyWord();
int follows( int letter, int ifTrue, int ifFalse );
int yylex();
void yyerror( char *s );
