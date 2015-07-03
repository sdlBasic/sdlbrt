/*
    Name:       error.c
    Purpose:    error support routines
    Author:     David Cuny and modify for sdlBasic  __vroby__
                Partially derived from Brian Kernighan and Rob Pike
                The Practice of Programming
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL

*/
#pragma GCC diagnostic ignored "-Wunused-result"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#pragma GCC diagnostic ignored "-Wformat-security"

/* which version to use? */
#ifdef __DEBUG_MEMORY__
    #define eAddMemLink(a,n)        eAddMemLinkDebug(a,n)
    #define eRemoveMemLink(a)       eRemoveMemLinkDebug(a)
    #define eMemTest(s,a)           eMemTestDebug(s,a)
    #define eFree(a)                eFreeDebug(a)
#else
    #define eAddMemLink(a,n)
    #define eRemoveMemLink(a)
    #define eMemTest(s,a)
    #define eFree(a)                free(a)
#endif

MemLink *lastMemLink = NULL;




/* eShutdown: close the application gracefully */
void eShutdown( int errorlevel )
{
    /* close any open files here... */
    exit(errorlevel);
}

/* ePrintf: print an error message and exit */
void ePrintf( int errType, char *fmt, ... )
{
    char        buffer[512], message[512];
    va_list     args;
    FILE        *errFile;
    SourceCode  *source = NULL;

#ifndef __WXWIN__
    fflush(stdout);
    fprintf(stderr, "\n" );
#endif

    if (error_type==0)
	error_description=(char *)eMalloc(512);

    switch (errType) {
    case Init:
        sprintf( message, "Initialization error\n" );
        break;

    case Syntax:
        source = eFindSource( parseLineId );
        if (source == NULL) {
            sprintf( message, "Syntax error, source code lookup corrupted\n" );
        } else {
	    sprintf( message, "File \"%s\" , line %d\nSyntax error: ", includeList[source->fileNum], source->lineNum );
        }
        break;

    case Runtime:
        source = eFindSource( runLineId );
        if (source == NULL) {
            sprintf( message, "Syntax error, source code lookup corrupted\n" );
        } else {
            sprintf( message, "File \"%s\" , line %d\nRuntime error: ", includeList[source->fileNum], source->lineNum );
        }
        break;

    default:
        sprintf( message, "Unknown error type\n" );

    }

    va_start(args, fmt);
    vsprintf( buffer, fmt, args );
    va_end(args);
    strcat( message, buffer );
    if (error_type==0)
	strcpy(error_description,buffer);

    if (fmt[0] != '\0' && fmt[strlen(fmt)-1] == ':') {
        sprintf( message, "\n%s", strerror(errno));
        strcat( buffer, message );
    }
    strcat( buffer, "\n");


    /* show the line */
    if (errType != Init) {
        if (source == NULL) {
            strcat( message, "\n<<Can't Find Source Line>>" );

        } else {
            sprintf( buffer, "\n%s", source->text);
            strcat( message, buffer );
        }
    }

    fprintf( stderr, "%s", message );
    //printf( message );

    /* open the error file */
    if (error_type!=2)
	errFile = fopen( "sdlBasic.err", "w" );
    else
	errFile =NULL;

    if (errFile != NULL) {
        fprintf( errFile, "%s", message );
        fclose( errFile );
    }

    debug=1;
    if (error_type!=2 && errType!=2 )
	error_type=errType;
    if (errType!=Init) { 
			screendebug(); 
	 }
    //eShutdown(2); /* conventional for failed execution */
}

/* eConsole: cross-platform version of printf */
void eConsole( char *fmt, ... )
{
    char    *buffer;
    va_list args;
    buffer= (char *)malloc(512);

    va_start(args, fmt);
    vsprintf( buffer, fmt, args );
    va_end(args);


    fprintf( stdout, "%s", buffer );

    free(buffer);
}




/* eAddMemLinkDebug: add memory chunk to tracking list */
void eAddMemLinkDebug( void *p, int n )
{
    MemLink     *link;

    /* malloc the link */
    link = (MemLink *)malloc(sizeof(MemLink));
    if (link == NULL) {
        ePrintf( Runtime, "eMalloc: malloc of MemLink failed:" );
    }

    /* set values */
    link->start = (intptr_t)p;
    link->end = link->start+(n-1);
    link->next = lastMemLink;
    lastMemLink = link;

}

/* eRemoveMemLink: remove memory chunk from tracking list */
void eRemoveMemLinkDebug( void *address )
{
    MemLink     *link;
    MemLink     *prev;

    if (address == NULL) {
        return;
    }

    prev = NULL;
    for ( link = lastMemLink; link != NULL; link = link->next ) {
        if (link->start == (intptr_t)address) {

            if (prev == NULL) {
                lastMemLink = link->next;
            } else {
                prev->next = link->next;
            }
            return;
        }
        prev = link;
    }
    ePrintf( Runtime, "eRemoveMemLink: memory address %p not in list", address );
}

