/*
    Name:       datafunction.c
    Purpose:    data function for sdlBasic
    Author:     __vroby__
    Copyright:  (c) 2004 Viola Roberto <__vroby__@libero.it>
    Licence:    LGPL
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//#include "datafunction.h"
#include "BASengine.h"


char *dataarray[10000];
int dataenter,datapointer;

void init_data()
{
    dataenter=0;
    datapointer=0;
}

void loaddata(char *datavalue)
{
    if (dataarray[dataenter]!=NULL)free(dataarray[dataenter]);
    dataarray[dataenter]=(char *)malloc(strlen(datavalue));
    strcpy(dataarray[dataenter],datavalue);
    dataenter++;
}

char *readdata()
{
    if (dataarray[datapointer]!=NULL)
       return dataarray[datapointer++];
    else
	return NULL;
}
