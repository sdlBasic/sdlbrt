/*
_________________________________________________________________________________________________________________________

    SDLengine core of sdlBasic



    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Library General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    __vroby__
    __vroby__@libero.it

_________________________________________________________________________________________________________________________

*/

#include "SDLengine.h"

//_________________________________________________________________________________________________________________________

// FILE INPUT OUTPUT
//_________________________________________________________________________________________________________________________

//getfreeimage								: return a number of image bank free
int getfreeimage()
{
    int i;
    for(i=1;i<NUM_IMAGES;i++)
	if(SDLimage[i]==NULL)return i;
    return -1;
}
//_________________________________________________________________________________________________________________________

//loadimage(filename,n)							: load a graphics file in a slot n if n=-1 use the first free and return as n
int loadimage(char *filename,int n)
{
    if(n==-1)n=getfreeimage();
    if(n<0)return -1;

    if(n>NUM_IMAGES){

	error_description="SDLengine error - loadImage: given slot exceed maximum slots number";
	error_type=1;
	SDLerr(stderr,"SDLengine error - loadImage: slot %d exceed maximum image slots number ",n);
	return -1;
    }

	if (fileExist(filename)){
		if ( SDLimage[n] != NULL ) {
			SDL_FreeSurface(SDLimage[n]);
			SDL_FreeSurface(SDLimageCC[n]);
		}

		SDLimage[n]= Load_Image(filename, 0);
		SDLimageCC[n]=Load_Image(filename, 1);

		SDL_hsx[n]=0;
		SDL_hsy[n]=0;
	}
	else{
		error_description="SDLengine error - loadImage: file not found";
		error_type=1;
		SDLerr(stderr,"SDLengine error - loadImage: file '%s' not found ",filename);
		//exit(2);
		return -1;
	}
	return n;
}
//_______________________________________________________________________________________________________________________

//loadzipimage(zipfile,filename,opt n)					: load a graphics file stored in a zip archive in a slot n if n=-1 use the first free and return as n
int loadzipimage(char *zipfile,char *filename,int n)
{
    if(n==-1)n=getfreeimage();
    if(n<0)return -1;

    if(n>NUM_IMAGES){

	error_description="SDLengine error - loadZipImage: specified slot exceed image slots maximum number";
	error_type=1;
	SDLerr(stderr,"SDLengine error - loadZipImage: slot %d exceed image slots maximum number ",n);
	return -1;
    }

	if (fileExist(zipfile)){
		if ( SDLimage[n] != NULL ) {
			SDL_FreeSurface(SDLimage[n]);
			SDL_FreeSurface(SDLimageCC[n]);
		}

		SDLimage[n]= Load_zip_Image(zipfile,filename, 0);
		SDLimageCC[n]=Load_zip_Image(zipfile,filename, 1);
		if (SDLimage[n]==NULL){
		    error_description="SDLengine error - loadZipImage: image not found inside specified zip file ";
		    error_type=1;
		    SDLerr(stderr,"SDLengine error - loadZipImage: '%s' not found in zip file '%s' \n", filename, zipfile);
		    return -1;
		}
		SDL_hsx[n]=0;
		SDL_hsy[n]=0;
	}
	else{
		error_description="SDLengine error - loadZipImage: zip file not found ";
		error_type=1;
		SDLerr(stderr,"SDLengine error - loadZipImage: zip file '%s' not found ",zipfile);
		return -1;
	}
	return n;
}
//-----------------------------------------------------------------------------
int mapblobimage(unsigned char *blob, int bsize, int n)
{
    if(n==-1)n=getfreeimage();
    if(n<0)return -1;

    if(n>NUM_IMAGES){

		error_description="SDLengine error - mapblobimage: specified slot exceed image slots maximum number";
		error_type=1;
		SDLerr(stderr,"SDLengine error - mapblobimage: slot %d exceed image slots maximum number ",n);
	return -1;
    }

	if ( SDLimage[n] != NULL ) {
		SDL_FreeSurface(SDLimage[n]);
		SDL_FreeSurface(SDLimageCC[n]);
	}

	SDLimage[n]= Map_blob_Image(blob,bsize, 0);
	SDLimageCC[n]=Map_blob_Image(blob,bsize, 1);
	if (SDLimage[n]==NULL){
		    error_description="SDLengine error - mapblobimage";
		    error_type=1;
		    SDLerr(stderr,"SDLengine error - mapblobimage");
		    return -1;
	}
	SDL_hsx[n]=0;
	SDL_hsy[n]=0;

	return n;
}
//_______________________________________________________________________________________________________________________

//saveimage(filename,n)							: save slot n in a graphics file(only bmp)
int saveimage(char *filename,int n)
{
	Save_Image(filename,SDLimage[n]);
	return 0;
}
//_______________________________________________________________________________________________________________________

//getfreesound								: return a number of first sound bank free
int getfreesound()
{
    int i;
    for(i=1;i<NUM_WAVES;i++)
	if(SDLsound[i]==NULL)return i;
    return -1;
}
//_______________________________________________________________________________________________________________________

