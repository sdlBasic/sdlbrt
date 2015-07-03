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

// IMAGE MANIPULATION
//_________________________________________________________________________________________________________________________

//hotspot(n,x,y)							: select the point of coordinates in a imageslot (n,0,0=up left(default) | n,1,1=center | n,2,2 =down right)n= image
int hotspot(int n,int x,int y)
{
    if (SDLimage[n]!=NULL){
	switch(x) {

	case 0:
		SDL_hsx[n]=0;
		break;
	case 1:
		SDL_hsx[n]=SDLimage[n]->w / 2;
		break;
	case 2:
		SDL_hsx[n]=SDLimage[n]->w;
		break;
	default:
		SDL_hsx[n]=x;
		break;
	}

	switch(y) {

	case 0:
		SDL_hsy[n]=0;
		break;
	case 1:
		SDL_hsy[n]=SDLimage[n]->h / 2;
		break;
	case 2:
		SDL_hsy[n]=SDLimage[n]->h;
		break;
	default:
		SDL_hsy[n]=y;
		break;
	}

	return 0;
    }
    else{
	error_description="SDLengine error - hotSpot: specified image slot is empty ";
	error_type=1;
	SDLerr(stderr,"SDLengine error - hotSpot: image slot %d is empty ", n);
	return -1;
    }
}
//_________________________________________________________________________________________________________________________

//setcolorkey(c)							: set the colorkey for bitmap transparency if set -1 (default ) will be used the left-up corner color.
int setcolorkey(int c)
{
    if (c==-1){
	colorkey=-1;
    }
    else{
	colorkey=(Uint32)SDL_MapRGB(SDLdisplay->format,(c & 255),((c/256)&255),(c/(256*256))&255);
    }
    return 0;
}
//_________________________________________________________________________________________________________________________

//imageexists(n)							: return 1 if the image buffer n exist 0 if empty
int imageexists( int n )
{
	if (n<0 || n>NUM_IMAGES)return -1;

	if ( SDLimage[n] == NULL ) {
		return(0);
	}
	return 1;
}
//_________________________________________________________________________________________________________________________

//imagewidth(n)								: return the image n width or error if image n if empty
int imagewidth(int n)
{
	if (n<0 || n>NUM_IMAGES)return -1;

	if ( SDLimage[n] != NULL ) {
		return SDLimage[n]->w;
	}
	else
	{
		error_description="SDLengine error - imageWidth: specified image slot is empty ";
		error_type=1;
		SDLerr(stderr,"SDLengine error - imageWidth: image slot %d is empty ", n);
		return -1;
	}

}
//_________________________________________________________________________________________________________________________

//imageheight(n)							: return the image n height or error if image n if empty
int imageheight(int n)
{
        if (n<0 || n>NUM_IMAGES)return -1;

	if ( SDLimage[n] != NULL ) {
		return SDLimage[n]->h;
	}
	else
	{
		error_description="SDLengine error - imageHeight: specified image slot is empty ";
		error_type=1;
		SDLerr(stderr,"SDLengine error - imageHeight: image slot %d is empty", n);
		return -1;
	}
}
//________________________________________________________________________________________________________________________________________

//deleteimage(n)							: erase the image n of the memory
int deleteimage(int n)
{
        if (n<0 || n>NUM_IMAGES)return -1;

	if ( SDLimage[n] != NULL ) {
		SDL_FreeSurface(SDLimage[n]);
		SDL_FreeSurface(SDLimageCC[n]);
		SDLimage[n]=NULL;
		SDLimageCC[n]=NULL;
		return 0;
	}
	else
	{
		error_description="SDLengine error - deleteImage: specified image slot is yet empty ";
		error_type=1;
		SDLerr(stderr,"SDLengine error - deleteImage: image slot %d is yet empty", n);
		return -1;

	}

}
//________________________________________________________________________________________________________________________________________

