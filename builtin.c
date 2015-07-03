/*
    Name:       builtin.c
    Purpose:    builtin routines for wxBasic modify for sdlBasic
    Author:     David Cuny    modify __vroby__
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

#pragma GCC diagnostic ignored "-Wunused-result"

void notYet( char *name )
{
    error_description="not implemented yet ";
    error_type=1;
    ePrintf( Runtime, "%s is not implemented yet", name );
}
//_______________________________________________________________________________________________________________________

/* basPrintStack: debugging wrapper of printStack */
void basPrintStack()
{
    printStack();
    pushNumber( 0 );
}

//_______________________________________________________________________________________________________________________

/* basConcat: concatenate two strings */
void basConcat()
{
    int     len1, len2;
    char    *string1, *string2, *buffer;

    string2 = popString();
    string1 = popString();

    len1 = strlen( string1 ),
    len2 = strlen( string2 );

    buffer = (char *)eMalloc( len1 + len2 + 1 );

    memcpy( buffer, string1, len1 );
    memcpy( buffer+len1, string2, len2 );
    buffer[len1+len2] = '\0';
    pushString( buffer );
    /*
    * ivanixcu: debug memleak
    */
    eFree(string1);
    eFree(string2);
}
//_______________________________________________________________________________________________________________________

/* basConvBas: returns representation from base to base */
void basConvBase()
{
    notYet("ConvBase");
    pushNumber(0);
}
//_______________________________________________________________________________________________________________________

void basIndexes()
{
    int     indexes;

    /* array is on stack */
    indexes = getArrayIndexes();
    popNumber();

    pushNumber(indexes);
}
//_______________________________________________________________________________________________________________________



//_________________________________________________________________________________________________________________________
//
// Run time
//_________________________________________________________________________________________________________________________
//_______________________________________________________________________________________________________________________

/* bas Arguments :return the arguments(n) or the number of arguments */
void basArgument()
{
    int     index;

    if (argCount==0){
	//copyStackItem( localstart );
	pushNumber(cmdArgc);
    }
    else{
	index = (int)popNumber();
	//copyStackItem( localstart+index );
	pushStringCopy( cmdArgv[index]);
    }
}
//_______________________________________________________________________________________________________________________


/* basArgc: return number of args in caller */
void basArgc()
{
    /* arg count is at localstart */
    //copyStackItem( localstart );
    pushNumber(cmdArgc);
}
//_______________________________________________________________________________________________________________________

/* basArgv: return arg onto stack */
void basArgv()
{
    int     index;
    index = (int)popNumber();
    pushStringCopy( cmdArgv[index]);
}
//_______________________________________________________________________________________________________________________

/* basCommand: returns requested arg from command line */
void basCommand()
{
    int     argNum;

    /* was an arg passed? */
    if (argCount == 0) {
        /* return count of args */
        pushNumber( cmdArgc );

    } else {

        /* get arg number */
        argNum = popNumber();
        if (argNum < 0 || argNum > cmdArgc) {
            /* out of range */
            pushStringCopy( "" );

        } else {
            /* return copy of arg */
            pushStringCopy( cmdArgv[ argNum-1 ] );
        }
    }
}
//_______________________________________________________________________________________________________________________

//setenv(varname,value): set a enviremont variable in currently os. if variable exist it will be overwrite
void basSetEnv()
{
    char * varname;
    char *value;
#if defined(WIN32)
    char *cmd;
#endif

    value=popString();
    varname=popString();
#if defined(WIN32)
    cmd=(char *)malloc(512);
    strcpy(cmd,"set ");
    strcat(cmd,varname);
    strcat(cmd,"=");
    strcat(cmd,value);
    cmd[strlen(cmd)]='\0';
    pushNumber(system(cmd));
#else
    pushNumber(setenv(varname,value,1));
#endif
}

//_______________________________________________________________________________________________________________________

//getenv(varname): return the value of enviremont variable in currently os
void basGetEnv()
{
    char *varname;
    varname=popString();
    pushStringCopy( getenv(varname) );
    eFree(varname);
}
//_______________________________________________________________________________________________________________________

