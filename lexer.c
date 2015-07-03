/*
    Name:       lexer.c
    Purpose:    Convert source wxBasic code into tokens
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define INBUFFER_MAX 1024               /* maximum size of line of code */

char    lineBuffer[INBUFFER_MAX];       /* line from source code */
char    word[INBUFFER_MAX];             /* token parsed from source */
int     wordPos = 0;
int     lineBufferPos = -1;             /* position in line buffer */
int     eofFlag = 0;                    /* end of file flag */


typedef struct IncludeData IncludeData;
struct IncludeData {
    FILE    *handle;        /* file handle */
    int     fileNum;        /* index to name in includeList */
    int     lineNum;        /* line number last read */
};

IncludeData includeStack[INCLUDE_MAXDEPTH];
int includeTos = -1;

/* pushIncludeFile: set file to be parsed */
int pushIncludeFile( char *s, long offset )
{
    char    fileName[256];

    /* save line number */
    if (includeTos > -1) {
        includeStack[includeTos].lineNum = lineNum;
    }

    includeTos++;
    if (includeTos == INCLUDE_MAXDEPTH) {
        ePrintf( Runtime, "Can't include %s, include stack depth of %d exceeded",
            s, INCLUDE_MAXDEPTH );
    }

    /* save name */
    if (includeCount > INCLUDE_MAX) {
        ePrintf( Runtime, "Can't include %s, maximum number of include files is %d",
            s, INCLUDE_MAX );
    }
    includeList[includeCount] = eCopyString(s);
    fileNum = includeCount;
    includeCount++;

    /* open new */
    inFile = fopen( s, "rt" );
    lineNum = 0;
    if (inFile != NULL) {
        strcpy( fileName, s );

    } else {
        /* try full file name */
#if !defined(AMIGA)
        if (cwd != NULL && strlen(cwd)) {
            strcpy( fileName, cwd );
            strcat( fileName, s );
#else
        {
            strcpy(fileName, s);
#endif

            inFile = fopen( fileName, "rt" );
            if ((inFile == NULL) || isdir(fileName)) {
                ePrintf( Init, "Unable to open file %s\n", fileName );
				return 0;
            }
        }
    }

    /* offset into the file? */
    if (offset != 0) {
        /* seek to position in file */
        fseek( inFile, offset, 0 );
    }

    /* save handle */
    includeStack[includeTos].handle = inFile;
    return 1;
}

/* pushZipIncludeFile: set file to be parsed */
int pushZipIncludeFile( char *zipfile, char *s, long offset )
{
    char *tmpfile;

    #ifndef WIN32
	char *tmpdir="/tmp";
    #else
	char *tmpdir=getenv("tmp");
    #endif
    if (file_unzip(zipfile,s,tmpdir)==0){
	tmpfile=(char *) malloc(strlen(tmpdir)+strlen(s)+2);
	strcpy(tmpfile,tmpdir);
	strcat(tmpfile,"/");
	strcat(tmpfile,s);
	tmpfile[strlen(tmpfile)]='\0';
  	  if (pushIncludeFile( tmpfile, offset )) { remove(tmpfile); return 1; } else { remove(tmpfile); return 0; }
    } else {
      return 0;
    }
}

/* popIncludeFile: pop to prior file on stack */
void popIncludeFile()
{
    /* close file */
    fclose( inFile );
    eofFlag = 0;

    /* pop stack */
    includeTos--;
    if (includeTos > -1 ) {
        /* restore prior settings */
        fileNum = includeStack[includeTos].fileNum;
        lineNum = includeStack[includeTos].lineNum;
        inFile = includeStack[includeTos].handle;
    }

    wordPos = 0;
    lineBufferPos = -1;

}


/* fix the eol char to work under DOS and Linux */
void fixEol()
{
    int len;

    len = strlen( lineBuffer );
    if (len > 1) {
        /* need to adjust for linux or mac eol? */
        if ((lineBuffer[len-2] == '\r' && lineBuffer[len-1] == '\n') ||
            (lineBuffer[len-2] == '\n' && lineBuffer[len-1] == '\r' )) {
            lineBuffer[len-2] = '\n';
            lineBuffer[len-1] = '\0';
        /* missing eol? */
        } else if (lineBuffer[len-1] != '\r' && lineBuffer[len-1] != '\n') {
            lineBuffer[len] = '\n';
            lineBuffer[len+1] = '\0';
        }
    }
}

/* getChar: read a char from the input file */
char getChar()
{
    /* end of file? */
    if (eofFlag) {
        return EOF;
    }

    /* end of buffer? */
    if (lineBufferPos == -1 || lineBuffer[lineBufferPos+1] == '\0') {
        lineBufferPos = -1;
        if (fgets( lineBuffer, INBUFFER_MAX-2, inFile ) == 0) {
            popIncludeFile();
            if (includeTos == -1) {
                eofFlag = 1;
                return EOF;
            } else {
                /* sort of hacky, but it works */
                return getChar();
            }
        }

        fixEol();

        /* save */
        lineNum++;
        parseLineId = eAddSourceCode( fileNum, lineNum, lineBuffer );

        /* shell comment? */
        if (lineNum == 1 && lineBuffer[0] == '#' ) {
            /* skip this line */
            lineBufferPos = -1;
            return getChar();
        }


    }
    lineBufferPos++;
    return lineBuffer[lineBufferPos];
}

/* ungetChar: move buffer back one char */
void ungetChar()
{
    lineBufferPos--;
}

/* nextTokenIsSep: true if next token is '\n' or ':' */
int nextTokenIsSep()
{
    int     i = lineBufferPos+1;

    while (1) {
        switch (lineBuffer[i++]) {
        case '\n':
        case ':':
            return 1;

        case ' ':
        case '\t':
            break;

        default:
            return 0;
        }
    }
}

int lexDigits()
{
    /* read digits into the word buffer */
    /* returns last non-digit char read */

    char   c;

    /* read digits */
    while (1){
        /* get the next char */
        c = getChar();

        /* exit if not a digit */
        if (!isdigit(c)) {
            break;
        }

        /* add to buffer */
        word[wordPos++] = c;

    }

    /* return last (non-digit) char read */
    return c;

}

int lexHexDigits()
{
    /* read digits into the word buffer */
    /* returns last non-digit char read */

    char   c;

    /* read digits */
    while (1){
        /* get the next char */
        c = getChar();

        /* exit if not a digit */
        if (isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')) {
            /* add to buffer */
            word[wordPos++] = c;

        } else {
            break;
        }
    }

    /* return last (non-digit) char read */
    return c;

}


/* read special char */
int lexBackquotedChar()
{
    char c;

    c = getChar();
    switch (c) {
        case 'n':
            return '\n';

        case 'r':
            return '\r';

        case 't':
            return '\t';

        case '\'':
            return '\'';

        case '\"':
            return '\"';

        case '\\':
            return '\\';

        default:
            /* fatal */
            ePrintf( Syntax, "Unknown escape code: \\%c", c );
            break;
    }

    /* can't get here */
    return ' ';
}

/* read string into buffer */
void lexString()
{

//   char c;
    int c;

    /* clear buffer */
    wordPos = 0;

    while (1) {
        /* read a char */
        c = getChar();

        if (c=='\n' || c == EOF) {
            /* fatal */
            ePrintf( Syntax, "End of line reached before closing quote" );
        }

        /* if end of string, leave loop */
        if (c=='\"') {
            break;
        }

        /* special character */
        if (c == '\\') {
            c = lexBackquotedChar();
        }

        /* add to string */
        word[wordPos++] = c;
    }

    /* pad end */
    word[wordPos] = '\0';
}

/* isNonBreakingChar: true for char that breaks a token */
int isNonBreakingChar( char c )
{
    if (isalnum(c)) {
        return 1;
    }

    switch (c) {
    case '$':
    case '_':
        return 1;
    default:
        return 0;
    }
}

/* lexIdentifier: parse remainder of token as identifier */
void lexIdentifier( int c )
{
    int     i;

    while ( isNonBreakingChar(c) ){
        word[wordPos++] = c;
        c = getChar();
    }

    /* replace last char */
    ungetChar();

    /* terminate string */
    word[wordPos] = '\0';

    /* save token */
    strcpy( currtok, word );

    /* lower case */
    for ( i = 0; word[i] != '\0'; i++ ) {
        word[i] = tolower( word[i] );
    }

}

/* identifyWord: identify type, and set data value */
int identifyWord()
{
    Symbol  *s;

    /* in symbol table? */
    s = NULL;
    if (currentScope != NULL) {
        s = findSymbol( word, currentScope );
    }
    if (s==NULL) {
        s = findSymbol( word, NULL );
    }
    if (s==NULL) {
        /* copy to private buffer */
        yylval.strValue = eCopyString( word );
        return Undefined;
    }

    switch( s->symboltype ) {
    case SYM_KEYWORD:
        if (s->klass == End && nextTokenIsSep()) {
            /* end statement */
            return EndX;
        } else {
            /* datatype holds symbol value */
            return s->klass;
        }

    case SYM_BUILTIN:
        yylval.symbol = s;
        return BuiltinName;

    case SYM_CONSTANT:
        yylval.symbol = s;
        return ConstantName;

    case SYM_VARIABLE:
        yylval.symbol = s;
        return VariableName;

    case SYM_ARRAY:
        yylval.symbol = s;
        return ArrayName;

    case SYM_FUNCTION:
        yylval.symbol = s;
        return FunctionName;

    case SYM_SUB:
        yylval.symbol = s;
        return SubName;

    case SYM_FORWARD_SUB:
        yylval.symbol = s;
        return ForwardSubName;

    case SYM_FORWARD_FUNCTION:
        yylval.symbol = s;
        return ForwardFunctionName;

    case SYM_CLASS:
        yylval.symbol = s;
        return ClassName;

    default:
        ePrintf( Syntax, "Bad data type: %s", word );
    }

    /* can't get here */
    return 0;
}

int follows( int letter, int ifTrue, int ifFalse )
{
    char    nextchar;

    nextchar = getChar();
    if (nextchar == letter ) {
        /* add to current token */
        currtok[1] = letter;
        currtok[2] = '\0';

        return ifTrue;
    } else {
        ungetChar();
        return ifFalse;
    }
}


int yylex()
{
    int     c, nextchar;

    /* reset position of built word */
    wordPos = 0;
    word[wordPos] = 0;

    /* skip whitespace */
    while (1) {
        c = getChar();
        if (c != ' ' && c != '\t' ) {
                break;
        }
    }

    /* save as token */
    currtok[0] = c;
    currtok[1] = '\0';

    /* what are we parsing? */
    switch (c) {

    case '\'':
        /* basic-style comment */
        strcpy( currtok, "end-of-line");
        lineBufferPos = -1;
        return '\n';

    case '/':
        c = getChar();
        switch (c) {
        case '=':
            yylval.iValue = OpDiv;
            return IncrSelf;
        case '/':
            /* c++ style comment */
            strcpy( currtok, "end-of-line");
            lineBufferPos = -1;
            return '\n';
        default:
            ungetChar();
            return '/';
        }

     case '-':
        c = getChar();
        switch (c) {
        case '=':
	    yylval.iValue = OpSub;
            return IncrSelf;
        case '-':
            /* diector style comment */
            strcpy( currtok, "end-of-line");
            lineBufferPos = -1;
            return '\n';
        default:
            ungetChar();
            return '-';
        }

    case '\n':
        strcpy( currtok, "end-of-line");
        lineBufferPos = -1;
        return c;

    /* end of file */
    case EOF:
        strcpy( currtok, "end-of-file" );
        return 0;

#if defined(GP2X)
    /* end of file */
    case 255:
		/* ivanixcu: handle end-of-line on gp2x */
        strcpy( currtok, "end-of-file" );
        return 0;
#endif

    /* integer */
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':

        /* add to buffer */
        word[wordPos++] = c;

        /* hex number? */
        if (c=='0') {
            c = getChar();

            if (c == 'x' || c == 'X') {
                word[wordPos++] = c;
                c = lexHexDigits();

                /* replace last non-digit */
                ungetChar();

                /* terminate string */
                word[wordPos] = 0;

                /* convert to a hex number */
                sscanf( word, "%x", &yylval.iValue );
                return Integer;

            } else {
                ungetChar();
            }
        }


        /* read remaining digits */
        c = lexDigits();

        /* floating point? */
        if (c=='.') {

            /* add chars to buffer */
            word[wordPos++] = c;

            /* get remaining digits */
            c = lexDigits();

        }

        /* replace last non-digit */
        ungetChar();

        /* terminate string */
        word[wordPos] = '\0';

        /* save as current token */
        strcpy( currtok, word );

        /* convert string to number */
        sscanf( word, NUMBER_FLOAT_FORMAT, &(yylval.fValue) );
        return Float;

    /* float or method name */
    case '.':
        /* add to buffer */
        word[wordPos++] = c;

        /* read next char */
        c = getChar();

        /* floating point number? */
        if (isdigit(c)) {
            /* add to string */
            word[wordPos++] = c;

            /* read remaining digits */
            lexDigits();

            /* replace last char read */
            ungetChar();

            /* terminate string */
            word[wordPos] = 0;

            /* save as current token */
            strcpy( currtok, word );

            /* convert string to number */
            sscanf( word, NUMBER_FLOAT_FORMAT,&(yylval.fValue) );
            return Float;

        } else {
            /* method name? */
            if (isalnum(c)) {
                /* clear buffer */
                wordPos = 0;

                /* read method */
                lexIdentifier( c );

                /* copy to private buffer */
                yylval.strValue = eCopyString( word );
                return MethodName;

            } else {
                /* breaks word */
                ungetChar();
                return '.';
            }
        }

    /* string */
    case '\"':
        /* parse the string */
        lexString();

        /* copy to private buffer */
        yylval.strValue = eCopyString( word );

        /* save as current token */
        strcpy( currtok, word );
        return String;

    case '!':
        return follows('=', Ne, '!');

    case '<':
        nextchar = getChar();

        switch (nextchar) {
        case '>':
            strcpy( currtok, "<>" );
            return Ne;

        case '=':
            strcpy( currtok, "<=" );
            return Le;

        case '<':
            strcpy( currtok, "<<" );
            return Shl;

        default:
            ungetChar();
            return Lt;
        }

    case '>':
        nextchar = getChar();

        switch (nextchar) {
        case '=':
            strcpy( currtok, ">=" );
            return Ge;

        case '>':
            strcpy( currtok, ">>" );
            return Shr;

        default:
            ungetChar();
            return Gt;
        }


    /* division is handled elsewhere */
    /* subtraction is handled elsewhere */
    case '+':
    case '*':
    case '\\':
    case '%':
    case '&':

        switch (c){
        case '+':   yylval.iValue = OpAdd;
                    break;

        case '*':   yylval.iValue = OpMul;
                    break;

        /* /= is handled elsewhere, with // */

        case '\\': yylval.iValue = OpIDiv;
                    break;

        case '%':   yylval.iValue = OpMod;
                    break;

        case '&':   yylval.iValue = OpConcat;
                    break;

        default:    ePrintf( Syntax, "Lexer failed parsing %c", c );
                    break;

        }

        return follows('=', IncrSelf, c );

    case '=':
        return Eq;

    default:
        /* alpha? */
        if (isNonBreakingChar(c)) {
            /* identifier */
            lexIdentifier(c);
            return identifyWord();

        } else {
            /* seperator */
            return c;
        }
    }

}

void yyerror( char *s )
{
    errFlag = 1;
    s = NULL;
}

