/*
    Name:       string.c
    Purpose:    string operation rutines for sdlBasic
    Author:     Viola Roberto __vroby__
    Copyright:  (c) 2003 Viola Roberto <__vroby__@libero.it>
    Licence:    LGPL
*/
//_______________________________________________________________________________________________________________________

//header

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
//#include "strings.h"
#include "BASengine.h"
//_______________________________________________________________________________________________________________________

/* asc: returns ascii value of first char in string */
int asc(char *string)
{
    return(unsigned char)string[0];
}
//_______________________________________________________________________________________________________________________

/* chr: return string corresponding to ascii key value */
char *chr(int v)
{
    char    *buffer = (char *)malloc(sizeof(char)*2);
    buffer[0] = (char)v;
    buffer[1] = '\0';
    return buffer;
}
//_______________________________________________________________________________________________________________________

/* format: returns formatted string with embedded args */
void format()
{
}
//_______________________________________________________________________________________________________________________
/* insert: insert source string to target at index */
char *insert(char *source, char *target,int position)
{
    char    *dest;
    dest = (char *) malloc(strlen(source)+strlen(target)+1);

	//strcpy(dest,"");
	strncpy(dest,source,position);
	strcpy(&dest[position],target);
	strcat(dest,source+position);
	return dest;
}
//_______________________________________________________________________________________________________________________

/* instr: returns position in source that target was found */
int instr(int start,char *find, char *search)
{
    int     searchLen, findLen, i;

    if (start < 0) {
	start = 0;
    }

    searchLen = strlen( search );
    findLen = strlen( find );

    /* searching for empty string? */
    if (searchLen == 0 || findLen == 0) {
        return 0;
    }

    start = (int)floor( start );
    for ( i = start; i < searchLen; i++ ) {
        if (strncmp( search+i, find, findLen ) == 0) {
            return( i+1 );
        }
    }

    /* not found */
    return 0 ;
}
//_______________________________________________________________________________________________________________________

/* lcase: convert string to lower case */
char *lcase(char *string)
{
    int     len, i;

    len = strlen( string );
    for ( i = 0; i<len; i++){
        string[i] = (char)tolower( (int)string[i] );
    }
    return string;
}
//_______________________________________________________________________________________________________________________

/* left: returns leftmost chars in string */
char *left(char *string,int pos)
{
    int     len, newLen;
    char    *left;

    len = strlen(string);

    if (pos > len-1) {
        return string;
    }

    if (pos < 1 || len <1) {
        return "";
    }

    newLen = (pos);
    left = (char *) malloc(newLen+1);
    for (pos=newLen;pos>0;pos--)left[pos]='\0';
    strncpy(left,string,newLen);
    left[newLen] = '\0';
    return left;
}
//_______________________________________________________________________________________________________________________

/* basLen: return length of string */
int len(char *string)
{
    return (strlen( string ) );
}
//_______________________________________________________________________________________________________________________

/* ltrim: returns string with left whitespace removed */
char *ltrim(char *string)
{
    char *trimmed;

    trimmed = string;
    while ( trimmed[0] != '\0' ) {
        if (!isspace(trimmed[0])) {
            break;
        }
        trimmed++;
    }
    // debug al limite: da testare
    return( trimmed );
}
//_______________________________________________________________________________________________________________________

/* mid: returns string with chars 1..n from source */
char *mid(char *string,int i,int n)
{
    int     j,len;
    char    *buffer;
	
    if (n<=0)
	n=strlen(string)+1-i;

    /* early outs */
    len = strlen( string ) - i;
    if ( i < 1 || len < 0 ) {
	buffer = (char *)malloc(2);    
	buffer[0] = '\0';
        return buffer;
    }


    buffer = (char *)malloc(len+2);
    for ( j = 0; j < n; j++ ) {
        if (string[i+j-1] == '\0' ) {
            break;
        }
        buffer[j] = string[i+j-1];
    }
    buffer[j] = '\0';
    return buffer;
}
//_______________________________________________________________________________________________________________________

/* replace: replace string from source with replace starting at index */
char *replace(char *src,char *rep, int i)
{
    int        a;
    char    *dest;

    if (i<0)i = 0;

    dest=(char *) malloc(strlen(src)+1);
    strcpy(dest,src);
    for(a=0;a<strlen(rep);a++){
	if ((a+i)>=strlen(dest))break;
	dest[i+a]=rep[a];
    }


    return(dest);
}
//_______________________________________________________________________________________________________________________