/* basRun: run command on new thread */
void basRun()
{
    notYet("Run");
    pushNumber(0);
}
//_______________________________________________________________________________________________________________________

/* basShell: execute command, wait until finished */
void basShell()
{
    char    *string;
    string = popString();
    system(string);
    eFree(string);
    pushNumber(0);
}
//_______________________________________________________________________________________________________________________

/* basStop:block the code and start debug */
void basStop()
{
    debug=1;
    error_type=2;
    error_description="stop encountered";
    screendebug();
    pushNumber(0);
}
//_______________________________________________________________________________________________________________________
//
// Array
//_________________________________________________________________________________________________________________________

/* basLBound: returns lower bound of array */
void basLBound()
{
    int     index, range;

    index = popNumber();
    /* leave array pointer on stack */

    range = getArrayBound( index, 0 );

    /* pop array pointer */
    popNumber();

    pushNumber(range);
}
//_______________________________________________________________________________________________________________________

/* basQuickSort: sort an array */
void basQuickSort()
{
    notYet("QuickSort");
    pushNumber(0);
}
//_______________________________________________________________________________________________________________________

/* basUBound: upperbound of array */
void basUBound()
{
    int     index, range;

    index = popNumber();
    /* leave array pointer on stack */

    range = getArrayBound( index, 1 );

    /* pop array pointer */
    popNumber();

    pushNumber(range);
}
//_______________________________________________________________________________________________________________________
//
//Strings
//_________________________________________________________________________________________________________________________

/* basAsc: returns ascii value of first char in string */
void basAsc()
{
    char    *string;
    string = popString();
    pushNumber( asc(string));
    eFree( string );
}
//_______________________________________________________________________________________________________________________

/* basChr: return string corresponding to ascii key value */
void basChr()
{
	char    *buffer = (char *)eMalloc(sizeof(char)*2);
	buffer[0] = (char)popNumber();
	buffer[1] = '\0';
	pushString( buffer );
}
//_______________________________________________________________________________________________________________________

/* basFormat: returns formatted string with embedded args */
void basFormat()
{
    notYet("Format");
    pushNumber(0);
}
//_______________________________________________________________________________________________________________________

/* basInsert: insert source string to target at index */
void basInsert()
{
	char    *source, *target;
	int     i;

	i = (int)popNumber();
	target = popString();
	source = popString();


	pushString((char *)insert(source,target,i));
	eFree(source);
	eFree(target);
}
//_______________________________________________________________________________________________________________________

/* basInstr: returns position in source that target was found */
void basInstr()
{
    //int searchLen, findLen, i;
    int     start;
    char    *find, *search;

    find = popString();
    search = popString();
    if (argCount==3) {
        start = (int)popNumber()-1;
        if (start < 0) {
            start = 0;
        }

    } else {
        start = 0;
    }


    pushNumber(instr(start,find, search));

    /* ivanixcu: fix memleak */
    eFree(find);
    eFree(search);
}
//_______________________________________________________________________________________________________________________

/* basLCase: convert string to lower case */
void basLCase()
{
    char    *string;

    string = popString();
    pushString(lcase(string));

}
//_______________________________________________________________________________________________________________________

/* basLeft: returns leftmost chars in string */
void basLeft()
{

    int     pos;
    char    *string;
    char *dest;


    pos = (int)popNumber();
    string = popString();

    dest=left(string,pos);
    pushStringCopy(dest);
	
    eFree(string);	
    //eFree(dest);

}
//_______________________________________________________________________________________________________________________

/* basLen: return length of string */
void basLen()
{
    char    *string;
	
    string = popString();
    pushNumber(len(string));
}
//_______________________________________________________________________________________________________________________

/* basLTrim: returns string with left whitespace removed */
void basLTrim()
{
    char    *string;
    char *dest;

    string = popString();
	
    dest=ltrim(string);	
    pushStringCopy(dest);
	
    //eFree(dest);    
    eFree(string);    
	
}
//_______________________________________________________________________________________________________________________

