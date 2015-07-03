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

//_______________________________________________________________________________________________________________________

// MOUSE
//_________________________________________________________________________________________________________________________

//xmouse								: return mouse x coordinate on display
int xmouse()
{
	int x,y;

	SDL_GetMouseState(&x, &y);
	if (autotimer()!=0)return -1;
	return x;
}
//_______________________________________________________________________________________________________________________

//ymouse								: return mouse y coordinate on display
int ymouse()
{
	int x,y;

	SDL_GetMouseState(&x, &y);
	if (autotimer()!=0)return -1;
	return y;
}
//_______________________________________________________________________________________________________________________

//xmousescreen(n)							: return mouse x coordinate on screen
int xmousescreen(int n)
{
	int x,y;

	SDL_GetMouseState(&x, &y);
	if (autotimer()!=0)return -1;
	return x+SDLoffx[n]-SDLscreen_rect[n].x;
}
//_______________________________________________________________________________________________________________________

//ymousescreen(n)							: return mouse y coordinate on screen
int ymousescreen(int n)
{
	int x,y;

	SDL_GetMouseState(&x, &y);
	if (autotimer()!=0)return -1;
	return y+SDLoffy[n]-SDLscreen_rect[n].y;
}
//_______________________________________________________________________________________________________________________

//bmouse 								: return the buttonclick on the mouse
int bmouse()
{
	if (autotimer()!=0)return -1;
	if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1))return 1;
	if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(2))return 2;
	if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(3))return 3;
	if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(4))return 4;
	if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(5))return 5;

	return 0;
}
//_______________________________________________________________________________________________________________________