//copyimage(s,d)  							: copy image s to image d
int copyimage(int s,int d)
{
	if (s<0 || s>NUM_IMAGES)return -1;
	if (d<0 || d>NUM_IMAGES)return -1;

	if ( SDLimage[s] != NULL ) {
		if ( SDLimage[d] != NULL ) {
			SDL_FreeSurface(SDLimage[d]);
			SDL_FreeSurface(SDLimageCC[d]);
		}

		SDLimage[d]=SDL_DisplayFormat(SDLimage[s]);
		if (SDLimage[d]==NULL)return -1;
		SDLimageCC[d]=SDL_DisplayFormat(SDLimageCC[s]);
		if (SDLimageCC[d]==NULL)return -1;
		//Image_colorkey(SDLimageCC[d]);

		return 0;
	}
	else
	{
		error_description="SDLengine error - copyImage: source image slot is empty ";
		error_type=1;
		SDLerr(stderr,"SDLengine error - copyImage: source image slot %d is empty ", s);
		return -1;

	}

}
//________________________________________________________________________________________________________________________________________

//setalpha(n,a)								: set trasparency
int setalpha(int n,int a)
{
        if (n<0 || n>NUM_IMAGES)return -1;

	if ( SDLimage[n] != NULL ) {
		SDL_SetAlpha (SDLimage[n], SDL_SRCALPHA, a) ;
		SDL_SetAlpha (SDLimageCC[n], SDL_SRCALPHA, a) ;
		return 0;
	}
	else
	{
		error_description="SDLengine error - imageAlpha: specified image slot is empty ";
		error_type=1;
		SDLerr(stderr,"SDLengine error - imageAlpha: image slot %d is empty ", n);
		return -1;
	}
}
//_________________________________________________________________________________________________________________________

//zoomimage(n,zoomx,zoomy)						: zoom image
int zoomimage(int n,double zoomx,double zoomy)
{
	SDL_Surface *tmp;

	if (n<0 || n>NUM_IMAGES)return -1;

	if ( SDLimage[n] != NULL ) {
		while(vbl==-1)waitTime(1);
		vbl=-1;
		tmp=zoomSurface(SDLimage[n], zoomx, zoomy, 0);
		if(tmp==NULL){
			error_description="SDLengine error - zoomImage: image not found ";
			error_type=1;
			SDLerr(stderr,"SDLengine error - zoomImage: image not found %s\n",SDL_GetError());
			return -1;
		}
		SDL_FreeSurface(SDLimage[n]);
		SDLimage[n]=tmp;

		tmp=zoomSurface(SDLimageCC[n], zoomx, zoomy, 0);
		if(tmp==NULL){
			error_description="SDLengine error - zoomImage: image not found ";
			error_type=1;
			SDLerr(stderr,"SDLengine error - zoomImage: image not found %s\n",SDL_GetError());
			return -1;
		}
		SDL_FreeSurface(SDLimageCC[n]);
		Image_colorkey(tmp);
		SDLimageCC[n]=tmp;
		vbl=0;
	}
	else
	{
		error_description="SDLengine error - zoomImage: specified image slot is empty ";
		error_type=1;
		SDLerr(stderr,"SDLengine error - zoomImage: image slot %d is empty", n);
		return -1;
	}
	return 0;
}
//_________________________________________________________________________________________________________________________

//rotateimage(n,angle)							: rotate image
int rotateimage(int n,double angle)
{
	SDL_Surface *tmp;

        if (n<0 || n>NUM_IMAGES)return -1;

	if ( SDLimage[n] != NULL ) {
		while(vbl==-1)waitTime(1);
		vbl=-1;

		tmp=rotozoomSurface (SDLimage[n], angle, 1, 1);
		if(tmp==NULL){
			error_description="SDLengine error - rotateImage: image not found ";
			error_type=1;
			SDLerr(stderr,"SDLengine error - rotateImage: image not found %s\n",SDL_GetError());
			return -1;
		}
		SDL_FreeSurface(SDLimage[n]);
		SDLimage[n]=tmp;

		tmp=rotozoomSurface (SDLimageCC[n], angle, 1, 1);
		if(tmp==NULL){
	    		error_description="SDLengine error - rotateImage: image not found ";
			error_type=1;
			SDLerr(stderr,"SDLengine error - rotateImage: image not found %s\n",SDL_GetError());
			return -1;
		}
		SDL_FreeSurface(SDLimageCC[n]);
		Image_colorkey(tmp);
		SDLimageCC[n]=tmp;
		vbl=0;
	}
	else
	{
		error_description="SDLengine error - rotateImage: specified image slot is empty ";
		error_type=1;
		SDLerr(stderr,"SDLengine error - rotateImage: image slot %d is empty", n);
		return -1;
	}
	return 0;

}
//_________________________________________________________________________________________________________________________