/* basMid: returns string with chars 1..n from source */
void basMid()
{

    int     i,n,len;
    char    *string;
    char    *dest;
	

    n=0;
    /* get args */
    if (argCount==3)
	n = (int)popNumber();

    i = (int)popNumber();
    string = popString();

    len=strlen(string);
    
    if (argCount!=3)
	n=len+1-i;

    
    if ( i < 1 || len < 0 ||  i >len ) {
	    ePrintf( Runtime, "BASengine Error \n");
    }
    dest=mid(string, i, n);
    pushStringCopy(dest);
    
    eFree(dest);    
    eFree(string);
}
//_______________________________________________________________________________________________________________________

/* basReplace: replace string from source with replace starting at index */
void basReplace()
{

    int     i;
    char    *src, *rep;
    char *dest;

    rep = popString();
    src = popString();
    if (argCount == 3)
	i = (int)popNumber();
    else
	i = 0;
    dest=replace(src, rep, i);
    pushStringCopy(dest);
    
    //eFree(src);    
    //eFree(rep);    
    //eFree(dest);    

}
//_______________________________________________________________________________________________________________________

/* basReplaceSubStr: replace substring in source with withstring */
void basReplaceSubStr()
{
    int start;
    char *source, *replace, *with;
    char *dest;
	
    with = popString();
    replace = popString();
    source = popString();
    if (argCount==4)
	start=popNumber();
    else
	start=0;

    dest=replacesubstr(start, source, replace, with);
    pushStringCopy(dest);
    
    //eFree(source);    
    //eFree(replace);
    //eFree(with);        
    //eFree(dest);    
}
//_______________________________________________________________________________________________________________________

/* basReverse: reverse a string */
void basReverse()
{
    char    *string;
    char *dest;	

    string = popString();
    dest=reverse(string);
    pushStringCopy(dest);

    eFree(string);
    eFree(dest);	
}
//_______________________________________________________________________________________________________________________

/* basRight: returns rightmost chars in string */
void basRight()
{

    int     pos;
    char    *string;
    char    *dest;	

    pos = (int)popNumber();
    string = popString();
	
    dest=	right(string,pos);
    pushStringCopy(dest);
	
    eFree(string);
    eFree(dest);

}
//_______________________________________________________________________________________________________________________

/* basRInstr: reverse Instr function, search from end to start */
void basRInstr()
{

    int     start;
    char    *find, *search;

    find = popString();
    search = popString();

    /* optional starting position */
    if (argCount==3) {
        start = (int)popNumber()-1;
    } else {
	start=-1;
    }

    pushNumber(rinstr( search, find, start));

}
//_______________________________________________________________________________________________________________________

/* basRTrim: right trim string */
void basRTrim()
{
    char *string;
    char *dest;
	
    string = popString();
    dest = rtrim(string);	
    pushStringCopy(dest);
	
    eFree(string);
    //eFree(dest);
}
//_______________________________________________________________________________________________________________________

/* basSpace: return string with n spaces in it */
void basSpace()
{
    int     n;
    n = (int)popNumber();
    pushString(space(n));

}
//_______________________________________________________________________________________________________________________

/* basStr: return string representation of numeric expression */
void basStr()
{
    char    *string;
    string = popString();
    pushStringCopy( string );
    eFree(string);
}
//_______________________________________________________________________________________________________________________

/* basStrF: converts a floating point or number value to a string */
void basStrF()
{
    char    *string;
    string = popString();
    pushStringCopy( string );
    eFree(string);
}
//_______________________________________________________________________________________________________________________

/* basString: returns string m chars wide with n in it */
void basString()
{

    int     n;
    char    *_string;

    _string = popString();
    n = (int)popNumber();
    pushString(string( n, _string));

}
//_______________________________________________________________________________________________________________________

/* basTally:  returns number of occurances of matchstring */
void basTally()
{
    int     start;
    char    *src, *sub;

    /* get the args */
    sub = popString();
    src = popString();

    /* optional start */
    if (argCount==3) {
        start = popNumber();
	}
    else {
	start = 0;
    }
    pushNumber(tally( src, sub, start));

}
//_______________________________________________________________________________________________________________________