/* replacesubstr: replace substring in source with withstring */
char *replacesubstr(int start, char *source, char *replace, char *with)
{
    unsigned int i;
    char    *dest;
    if (start<0)
	start=0;

    i=start;
    while (i<strlen(source)){
		if (strncmp(source+i,replace,strlen(replace))==0){
			dest = (char *) malloc( strlen(source)+ strlen(with)+1 );
			strcpy(dest,"");
			strncpy(dest,source,i);
			dest[i] = '\0';
			strcat(dest,with);
			strcat(dest,source+i+strlen(replace));
			source = (char *) malloc(strlen(dest)+1);
			strcpy(source,dest);
			i+=strlen(with);
		}
		i++;
	}
    return(source);
}
//_______________________________________________________________________________________________________________________

/* reverse: reverse a string */
char *reverse(char *string)
{
    int     len, i, j;
    char    *buffer;

    len = strlen( string );

    buffer = (char *)malloc(len+1);
    j = len-1;
    for( i = 0; i < len; i++ ) {
        buffer[j--] = string[i];
    }
    buffer[len] = '\0';

    return(buffer);
}
//_______________________________________________________________________________________________________________________

/* right: returns rightmost chars in string */
char *right(char *string,int pos)
{
    int     len, newlen;
    char    *right;

    len = strlen(string);

    if (pos >= len) {
        return( string );
    }

    if (pos < 1) {
        return( "" );
    }

    newlen = pos+1;
    right = (char *)malloc((newlen+1));
    memcpy(right,string+(len-pos),newlen);
    right[newlen]=0;
    return( right );
}
//_______________________________________________________________________________________________________________________

/* rinstr: reverse Instr function, search from end to start */
int rinstr(char *search,char *find,int start)
{
    int      searchLen, findLen, i;

    findLen = strlen( find );
    searchLen = strlen( search );

    if (start<=0)
    start = searchLen-1;

    /* searching for empty string? */
    if (searchLen == 0 || findLen == 0) {
        return( 0 );
    }


    /* search */
    for ( i = start; i >= 0; i-- ) {
        if (strncmp( search+i, find, findLen ) == 0) {
            return( i+1 );
        }
    }

    /* not found */
    return( 0 );
}
//_______________________________________________________________________________________________________________________

/* rtrim: right trim string */
char *rtrim(char *string)
{
    int     len, i;
    len = strlen(string);
    for ( i = len-1; i > -1; i-- ) {
        if (!isspace(string[i])) {
            string[i+1] = '\0';
            return( string );
        }
    }
    string[0] = '\0';
    return(string );
}
//_______________________________________________________________________________________________________________________

/* space: return string with n spaces in it */
char *space(int n)
{
    char    *string;
/*
    if (n<0) 
    {
        n = 0;
    }
*/
    if (n<1) 
    {
        n = 1;
    }
    string = (char *)malloc((unsigned int)n+1);
    memset(string,' ',n);
    string[n] = '\0';
    return(string);
}
//_______________________________________________________________________________________________________________________

/* str: return string representation of numeric expression */
char *str(int v)
{
    char    *string;
    string = (char *)malloc(32);
    sprintf(string,"%d",v);
    return(string);
}
//_______________________________________________________________________________________________________________________

/* string: returns string m chars wide with n in it */
char *string(int n, char *string)
{
    int     l,i;
    char    *buffer;

    l=strlen(string)+1;

    buffer = (char *)malloc((l*n)+1);
    strcpy(buffer,"");
    for (i=0;i<n;i++)
	strcat(buffer,string);
    buffer[(l*n)] = '\0';
    return( buffer );
}
//_______________________________________________________________________________________________________________________

/* basTally:  returns number of occurances of matchstring */
int tally(char *src,char *sub,int start)
{
    int		i,ret;

    if (start<0)start = 0;
    ret=0;
    for(i=start;i<strlen(src);i++)
        if (strncmp(src+i,sub,strlen(sub))==0)
            ret++;

    return(ret);
}
//_______________________________________________________________________________________________________________________

/* trim: returns string with left and right whitespace removed */
char *trim( char *string)
{
      int     len, i;
      char    *trimmed;

    len = strlen(string);
    for ( i = len-1; i > -1; i-- ) {
        if (!isspace(string[i])) {
            string[i+1] = '\0';
            break;
        }
    }

    if (i==0)
	    string[0] = '\0';

    trimmed=string;
    while ( trimmed[0] != '\0' ) {
        if (!isspace(trimmed[0])) {
            break;
        }
        trimmed++;
    }

    return( trimmed );
}
//_______________________________________________________________________________________________________________________

/* ucase: convert string to upper case */
char *ucase(char *string)
{
    int     len, i;

    len = strlen( string );
    for ( i = 0; i<len; i++){
        string[i] = toupper( string[i] );
    }
    return( string );
}
//_______________________________________________________________________________________________________________________

/* val: returns closest numeric representation of number */
double val(char *string)
{
    return( atof(string) );
}
//_______________________________________________________________________________________________________________________