//changemouse(n)							: change mouse from default(0) to emulate with sprite 0 - image 0 (1,2,3)
int changemouse(int n)
{
    SDL_Surface *temp;
    SDL_Color tmpcol;
    int tempback,tempcc;

    if (n==-1)return mousepointer;
    tempback=autoback(-1);
    tempcc=colorkey;
    colorkey=0;
    autoback(0);
    switch(n){
	case 1:
	    SDL_ShowCursor(SDL_DISABLE );
	    if(mousestate==1){
		if (SDLimageCC[0]!=NULL)SDL_FreeSurface(SDLimageCC[0]);
		SDLimageCC[0]=SDL_DisplayFormat(SDL_CreateRGBSurface(SDL_HWSURFACE, 32, 32,32,0,0,0,0));
		/* big hack: how to change an image in screen!!! */
		temp=SDLscreen[c_screen];
		SDLscreen[c_screen]=SDLimageCC[0];
		tmpcol=SDLcol;

		SDL_FillRect(SDLscreen[c_screen],NULL,0);
		ink(0xEEAA00);
		line(0,0,7,0);line(0,0,0,6);line(8,1,8,2);line(1,7,2,7);
		line(3,6,9,12);line(7,3,13,9);line(13,10,11,12);
		dot(10,12);
		ink(0xCC6600);
		line(1,1,11,11);paint(4,1);
		ink(0xEECC88);
		paint(1,4);
		SDL_hsx[0]=1;SDL_hsy[0]=1;

		/*resume hack */
		SDLscreen[c_screen]=temp;
		if (SDL_MUSTLOCK(SDLscreen[c_screen]))
		    SDL_LockSurface(SDLscreen[c_screen]);
		Image_colorkey(SDLimageCC[0]);
		if (SDL_MUSTLOCK(SDLscreen[c_screen]))
		    SDL_UnlockSurface(SDLscreen[c_screen]);
		SDLcol=tmpcol;

		}
	    mousepointer=1;
	    break;
	case 2:
	    SDL_ShowCursor(SDL_DISABLE );
	    if(mousestate==1){
		if (SDLimageCC[0]!=NULL)SDL_FreeSurface(SDLimageCC[0]);
		SDLimageCC[0]=SDL_DisplayFormat(SDL_CreateRGBSurface(SDL_HWSURFACE, 32, 32,32,0,0,0,0));
		/* big hack: how to change an image in screen!!! */
		temp=SDLscreen[c_screen];
		SDLscreen[c_screen]=SDLimageCC[0];
		tmpcol=SDLcol;

		SDL_FillRect(SDLscreen[c_screen],NULL,0);
		ink(0xEECC88);
		line(7,0,7,3);line(7,11,7,14);line(0,7,3,7);line(11,7,14,7);
		ink(0xCC6600);
		dot(7,1);dot(7,3);dot(7,11);dot(7,13);dot(1,7);dot(3,7);dot(11,7);dot(13,7);
		ink(0xEEAA00);
		dot(6,6);dot(6,8);dot(8,6);dot(8,8);
		SDL_hsx[0]=7;SDL_hsy[0]=7;

		/*resume hack */
		SDLscreen[c_screen]=temp;
		if (SDL_MUSTLOCK(SDLscreen[c_screen]))
		    SDL_LockSurface(SDLscreen[c_screen]);
		Image_colorkey(SDLimageCC[0]);
		if (SDL_MUSTLOCK(SDLscreen[c_screen]))
		    SDL_UnlockSurface(SDLscreen[c_screen]);

		SDLcol=tmpcol;
		}
	    mousepointer=2;
	    break;
	case 3:
	    SDL_ShowCursor(SDL_DISABLE );
	    if(mousestate==1){
		if (SDLimageCC[0]!=NULL)SDL_FreeSurface(SDLimageCC[0]);
		SDLimageCC[0]=SDL_DisplayFormat(SDL_CreateRGBSurface(SDL_HWSURFACE, 32, 32,32,0,0,0,0));
		/* big hack: how to change an image in screen!!! */
		temp=SDLscreen[c_screen];
		SDLscreen[c_screen]=SDLimageCC[0];
		tmpcol=SDLcol;

		SDL_FillRect(SDLscreen[c_screen],NULL,0);
		ink(0xCC6600);
		bar(0,2,1,14);bar(13,2,14,14);bar(1,1,4,7);bar(10,1,13,7);
		bar(3,0,11,6);
		ink(0xEEAA00);
		bar(3,2,11,4);bar(4,1,10,5);bar(5,0,9,6);line(5,11,7,6);
		ink(0xEECC88);
		bar(4,2,10,4);bar(5,1,9,5);bar(3,12,5,13);line(0,15,14,15);
		ink(0xCC6600);
		line(7,1,7,3);line(8,3,9,4);
		SDL_hsx[0]=7;SDL_hsy[0]=7;


		/*resume hack */
		SDLscreen[c_screen]=temp;
		if (SDL_MUSTLOCK(SDLscreen[c_screen]))
		    SDL_LockSurface(SDLscreen[c_screen]);
		Image_colorkey(SDLimageCC[0]);
		if (SDL_MUSTLOCK(SDLscreen[c_screen]))
		    SDL_UnlockSurface(SDLscreen[c_screen]);
		SDLcol=tmpcol;
		}
	    mousepointer=3;
	    break;

	default:
	    if(mousestate==1){
		locatemouse(xmouse(),ymouse());
		deletesprite(0);
		mouseshow();
	    }
	    else{
		mousehide();
		deletesprite(0);
		}
	    mousepointer=0;
	    break;
    }
    colorkey=tempcc;
    autoback(tempback);
    if (autotimer()!=0)return -1;
    return 0;
}
//_______________________________________________________________________________________________________________________

//locatemouse(x,y)							: move mouse at x y coordinates
int locatemouse(int x, int y)
{
   SDL_WarpMouse(x,y);
   return 0;
}
//_______________________________________________________________________________________________________________________

//mouseshow								: show the mouse cursor
int mouseshow()
{
	SDL_ShowCursor(SDL_ENABLE);
	mousestate=1;
	if (autotimer()!=0)return -1;
	return 0;
}
//_______________________________________________________________________________________________________________________

//mousehide								: hide the mouse cursor
int mousehide()
{
	SDL_ShowCursor(SDL_DISABLE );
	mousestate=0;
	if (autotimer()!=0)return -1;
	return 0;
}
//_______________________________________________________________________________________________________________________

//mousezone(x,y,w,h)							: return 1 if the mouse pointer is in rectangle(xy with size wh)
int mousezone(int x,int y,int w,int h)
{
	if (autotimer()!=0)return -1;
	if ( xmousescreen(c_screen)>x)
		if (xmousescreen(c_screen)<(x+w))
			if(ymousescreen(c_screen)>y)
				if(ymousescreen(c_screen)<y+h)
					return 1;
	return 0;
}