//loadsound(filename,n)							: load a wave file in a sound slot n if n=-1  use and return the first free
int loadsound(char *filename,int n)
{
	if(n==-1)n=getfreesound();
	if(n<0)return -1;
	if (n>NUM_WAVES){
		error_description="SDLengine error - loadSound: given slot exceed maximum slots number ";
		error_type=1;
		SDLerr(stderr,"SDLengine error - loadSound: slot %d exceed maximum sound slots number ",n);
		return -1;
	}


	if (fileExist(filename)){
		 Mix_FreeChunk(SDLsound[n]);
		 SDLsound[n]=Mix_LoadWAV(filename);
	}
	else{
		error_description="SDLengine error - loadSound: file not found ";
		error_type=1;
		SDLerr(stderr,"SDLengine error - loadSound: file '%s' not found ",filename);
		return -1;
	}
	return n;
}
//________________________________________________________________________________________________________________________________________

//loadzipsound(zipfile,filename,n)					: load a wave file in a sound slot n if n=-1  use and return the first free
int loadzipsound(char *zipfile,char *filename,int n)
{
    unsigned char *mem;
    SDL_RWops *src;
    int size;

	if(n==-1)n=getfreesound();
	if(n<0)return -1;
	if (n>NUM_WAVES){
		error_description="SDLengine error - loadZipSound: specified slot exceed maximum slots number ";
		error_type=1;
		SDLerr(stderr,"SDLengine error - loadZipSound: slot %d exceed maximum sound slots number ",n);
		return -1;
	}


	if (fileExist(zipfile)){
	    	if (load_zipped_file (zipfile, filename, &mem, &size)==0){
		    src=SDL_RWFromMem(mem, size);
		    Mix_FreeChunk(SDLsound[n]);
		    SDLsound[n]=Mix_LoadWAV_RW(src,1);
		}
		else{
		    error_description="SDLengine error - loadZipSound: sound not found in specified zip file";
		    error_type=1;
		    SDLerr(stderr,"SDLengine error - loadZipSound: sound '%s' not found in file '%s' \n",filename, zipfile);
		    return -1;
		}
	}
	else{
	    error_description="SDLengine error - loadZipSound: zip file not found ";
	    error_type=1;
	    SDLerr(stderr,"SDLengine error - loadZipSound: '%s' not found ", zipfile);
	    return -1;
	}
	return n;
}
//________________________________________________________________________________________________________________________________________

//savesound(filename,n)							: save a wave file from sound slot n
int savesound(char *filename, int n)
{
    FILE *fwave;
    char lws,hws;
    int i;
    int alen;

    if ( SDLsound[n] != NULL ) {
	unsigned char headsound[]={82,73,70,70,86,23,0,0,87,65,86,69,102,109,116,32,16,0,0,0,1,0,1,0,17,43,0,0,17,43,0,0,1,0,8,0,100,97,116,97};
	alen=SDLsound[n]->alen/14;
	lws=alen & 255;
	hws=alen / 256;
	fwave=fopen(filename,"wb");

	    for(i=0;i<40;i++){
		fputc(headsound[i],fwave);
	    }
	    fputc(lws,fwave);
	    fputc(hws,fwave);
	    fputc(0,fwave);
	    fputc(0,fwave);
	    fputc(0,fwave);
	    fputc(0,fwave);
	    fputc(0,fwave);

	    for(i=0;i<SDLsound[n]->alen;i+=14)
		fputc(SDLsound[n]->abuf[i+1],fwave);
	fclose(fwave);

	return 0;
    }
    else
    {
	error_description="SDLengine error - saveSound: specified sound slot is empty ";
	error_type=1;
	SDLerr(stderr,"SDLengine error - saveSound: sound slot %d is empty ", n);
	return -1;

    }
}
//_______________________________________________________________________________________________________________________

//loadmusic(filename)							: load a music module (xm,mod,ogg and only for linux mp3)
int loadmusic(char *filename)
{
	if (fileExist(filename)){
		Mix_FreeMusic(SDLmusic);
		SDLmusic = Mix_LoadMUS(filename);
	}
	else{
		error_description="SDLengine error - loadMusic: file not found ";
		error_type=1;
		SDLerr(stderr,"SDLengine error - loadMusic: file '%s' not found ", filename);
		return -1;
	}
	return 0;
}
//________________________________________________________________________________________________________________________________________

//loadzipmusic(zipfile,filename)					: load a zipped music module (xm,mod,ogg and only for linux mp3)

int loadzipmusic(char *zipfile,char *filename)
{

    char *tmpfile;

	if (fileExist(zipfile)){
	    #ifndef WIN32
		char *tmpdir="/tmp";
	    #else
		char *tmpdir=getenv("tmp");
	    #endif
		if (file_unzip(zipfile,filename,tmpdir)==0){
		    tmpfile=(char *) malloc(strlen(tmpdir)+strlen(filename)+2);
		    strcpy(tmpfile,tmpdir);
		    strcat(tmpfile,"/");
		    strcat(tmpfile,filename);
		    tmpfile[strlen(tmpfile)]='\0';
		    loadmusic(tmpfile);
		    remove(tmpfile);
		}
		else{
		    error_description="SDLengine error - loadZipMusic: music not found in specified zip file ";
		    error_type=1;
		    SDLerr(stderr,"SDLengine error - loadZipMusic: music '%s' not found in file '%s' \n", filename, zipfile);
		    return -1;
		}
	}
	else{
		error_description="SDLengine error - loadZipMusic: zip file not found ";
		error_type=1;
		SDLerr(stderr,"SDLengine error - loadZipMusic: zip file'%s' not found ", zipfile);
		return -1;
	}
	return 0;
}

//________________________________________________________________________________________________________________________________________
