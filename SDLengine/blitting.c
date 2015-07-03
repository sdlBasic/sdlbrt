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

// BLITTING
//_________________________________________________________________________________________________________________________

//blt(n,sx,sy,sw,sh,dx,dy)						: copy a part of graphics slot in screen
int blt(int n,int sx,int sy,int sw,int sh,int dx,int dy)
{
	SDL_Rect s;
	SDL_Rect d;

	s.x=sx;
	s.y=sy;
	s.w=sw;
	s.h=sh;

	d.x=dx;
	d.y=dy;
	d.w=sw;
	d.h=sh;

        if (n<0 || n>NUM_IMAGES)return -1;

	if (SDLimage[n]!=NULL){
		SDL_BlitSurface( SDLimage[n], &s ,SDLscreen[c_screen], &d);
	}
	else {
		error_description="SDLengine error - blt: specified image slot is empty ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - blt: image slot %d is empty", n);
		return-1;
	}

	if (autotimer()!=0)return -1;
	return 0;
}
//__________________________________________________________________________________________________________________________

//pastebob(x,y,n)							: copy on screen image n at x,y performing clip
int pastebob(int x,int y,int n)
{
	SDL_Rect s;
	SDL_Rect d;

	if (n<0 || n>NUM_IMAGES){
		error_description="SDLengine error - pasteBob: invalid image number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - pasteBob: %d is an invalid image number", n);
		return -1;
	}

	if (SDLimageCC[n]!=NULL){
		s.x=0;
		s.y=0;
		s.w=SDLimageCC[n]->w;
		s.h=SDLimageCC[n]->h;

		d.x=x-SDL_hsx[n];
		d.y=y-SDL_hsy[n];
		d.w=SDLimageCC[n]->w;
		d.h=SDLimageCC[n]->h;

		SDL_BlitSurface(SDLimageCC[n], &s, SDLscreen[c_screen], &d );
	}
	else {
		error_description="SDLengine error - pasteBob: specified image slot is empty ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - pasteBob: image slot %d is empty", n);
		return -1;
	}

	if (autotimer()!=0)return -1;
	return 0;
}
//__________________________________________________________________________________________________________________________

//pasteicon(x,y,n)							: copy on screen image n at x,y without clipping
int pasteicon(int x,int y,int n)
{
	SDL_Rect s;
	SDL_Rect d;

        if (n<0 || n>NUM_IMAGES){
		error_description="SDLengine error - pasteIcon: invalid image number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - pasteIcon: %d is an invalid image number", n);
		return -1;
	}

	if (SDLimage[n]!=NULL){
		s.x=0;
		s.y=0;
		s.w=SDLimage[n]->w;
		s.h=SDLimage[n]->h;

		d.x=x-SDL_hsx[n];
		d.y=y-SDL_hsy[n];
		d.w=SDLimage[n]->w;
		d.h=SDLimage[n]->h;

		SDL_BlitSurface(SDLimage[n], &s, SDLscreen[c_screen], &d );
	}
	else {
		error_description="SDLengine error: specified image slot is empty ";
		error_type=1;
		SDLerr(stderr, "SDLengine errorpasteIcon: image slot %d is empty", n);
		return -1;
	}

	if (autotimer()!=0)return -1;
	return 0;
}
//__________________________________________________________________________________________________________________________

//grab(n,x,y,w,h)							: grab a a selectarea and copy it in slot n
int grab(int n,int x,int y,int w,int h)
{
	SDL_Rect s;
	SDL_Rect d;
	int bpp;
	int oldck;

	s.x=x;
	s.y=y;
	s.w=w;
	s.h=h;

	d.x=0;
	d.y=0;
	d.w=w;
	d.h=h;

	if (n<0 || n>NUM_IMAGES)return -1;

	if (SDLimage[n]!=NULL){
	    SDL_FreeSurface(SDLimage[n]);
	    SDLimage[n] = NULL;
	    SDL_FreeSurface(SDLimageCC[n]);
	    SDLimageCC[n] = NULL;
	}

	SDLimage[n] = SDL_CreateRGBSurface(SDL_HWSURFACE, w, h,32,0,0,0,0);
	if(SDLimage[n]  == NULL) {
		error_description="SDLengine error - grab: CreateRGBSurface failed ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - grab: CreateRGBSurface failed: %s\n", SDL_GetError());
		return -1;
	}
	SDL_BlitSurface(SDLscreen[c_screen], &s, SDLimage[n], &d );

	SDLimageCC[n]=SDL_DisplayFormat(SDLimage[n]);
	if(SDLimageCC[n]  == NULL) {
		error_description="SDLengine error - grab: CreateRGBSurface failed ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - grab: CreateRGBSurfaceCC failed: %s\n", SDL_GetError());
		return -1;
	}

	bpp = SDLimageCC[n]->format->BytesPerPixel;
	oldck=colorkey;

	if (colorkey==-1){
	    if (SDL_MUSTLOCK(SDLimageCC[n]))
		SDL_LockSurface(SDLimageCC[n]);

	    colorkey=*(Uint32 *)SDLimageCC[n]->pixels;

	    if (SDL_MUSTLOCK(SDLimageCC[n]))
		SDL_UnlockSurface(SDLimageCC[n]);
	}

	switch(bpp) {
	    case 1:
		SDL_SetColorKey(SDLimageCC[n], (SDL_SRCCOLORKEY),(Uint8)colorkey);//|SDL_RLEACCEL
		break;
	    case 2:
		SDL_SetColorKey(SDLimageCC[n], (SDL_SRCCOLORKEY),(Uint16)colorkey);//|SDL_RLEACCEL
		break;
	    case 3:
		SDL_SetColorKey(SDLimageCC[n], (SDL_SRCCOLORKEY),(Uint32)colorkey);//|SDL_RLEACCEL
		break;
	    case 4:
		SDL_SetColorKey(SDLimageCC[n], (SDL_SRCCOLORKEY),(Uint32)colorkey);//|SDL_RLEACCEL
		break;
	}
	colorkey=oldck;

	SDL_hsx[n]=0;
	SDL_hsy[n]=0;

	return 0;
}
//__________________________________________________________________________________________________________________________