/* lookup: sequential search through MemLink list */
MemLink *lookupMemLink( void *p )
{
    MemLink *link = lastMemLink;

    for ( ; link != NULL; link = link->next ) {
        if ((intptr_t)p >= link->start && (intptr_t)p <= link->end) {
            return link;
        }
    }
    return NULL; /* no match */
}

/* eMemTest: ensure that the memory was allocated */
void eMemTestDebug( char *message, void *address )
{
    if (address != NULL) {
        if (lookupMemLink(address) == NULL) {
            ePrintf( Runtime, "eMemTest: %s: address %p not allocated",
                message, address );
        }
    }
}

/* freeAll: free all the elements in list */
void freeMemLinksDebug()
{
    MemLink *link = lastMemLink;
    MemLink *next;

    for ( ; link != NULL; link = next) {
        next = link->next;
        free( (void*)(link->start) );     /* the chunk */
        free( link );                   /* the link */
    }
}

/* eCopyString: copy a string, report if error */
char *eCopyString(char *s)
{
    char    *t;

    t = (char *)eMalloc(strlen(s)+1);
    strcpy(t, s);
    return t;
}

/* expected: print error and die */
void expected( char *expect )
{
    ePrintf( Syntax, "Parse error: expected %s, but got %s", expect, currtok );
}

/* eMalloc: malloc and report if error */
void *eMalloc(size_t size)
{
    void        *p;

    /* malloc the chunk */
    p = (void *)malloc(size);
    if (p == NULL) {
        ePrintf( Runtime, "eMalloc: malloc of %u bytes failed:", size );
    }
    eAddMemLink( p, size );
    return p;

}

/* eRealloc: realloc and report if error */
void *eRealloc( void *theOld, size_t size)
{
    void        *theNew;

    /* realloc the chunk */
    theNew = (void *)realloc(theOld,size);
    if (theNew == (void *)NULL) {
        ePrintf( Runtime, "eRealloc: realloc of %u bytes failed:", size );
    }

#ifdef __DEBUG_MEMORY__
    if (theNew != theOld) {
        eRemoveMemLink(theOld);
        eAddMemLink(theNew,size);
    }
#endif

    return theNew;

}

/* eFreeDebug: free chunk of memory */
void eFreeDebug( void *address )
{
    if (address != NULL) {
        eRemoveMemLink( address );
        free( address );
    }
}