//rotozoomimage(n,angle,zoom)						: rotate and zoom image
int rotozoomimage(int n,double angle,double zoom)
{
	SDL_Surface *tmp;

        if (n<0 || n>NUM_IMAGES)return -1;

	if ( SDLimage[n] != NULL ) {
		while(vbl==-1)waitTime(1);
		vbl=-1;

		tmp=rotozoomSurface (SDLimage[n], angle, zoom, 1);
		if(tmp==NULL){
			error_description="SDLengine error - rotoZoomImage: image not found ";
			error_type=1;
			SDLerr(stderr,"SDLengine error - rotoZoomImage: image not found %s\n",SDL_GetError());
			return -1;
		}

		SDL_FreeSurface(SDLimage[n]);
		SDLimage[n]=tmp;

		tmp=rotozoomSurface(SDLimageCC[n], angle, zoom, 1);
		if(tmp==NULL){
			error_description="SDLengine error - rotoZoomImage: image not found ";
			error_type=1;
			SDLerr(stderr,"SDLengine error - rotoZoomImage: image not found %s\n",SDL_GetError());
			return -1;
		}
		SDL_FreeSurface(SDLimageCC[n]);
		Image_colorkey(tmp);
		SDLimageCC[n]=tmp;
		vbl=0;
	}
	else
	{
		error_description="SDLengine error - rotoZoomImage: specified image slot is empty ";
		error_type=1;
		SDLerr(stderr,"SDLengine error - rotoZoomImage: image slot %d is empty", n);
		return -1;
	}
	return 0;

}
//_________________________________________________________________________________________________________________________

//mirrorimage(n,x,y)							:vertical-orizontal mirror
int mirrorimage(int n,int x,int y)
{
    int px,py,dx,dy,w,h;
    SDL_Surface *tmp;
    SDL_Surface *tmpCC;
    if (n<0 || n>NUM_IMAGES)return -1;

    if ( SDLimage[n] != NULL ) {
	while(vbl==-1)waitTime(1);
	vbl=-1;

	w=SDLimage[n]->w-1;
	h=SDLimage[n]->h-1;

	tmp=SDL_DisplayFormatAlpha(SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_HWACCEL,SDLimage[n]->w,SDLimage[n]->h,32,0,0,0,0));
	tmpCC=SDL_DisplayFormatAlpha(SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_HWACCEL,SDLimage[n]->w,SDLimage[n]->h,32,0,0,0,0));
	if(tmp==NULL || tmpCC==NULL){
	    error_description="SDLengine error - mirrorImage: image not created ";
	    error_type=1;
	    SDLerr(stderr,"SDLengine error - mirrorImage: image not created %s\n",SDL_GetError());
	    return -1;
	}

	if (SDL_MUSTLOCK(SDLimage[n])){
	    SDL_LockSurface(SDLimage[n]);
	    SDL_LockSurface(SDLimageCC[n]);
	    SDL_LockSurface(tmp);
	    SDL_LockSurface(tmpCC);
	}
	for (py=0; py<=h; py++){
	    for (px=0; px<=w; px++){
		    if (x==0)
			dx=px;
		    else
			dx=w-px;

		    if (y==0)
			dy=py;
		    else
			dy=h-py;

		    putpixel(tmp,px,py,getpixel(SDLimage[n],dx,dy));
		    putpixel(tmpCC,px,py,getpixel(SDLimage[n],dx,dy));
	    }
	}
	if (SDL_MUSTLOCK(SDLimage[n])){
	    SDL_UnlockSurface(SDLimage[n]);
	    SDL_UnlockSurface(SDLimageCC[n]);
	    SDL_UnlockSurface(tmp);
	    SDL_UnlockSurface(tmpCC);
	}
	SDL_FreeSurface(SDLimage[n]);
	SDLimage[n]=tmp;
	SDL_FreeSurface(SDLimageCC[n]);
	SDLimageCC[n]=tmpCC;
	Image_colorkey(SDLimageCC[n]);

	vbl=0;
    }
    else
    {
	error_description="SDLengine error - mirrorImage: specified image slot is empty ";
	error_type=1;
	SDLerr(stderr,"SDLengine error - mirrorImage: image slot %d is empty", n);
	return -1;
    }

    return 0;
}

