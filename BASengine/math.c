//_______________________________________________________________________________________________________________________
//
//Maths
//_________________________________________________________________________________________________________________________
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "BASengine.h"


/* bin: returns binary representation of number */
char *bin(int i)
{
    int l;
    char    *buffer ,*ret;

    buffer = (char *)malloc(1024);
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

    ret = (char *)malloc(l+1);
    for (i=0;i<l;i++)
	ret[i]=buffer[l-i-1];
    ret[l]='\0';
    free(buffer);
    return ret;
}
//_______________________________________________________________________________________________________________________

/* hex: returns hexidecimal representation of number */
char *hex(int i)
{
    char *buffer;

    buffer = (char *)malloc(16);
    sprintf( buffer, "%x", i);
    return buffer;
}
//_______________________________________________________________________________________________________________________

/* randomize: reseed the random number generator */
void randomize(int seed)
{
    if (seed<0)
        seed = time(NULL);
    srand( seed );
}
//_______________________________________________________________________________________________________________________

/* rnd: return an random number */
double rnd(int upper)
{
    int result;

    result = rand();
    result = (result % (upper-1))+1;

    return( (result ) );
}
//_______________________________________________________________________________________________________________________

/* round: round to nearest integer */
double round(double n1)
{
    double n2;
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
    return( n2 );
}
//_______________________________________________________________________________________________________________________

/* sgn: returns sign of numeric expression */
int sgn(double  n)
{
    if (n < 0) {
        return(-1);
    } else if (n > 0) {
        return(1);
    } else {
        return(0);
    }
}
//_______________________________________________________________________________________________________________________

/* min: return min number of the operands */
double Min(double a, double b)
{
    if (b>a)
	return a;
    else
	return b;
}
//_______________________________________________________________________________________________________________________

/* max: return max number of the operands */
double Max(double a, double b)
{
    if (b<a)
	return a;
    else
	return b;
}
//_______________________________________________________________________________________________________________________

/* bitwiseand: return the logic and of the operands */
int bitwiseand(int a, int b)
{
    return(a & b);
}
//_______________________________________________________________________________________________________________________

/* bitwiseor: return the logic or of the operands */
int bitwiseor(int a, int b)
{
    return(a | b);
}
//_______________________________________________________________________________________________________________________

/* bitwisexor: return the logic xor of the operands */
int bitwisexor(int a, int b)
{
    return(a ^ b);
}