/* sdlBasic special screen for step tracing and inspect code */
void screendebug()
{

    char *curline;
    char *inputvar;
    char *binputvar;
    char *retvar;
    char *indexvar;
    int i,a,ba,oldpaper,oldpen,oldscreen,oldautoback;
    SourceCode *source=NULL;
    Symbol *s;
    Array *arr;


  	 while(stopkey()!=0);

    oldautoback=autoback(-1);
    oldscreen=screen(-1);
    oldpaper=paper(-1);
    oldpen=pen(-1);
    paper(0);
    pen(0xffffff);
    autoback(0);
    screenopen(8,displaywidth(),100,0,displayheight()-110,displaywidth(),100,0);
    cls();

    if (error_type !=2){
	prints("");
	paper(0xff0000);
	pen(0xffffff);
	prints(error_description);
    }
    paper(0);
    pen(0xffffff);
    prints("");

    for(i=(0-2);i<1; i++){
	if (error_type==Runtime)
	    source = eFindSource( runLineId + i );
	else
	    source = eFindSource( parseLineId + i );

	if (source == NULL) {
	    prints(" ");
	}
	else{
	    if (i==0) pen(0xff0000);
	    else pen(0xffffff);
	    curline=(char *)eMalloc(1024);
	    sprintf(curline,"%s ",source->text);
	    curline[strlen(source->text)-1]=0;
	    prints(curline);
	    free(curline);
    	    pen(0xffffff);

	}
    }

    locate(0,0);
    paper(0xffffff);
    pen(0);
    #if defined(GP2X)
    prints("start Run|select Step|vol +- Exit");
    #else
    prints("F5 Run|F6 Step|F4 Watch|Ctrl+c Exit");
    #endif
    paper(0);
    pen(0xffffff);

    screenswap();
    screenalpha(8,192);
    autoback(25);

    //F5 / START
    #if defined(GP2X)
    while(bjoy(0) != 0x00100){
    #else
    while(key(286)==0 ){
    #endif
	if (stopkey()==-1){
	    terminate();
	    exit(2);
	}
	//F6
	#if defined(GP2X)
	if(bjoy(0) == 0x00200)break;
	#else
	if (key(287))break;
	#endif

	//F4
	if (key(285)){
	    char stackstring[10][1024];
	    inputvar=(char *)eMalloc(1024);
	    binputvar=(char *)eMalloc(1024);
	    retvar=(char *)eMalloc(1024);
	    indexvar=(char *)eMalloc(1024);


	    screenalpha(8,255);
	    cls();
	    locate(0,0);
	    paper(0xffffff);
	    pen(0);
	    prints("F5 Run|F6 Step|F4 Watch|Ctrl+c Exit");
	    paper(0);
	    pen(0xffffff);
	    screenswap();

	    strcpy(inputvar,"");
	    inputS(">",inputvar);

	    i=0;
	    while(i<strlen(inputvar) && inputvar[i]!='[')i++;
	    strncpy(binputvar,&inputvar[i],strlen(inputvar)-1);
	    inputvar[i]='\0';

	    s=NULL;

	    s=findSymbol(inputvar,currentScope);

	    if (s==NULL && currentScope != NULL ){
		s=findSymbol(inputvar,NULL);
	    }

	    if (s!=NULL){
		if (s->symboltype==SYM_ARRAY){
		    arr=NULL;
		    arr=getArray(s);
		    if (arr->isDynamic!=0){
			fprints("dinamic array:");
			i=0;
			if (binputvar[0]=='['){
			    a=0;
			    do{
				a++;
				ba=a;
				while(a<strlen(binputvar) && binputvar[a]!=',' && binputvar[a]!=']')a++;
				if( binputvar[ba]=='\"')ba++;
				if(a<strlen(binputvar) && (a-ba)>0 ) {
				    strcpy(indexvar,"");
				    if ( binputvar[a-1]=='\"'){
					strncpy(indexvar,&binputvar[ba],a-ba-1);
					indexvar[a-ba-1]='\0';
				    }
				    else{
					strncpy(indexvar,&binputvar[ba],a-ba);
					indexvar[a-ba]='\0';
				    }
				    printf("indexvar:%s - a:%d - ba:%d - i:%d -len:%zd   \n",indexvar,a,ba,i,strlen(binputvar));
				    strcpy(stackstring[i],indexvar);
				}
				i++;
			    }while(a<strlen(binputvar));
			}
			else{
			    do{
				strcpy(indexvar,"");
				inputS(":select element of array >",indexvar);
				if (strlen(indexvar)!=0)
				    strcpy(stackstring[i],indexvar);
				i++;
			    }while(strlen(indexvar)!=0);
			}
			for(a=i ;a>=0;a--)
			    pushString(stackstring[a]);

			i--;

			if (i>0){
			    pushNumber(i);
			    getArrayElement(s);
			    retvar=popString();
			}
			else{
			    retvar="invalid";
			}
			prints("");
		    }
		    else{
			fprints("static array:");
			sprintf(retvar,"indexes %d, ",arr->indexes);
			fprints(retvar);
			sprintf(retvar,"elements %d ",arr->elements);
			prints(retvar);
			if (binputvar[0]=='['){
			    a=0;
			    for (i=0;i<arr->indexes;i++){
				a++;
				ba=a;
				while(a<strlen(binputvar) && binputvar[a]!=',' && binputvar[a]!=']')a++;
				strcpy(indexvar,"");
				strncpy(indexvar,&binputvar[ba],a-ba);
				indexvar[a-ba]='\0';
				strcpy(stackstring[i],indexvar);
				//pushNumber(atof(indexvar));
			    }
			}
			else{
			    for (i=0;i<arr->indexes;i++){
				strcpy(indexvar,"");
				inputS(":select element of array >",indexvar);
				strcpy(stackstring[i],indexvar);
				//pushNumber(atof(indexvar));
			    }
			}
			for(a=i ;a>=0;a--)
			    pushNumber(atof(stackstring[a]));

			pushNumber(arr->indexes);
			getArrayElement(s);
			retvar=popString();
			prints("");
		    }
		}
		else{
		    getVar(s);
		    retvar=popString();
		}
	    }
	    else{
		retvar=(char *)eMalloc(32);
		strcpy(retvar,"not found \0");
	    }

	    if (currentScope!=NULL){
		if (s!=NULL){
		    fprints(symbolName[s->symboltype]);
		    fprints(" ");
		}
		fprints(currentScope->name);
		fprints(".");
	    }
	    fprints(inputvar);
	    fprints(":");
	    prints(retvar);

	    locate(0,0);
	    paper(0xffffff);
	    pen(0);
	    prints("F5 Run|F6 Step|F4 Watch|Ctrl+c Exit");
	    paper(0);
	    pen(0xffffff);
	    eFree(inputvar);
	    eFree(retvar);
	    eFree(indexvar);
	}

	screenalpha(8,192);
	screenswap();
    }
    //F5
    #if defined(GP2X)
    if(bjoy(0) == 0x00100)debug=0; // step mode disabled
    #else
    if (key(286))debug=0; // step mode disabled
    #endif

    //wait release of key to continue;
    while(key(286)!=0 || key(287)!=0 );

    screenclose(8);
    paper(oldpaper);
    pen(oldpen);
    screen(oldscreen);
    screenswap();
    autoback(oldautoback);

}