/* basTrim: returns string with left and right whitespace removed */
void basTrim()
{
      char *string;
      char *dest;

    string = popString();
	
    dest=trim( string);		
    pushStringCopy(dest);

    eFree(string);
}
//_______________________________________________________________________________________________________________________

/* basTypeOf:  returns string with datatype */
void basTypeOf()
{
    int         datatype;
    Variant     *v;
    v = getStackPointer( tos );
    datatype = v->datatype;
    dropTos();
    switch(datatype) {
    case DATA_NUMBER:
        pushStringCopy( "number" );
        break;

    case DATA_STRING:
        pushStringCopy( "string" );
        break;

    case DATA_OBJECT:
        pushStringCopy( "object" );
        break;

    default:
        pushStringCopy( "unknown" );
        break;
    }
}
//_______________________________________________________________________________________________________________________

/* basUCase: convert string to upper case */
void basUCase()
{
    char    *string;

    string = popString();
    pushString(ucase(string));

}
//_______________________________________________________________________________________________________________________

/* basVal: returns closest numeric representation of number */
void basVal()
{
    char    *string;
    string = popString();
    pushNumber( val(string) );
    eFree( string );
}
//_______________________________________________________________________________________________________________________
//
//Maths
//_________________________________________________________________________________________________________________________

/* basAbs: returns absolute value of number */
void basAbs()
{
    Number  n;
    n = popNumber();
    if (n < 0) {
        pushNumber( -n );
    } else {
        pushNumber( n );
    }
}
//_______________________________________________________________________________________________________________________

/* basACos: returns arccos of number */
void basACos()
{
    pushNumber( acos( popNumber() ) );
}
//_______________________________________________________________________________________________________________________

/* basASin: returns arcsin of number */
void basASin()
{
    pushNumber( asin( popNumber() ) );
}
//_______________________________________________________________________________________________________________________

/* basATan: returns arctan of number */
void basAtan2()
{
    pushNumber( atan2( popNumber(), popNumber() ) );
}
//_______________________________________________________________________________________________________________________

/* basAtan2: returns arctan of 2 numbers where the signs determine the quadrant of the result */
void basAtan() {
    pushNumber( atan( popNumber() ) );
}
//_______________________________________________________________________________________________________________________

/* basBin: returns binary representation of number */
void basBin()
{
    int i,l;
    char    *buffer ,*ret;

    buffer = (char *)eMalloc(1024);
    i = (int)popNumber();
    strcpy(buffer,"");

    if (i==0)strcat(buffer,"0");

    while(i>0){
	if ((i%2)==0)
	    strcat(buffer,"0");
	else
	    strcat(buffer,"1");
	i=i /2;
    }
    l=strlen(buffer);

    ret = (char *)eMalloc(l+1);
    for (i=0;i<l;i++)
	ret[i]=buffer[l-i-1];
    ret[l]='\0';
    eFree(buffer);
    pushString( ret );
}
//_______________________________________________________________________________________________________________________

/* basCos: returns cos of number */
void basCos()
{
    pushNumber( cos( popNumber() ) );
}
//_______________________________________________________________________________________________________________________

/* basExp: returns exponential function */
void basExp()
{
    pushNumber( exp( popNumber() ) );
}
//_______________________________________________________________________________________________________________________

/* basFix: truncate fractional number, rounding down towards zero */
void basFix()
{
    pushNumber( floor( popNumber() ) );
}
//_______________________________________________________________________________________________________________________

/* basFrac: return fractional portion of number */
void basFrac()
{
    Number  n;
    n = popNumber();
    n -= floor(n);
    pushNumber(n);
}
//_______________________________________________________________________________________________________________________

/* basHex: returns hexidecimal representation of number */
void basHex()
{
    int i;
    char    *buffer = (char *)eMalloc(16);
    i = (int)popNumber();
    sprintf( buffer, "%x", i);
    pushString( buffer );
}
//_______________________________________________________________________________________________________________________

