/*
    Name:       membank.c
    Purpose:    memor bank support for wxBasic/sdlBasic
    Author:     Viola Roberto __vroby__
    Copyright:  (c) 2003 Viola Roberto <__vroby__@libero.it>
    Licence:    LGPL
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../SDLengine/SDLengine.h"
#include "BASengine.h"


char *membank[NUM_MEMBANKS];
int banksize[NUM_MEMBANKS];
int curbank;


//--Internal ---------------------------------------------------
void init_membank()
{
    int i;
    for(i=0;i<NUM_MEMBANKS;i++)
	    banksize[i]=0;
    curbank=0;
}

//--Base ---------------------------------------------------

int reservebank(int bank,int size)
{

    if (banksize[bank]!=0)
    free(membank[bank]);
    membank[bank]=(char *) malloc(size);
    banksize[bank]=size;
    curbank=bank;
    if (membank[bank]==NULL){
	error_description="membank Error:memory bank not allocated. Fill all memory?  ";
	error_type=1;
	return -1;
    }
    memset(membank[bank],0,size);
    return 0;
}
//______________________________________________________________________________________________

// warning: sdlBasic stuff

// special access at imagebank buffer
int baseimage(int bank,int n)
{
    if (SDLimage[n]!=NULL){

    	if (SDL_MUSTLOCK(SDLimage[n]))
		SDL_LockSurface(SDLimage[n]);

	membank[bank]=(char*)SDLimage[n]->pixels;
	banksize[bank]=SDLimage[n]->w * SDLimage[n]->h * SDLimage[n]->format->BytesPerPixel;
	curbank=bank;

    	if (SDL_MUSTLOCK(SDLimage[n]))
		SDL_UnlockSurface(SDLimage[n]);
	return 0;
    }
    else{
	error_description="membank Error:image not found ";
	error_type=1;
	return -1;
    }
}
//______________________________________________________________________________________________

// special access at imagebank buffer colorkeyclipped
int baseimageCC(int bank,int n)
{

    if (SDLimageCC[n]!=NULL){

	SDL_FreeSurface(SDLimageCC[n]);
	SDLimageCC[n]=SDL_DisplayFormat(SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_HWACCEL,SDLimage[n]->w,SDLimage[n]->h,32,0,0,0,0));

	SDL_BlitSurface( SDLimage[n], NULL ,SDLimageCC[n], NULL);
	Image_colorkey(SDLimageCC[n]);


	membank[bank]=(char*)SDLimageCC[n]->pixels;
	banksize[bank]=SDLimageCC[n]->w * SDLimageCC[n]->h * SDLimageCC[n]->format->BytesPerPixel;
	curbank=bank;

	return 0;
    }
    else {
	error_description="membank Error:image not found ";
	error_type=1;
	return -1;
    }
}
//______________________________________________________________________________________________

// special access at imagebank buffer colorkeyclipped
int basescreen(int bank,int n)
{
    if (SDLscreen[n]!=NULL){

    	if (SDL_MUSTLOCK(SDLscreen[n]))
		SDL_LockSurface(SDLscreen[n]);

	membank[bank]=(char*)SDLscreen[n]->pixels;
	banksize[bank]=SDLscreen[n]->w * SDLscreen[n]->h * SDLscreen[n]->format->BytesPerPixel;
	curbank=bank;

    	if (SDL_MUSTLOCK(SDLscreen[n]))
		SDL_UnlockSurface(SDLscreen[n]);
	return 0;
    }
    else{
	error_description="membank Error:screen not opened ";
	error_type=1;
	return -1;
    }
}
//______________________________________________________________________________________________

// special access at soundbank buffer
int basesound(int bank,int n)
{
    if (SDLsound[n]!=NULL){

	membank[bank]=(char *)SDLsound[n]->abuf;
	banksize[bank]=SDLsound[n]->alen;
	curbank=bank;
	return 0;
    }
    else{
	error_description="membank Error:sound not found ";
	error_type=1;
	return -1;
    }
}
//______________________________________________________________________________________________


int freebase(int bank)
{
    membank[bank]=NULL;
    banksize[bank]=0;
    if (curbank==bank)curbank=0;
    return 0;
}
//______________________________________________________________________________________________

int freebank(int bank)
{
    free(membank[bank]);
    banksize[bank]=0;
    if (curbank==bank)curbank=0;
    return 0;
}
//______________________________________________________________________________________________


int copybank(int s,int d)
{
    if (membank[s]==NULL){
	error_description="membank Error:source bank not found ";
	error_type=1;
	return -1;
    }
    if (banksize[d]!=0)
	free(membank[d]);

    membank[d]=(char *) malloc(banksize[s]);
    banksize[d]=banksize[s];

    memcpy(membank[d],membank[s],banksize[s]);
    if (membank[d]==NULL){
	error_description="membank Error:could not copy bank or memory bank not allocated ";
	error_type=1;
	return -1;
    }
    else
	return 0;
}
//______________________________________________________________________________________________

int loadbank(char *filename,int bank)
{
    int err;
    int len;
    int adv;
    unsigned int len1;
    FILE *handle;

    len1=0xfffe;
    adv=0;
    if (bank==-1)bank=curbank;


    handle=fopen(filename,"rb");
    if (handle==NULL){
	error_description="membank Error:cold not open the file for loading ";
	error_type=1;
	return -1;
    }
    fseek(handle,0,SEEK_END);
    len=ftell(handle);
    fseek(handle,0,SEEK_SET);

    if (banksize[bank]!=0)
	free(membank[bank]);

    membank[bank]=(char *) malloc(len);
    banksize[bank]=len;

    while (len1<len)
    {
	err=fread(membank[bank]+adv,len1,1,handle);
	len=len-len1;
	adv=adv+len1;
    };

    err=fread(membank[bank]+adv,len,1,handle);
    fclose(handle);
    return err;
}
//______________________________________________________________________________________________

int savebank(char *filename,int bank)
{
    int err;
    int len;
    int adv;
    unsigned int len1;
    FILE *handle;

    if (bank==-1)bank=curbank;

    handle=fopen(filename,"wb");
    if (handle==NULL){
	error_description="membank Error:cold not open the file for saving ";
	error_type=1;
	return -1;
    }

    len=banksize[bank];
    len1=0xfffe;
    adv=0;
    while (len1<len)
    {
	err=fwrite(membank[bank]+adv,1,len1,handle);
	len=len-len1;
	adv=adv+len1;
    }

    err=fwrite(membank[bank]+adv,len,1,handle);
    fclose(handle);
    return err;
}
//______________________________________________________________________________________________

int setbank(int bank)
{
    if (bank==-1){
	return curbank;
    }
    else{
	curbank=bank;
	if (membank[bank]==NULL){
	    error_description="membank Error:bank not used or not allocated ";
	    error_type=1;
	    return -1;
	}
	else
	    return 0;
    }
}
//______________________________________________________________________________________________

int sizebank(int bank)
{
    if (bank==-1)bank=curbank;
    return banksize[bank];
}


//--poke ---------------------------------------------------
//______________________________________________________________________________________________

int poke(int bank,int address,unsigned char byte)
{
    if (bank==-1)bank=curbank;

    if (address <0){
	error_description="membank Error:poke must be used  with positive address ";
	error_type=1;
	return -1;
    }
    if (address >banksize[bank]-1){
	error_description="membank Error:poke address out of bank ";
	error_type=1;
	return -1;
    }
    membank[bank][address]=byte & 255;

    return 0;
}
//______________________________________________________________________________________________

int doke(int bank,int address,unsigned short byte)
{
    if (bank==-1)bank=curbank;

    if (address <0){
	error_description="membank Error:doke must be used  with positive address ";
	error_type=1;
	return -1;
    }
    if (address+1 >banksize[bank]-1){
	error_description="membank Error:doke address out of bank ";
	error_type=1;
	return -1;
    }

    membank[bank][address]=byte & 255;
    membank[bank][address+1]=byte / 256;

    return 0;
}
//______________________________________________________________________________________________

int loke(int bank,int address,unsigned int byte)
{
    if (bank==-1)bank=curbank;


    if (address <0){
	error_description="membank Error:loke must be used  with positive address ";
	error_type=1;
	return -1;
    }
    if (address+3 >banksize[bank]-1){
	error_description="membank Error:loke address out of bank ";
	error_type=1;
	return -1;
    }

    membank[bank][address]=byte & 255;
    membank[bank][address+1]=(byte / 256)&255;
    membank[bank][address+2]=(byte/256/256) & 255;
    membank[bank][address+3]=(byte/256/256/256) & 255;

    return 0;
}


//--peek ---------------------------------------------------
//______________________________________________________________________________________________

int peek(int bank,int address)
{
    if (bank==-1)bank=curbank;

    if (address <0){
	error_description="membank Error:peek must be used with positive address ";
	error_type=1;
	return -1;
    }
    if (address >banksize[bank]-1){
	error_description="membank Error:peek address out of bank ";
	error_type=1;
	return -1;
    }

    return  (unsigned char)membank[bank][address];
}
//______________________________________________________________________________________________

int deek(int bank,int address)
{
     unsigned char lo,hi;

    if (bank==-1)bank=curbank;

    if (address <0){
	error_description="membank Error:deek must be used with positive address ";
	error_type=1;
	return -1;
    }
    if (address+1 >banksize[bank]-1){
	error_description="membank Error:deek address out of bank ";
	error_type=1;
	return -1;
    }

    lo=(unsigned char)membank[bank][address];
    hi=(unsigned char)membank[bank][address+1];
    return lo+(hi*256);
}
//______________________________________________________________________________________________

int leek(int bank,int address)
{
    unsigned char lo,hi,lohi,hihi;

    if (bank==-1)bank=curbank;

    if (address <0){
	error_description="membank Error:leek must be used with positive address ";
	error_type=1;
	return -1;
    }
    if (address+3 >banksize[bank]-1){
	error_description="membank Error:leek address out of bank ";
	error_type=1;
	return -1;
    }

    lo=(unsigned char)membank[bank][address];
    hi=(unsigned char)membank[bank][address+1];
    lohi=(unsigned char)membank[bank][address+2];
    hihi=(unsigned char)membank[bank][address+3];
    return lo+(hi*256)+(lohi*256*256)+(hihi*256*256*256);
}

//______________________________________________________________________________________________

//--fastcopy ---------------------------------------------------

int memcopy(int sbank,int s ,int dbank,int d,int size)
{
    if (banksize[sbank]-1 <s+size){
	error_description="membank Error:copy source read out of bank ";
	error_type=1;
	return -1;
    }
    if (banksize[dbank]-1 <d+size){
	error_description="membank Error:copy dest write out of bank ";
	error_type=1;
	return -1;
    }

    memcpy(&membank[dbank][d],&membank[sbank][s],size);
    return 0;
}