/* basInt: convert to 32 bit integer, truncating decimals */
void basInt()
{
    pushNumber( (int)popNumber() );
}
//_______________________________________________________________________________________________________________________

/* basLog: returns natural log of expression */
void basLog()
{
    pushNumber( log( popNumber() ) );
}
//_______________________________________________________________________________________________________________________

/* basRandomize: reseed the random number generator */
void basRandomize()
{
    int seed;
    if (argCount==1) {
        seed = (int)popNumber();
    } else {
        seed = time(NULL);
    }
    srand( seed );
    pushNumber(0);
}
//_______________________________________________________________________________________________________________________

/* basRnd: return an random number */
void basRnd()
{
    int upper;

    if (argCount==1)
        upper =popNumber();
    else
	upper=-1;

    pushNumber( (Number)rnd(upper));

}
//________________________________________________cd dev*_______________________________________________________________________

/* basRound: round to nearest integer */
void basRound()
{
    Number n1, n2;
    n1 = popNumber();
    n2 = floor(n1);
    if (n2 == 0) {
        /* leave it alone */

    } else if (n2 > 0) {
        if ((n1 - n2) > 0.5) {
            n2++;
        }
    } else {
        if (-(n2 - n1) > 0.5) {
            n2++;
        }
    }
    pushNumber( n2 );
}
//_______________________________________________________________________________________________________________________

/* basSgn: returns sign of numeric expression */
void basSgn()
{
    Number  n;
    n = popNumber();
    if (n < 0) {
        pushNumber(-1);
    } else if (n > 0) {
        pushNumber(1);
    } else {
        pushNumber(0);
    }
}
//_______________________________________________________________________________________________________________________

/* basSin: returns sine of given angle in radians */
void basSin()
{
    pushNumber( sin( popNumber() ) );
}
//_______________________________________________________________________________________________________________________

/* basSqr: return square root - make sure it's non-negative */
void basSqr()
{
    pushNumber( sqrt( popNumber() ) );
}
//_______________________________________________________________________________________________________________________

/* basTan: return tanget of given angle in radians */
void basTan()
{
    pushNumber( tan( popNumber() ) );
}
//_______________________________________________________________________________________________________________________

/* basMin: return min number of the operands */
void basMin()
{
    double a,b;
    a=popNumber();
    b=popNumber();
    if (b<a)a=b;
    pushNumber(a);
}
//_______________________________________________________________________________________________________________________

/* basMax: return max number of the operands */
void basMax()
{
    double a,b;
    a=popNumber();
    b=popNumber();
    if (b>a)a=b;
    pushNumber(a);
}
//_______________________________________________________________________________________________________________________

/* basBitwiseAnd: return the logic and of the operands */
void basBitwiseAnd()
{
        int a,b;
    a=popNumber();
    b=popNumber();
    pushNumber(a & b);
}
//_______________________________________________________________________________________________________________________

/* basBitwiseOr: return the logic or of the operands */
void basBitwiseOr()
{
        int a,b;
    a=popNumber();
    b=popNumber();
    pushNumber(a | b);
}
//_______________________________________________________________________________________________________________________

/* basBitwiseXor: return the logic xor of the operands */
void basBitwiseXor()
{
    int a,b;
    a=popNumber();
    b=popNumber();
    pushNumber(a ^ b);
}
//_______________________________________________________________________________________________________________________
//
//Files
//_________________________________________________________________________________________________________________________

/* basEof: returns nonzero if Eof */
void basEof()
{
    pushNumber( (Number)fileEof( (int)popNumber() ) );
}
//_______________________________________________________________________________________________________________________

/* basFileExists: returns true if the file exists */
void basFileExists()
{
    char    *fname;

    fname = popString();
    pushNumber(FileExists(fname));
    eFree(fname);
}
//_______________________________________________________________________________________________________________________

/* basFileCopy : copy a file */
void basFileCopy()
{
    char *source;
    char *dest;
    int ret;

    dest=popString();
    source=popString();
    ret=filecopy(source,dest);
    if (ret==-1){
	error_description="file copy error";
	error_type=1;
	ePrintf( Runtime, "file Error \n");
    }
    eFree( dest );
    eFree( source );
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

/* basFileMove:move a file */
void basFileMove()
{
    char *source;
    char *dest;
    int ret;

    dest=popString();
    source=popString();
    ret=filemove(source,dest);
    if (ret==-1){
	error_description="file move error";
	error_type=1;
	ePrintf( Runtime, "file Error \n");
    }
    eFree( dest );
    eFree( source );
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

/* basFileRename: move a file */
void basFileRename()
{
    char *source;
    char *dest;
    int ret;

    dest=popString();
    source=popString();
    ret=filerename(source,dest);
    if (ret==-1){
	error_description="file rename error";
	error_type=1;
	ePrintf( Runtime, "file Error \n");
    }
    eFree( dest );
    eFree( source );
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

/* basFreeFile: return the handle of the next free file */
void basFreeFile()
{
    pushNumber(fileFree());
}
//_______________________________________________________________________________________________________________________

/* basKill: delete filename */
void basKill()
{
    char    *name = popString();
    remove( name );
    eFree(name);
    pushNumber(0);
}
//_______________________________________________________________________________________________________________________

/* basLoc: returns position in file */
void basLoc()
{
    pushNumber( filePosition( popNumber() ) );
}
//_______________________________________________________________________________________________________________________

/* basLof: returns length of file */
void basLof()
{
    pushNumber( fileSize( popNumber() ) );
}
//_______________________________________________________________________________________________________________________

/* basReadByte: return a byte from the file */
void basReadByte()
{
    pushNumber( (Number)fileReadByte( (char)popNumber() ) );
}
//_______________________________________________________________________________________________________________________

/* basSeek: seek file position/return current file position */
void basSeek()
{
    int     file, pos;

    /* which version? */
    if (argCount==2) {
        /* seek to position */
        pos = popNumber();
        file = popNumber();
        pushNumber( fileSeek( file, pos ));

    } else {
        /* return position in file */
        file = popNumber();
        pushNumber( filePosition( file ) );
    }
}
//_______________________________________________________________________________________________________________________


/* basWriteByte: return a byte from the file */
void basWriteByte()
{
    char    c;
    int     fileNum;

    c = popNumber();
    fileNum = popNumber();
    fileWriteByte( fileNum, c );
    pushNumber( 0 );
}

//_______________________________________________________________________________________________________________________
//
//Dirs
//_________________________________________________________________________________________________________________________

/* basChDir: change directory */
void basChDir()
{
    char    *name;
    name = popString();
    pushNumber(chdir(name));
     eFree(name);
}
//_______________________________________________________________________________________________________________________

/* basDir: returns current path */
void basDir()
{
	pushStringCopy(dir());
}
//_______________________________________________________________________________________________________________________

/* basDirExists: returns true if directory exists */
void basDirExists()
{
	char *path;
	path=popString();
	pushNumber(direxists(path));
	eFree(path);
}
//_______________________________________________________________________________________________________________________

/* basDirFirst: returns first entry in path dir */
void basDirFirst()
{
	char *path;
	path = popString();
	pushStringCopy(dirfirst(path));
	eFree(path);
}
//_______________________________________________________________________________________________________________________

/* basDirNext: returns next entry in  path dir */
void basDirNext()
{
	pushStringCopy(dirnext());
}
//_______________________________________________________________________________________________________________________

/* basMkDir: create a new directory */
#if !defined(WIN32) & !defined(__amigaos4__)
    int mkdir(char *name); //used for forcing the warning
    int chmod(char *name,int p); //used for forcing the warning
#endif

void basMkDir()
{
    char    *name;
    name = popString();
#ifdef __amigaos4__
    pushNumber(mkdir(name,0777));
#else
   mkdir(name);
#ifndef WIN32
    chmod(name,0777);
#endif
    pushNumber(0);
#endif
}
//_______________________________________________________________________________________________________________________

/* basRmDir: remove directory */
void basRmDir()
{
    char    *name;
    name = popString();
    pushNumber(rmdir(name));
    eFree(name);
}
//_______________________________________________________________________________________________________________________

//Data function support
//_________________________________________________________________________________________________________________________

/* basData: load in array the data */
void basData()
{
    int i;
    char *datavalue[255];

    for( i=argCount-1;i>=0;i--){
	datavalue[i]=popString();
    }

    for( i=0;i<argCount;i++){
	loaddata(datavalue[i]);
	/* ivanixcu: fix memleak */
        eFree(datavalue[i]);
    }


    pushNumber(argCount);
}
//_______________________________________________________________________________________________________________________

/* basRead: return the data stored */
void basRead()
{
    if (argCount==1){
	datapointer=popNumber();
	if (datapointer>dataenter)datapointer=-1;
	if (datapointer<0){
	    error_description="read data error";
	    error_type=1;
	    ePrintf( Runtime, "%d it's out of range\n", datapointer );
	}
	pushNumber(datapointer);
    }
    else{
	if (datapointer>=dataenter){
	    error_description="read data error";
	    error_type=1;
	    ePrintf( Runtime, "%d it's out of range\n", datapointer );
}
	pushString(readdata());
    }
}
//_______________________________________________________________________________________________________________________

//Date and time
//_________________________________________________________________________________________________________________________

/* basDate: returns date in MM-DD-YYYY format */
void basDate()
{
    time_t      t;
    struct tm   *tmp;
    char        *buffer = (char *)eMalloc(11);

    /* get time */
    t = time(NULL);
    tmp = localtime(&t);

    sprintf( buffer, "%02d-%02d-%04d",
        tmp->tm_mon+1, tmp->tm_mday, tmp->tm_year+1900 );

    pushString( buffer );
}
//_______________________________________________________________________________________________________________________

/* basTicks: returns current timer value */
void basTicks()
{
#ifdef UNIX
    //fixed using mandel demo
    pushNumber( clock()/826 );
#else
    pushNumber( clock() );
#endif
}
//_______________________________________________________________________________________________________________________

/* basTime: return time in HH:MM:SS format */
void basTime()
{
    time_t      t;
    struct tm   *tmp;
    char        *buffer = (char *)eMalloc(9);

    /* get time */
    t = time(NULL);
    tmp = localtime(&t);

    sprintf( buffer, "%02d:%02d:%02d",
        tmp->tm_hour, tmp->tm_min, tmp->tm_sec );

    pushString( buffer );
}
//_______________________________________________________________________________________________________________________

#ifdef MEMORYBANK_SUPPORT
#include "builtin/memorybank.c"
#endif

#ifdef SDLENGINE_SUPPORT
#include "builtin/sdlengine.c"
#endif

#ifdef CD_SUPPORT
#include "builtin/cd.c"
#endif

#ifdef VIDEOMPEG_SUPPORT
#include "builtin/videompeg.c"
#endif

#ifdef SOCKET_SUPPORT
#include "builtin/socket.c"
#endif

#ifdef SQLITE_SUPPORT
#include "builtin/sqlite.c"
#endif

/*--- end ---------------------------------------------------------------*/

/* addBuiltin: add a builtin to the dictionary */
void addBuiltin( char *name, void (*routine)(void), int args, int optargs )
{
    Symbol  *s;
    s = findSymbol( name, NULL );
    if (s==NULL) {
        s = addSymbol( name, NULL, SYM_BUILTIN );
        s->builtin = routine;
        s->args = args;
        s->optargs = optargs;

    } else {
        ePrintf( Runtime, "builtin %s is already declared as a %s",
            s->name, symbolName[s->symboltype] );
    }

}

/* initBuiltins: install all the builtins */
void initBuiltins()
{
    int i;

    for (i = 0; builtin[i].name != NULL; i++) {
        addBuiltin( builtin[i].name,
                    builtin[i].routine,
                    builtin[i].args,
                    builtin[i].optargs );
    }
}

