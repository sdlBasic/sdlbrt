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

    vroby65
    vroby.mail@gmail.com

_________________________________________________________________________________________________________________________

*/

#include "SDLengine.h"

//_________________________________________________________________________________________________________________________

//SCREEN
//_________________________________________________________________________________________________________________________

//setdefaults(w,h,bpp,0=screen|1=window |2=resizable)		: open the display, perform initializations on cursor and fonts and sets default values on sprites, bobs and screens system.
int setdefaults(int w,int h, int bpp, int mode)
{
	setdisplay(w,h,bpp,mode);
	autoback(25);

	/* create and initialize print font */
	createfont();

	/* create and initialize print cursor */
	createcursor();

	autoupdatesprite(1);
	autoupdatebob(1);
	dualplayfield(0);
	mouseshow();
	return 0;
}

//setdisplay(w,h,bpp,0=screen|1=window |2=resizable)			: open the screen/window in double buffer.
int setdisplay(int w,int h, int bpp, int mode)
{
    #define SAFERES() setdisplay(640,480,0,1)
	//GL_display=0;
	display_mode=mode;
	SDLnoAlphaChannel=0;//alpha enabled

	switch (mode){
	case 0:
		/* Open the display device full screen */
		SDLdisplay = SDL_SetVideoMode(w, h, bpp, SDL_HWSURFACE|SDL_FULLSCREEN|SDL_DOUBLEBUF|SDL_ANYFORMAT|SDL_HWPALETTE|SDL_SRCALPHA );//|SDL_ASYNCBLIT
		if ( SDLdisplay == NULL ) {
			display_mode=1;
			SAFERES();
			autoback(25);
			error_description="SDLengine error - setDisplay: Can't set requested video mode ";
			error_type=1;
			SDLerr(stderr, "SDLengine error - setDisplay: Can't set video mode: %d ",mode);
			return -1;
		}
		#if defined(UNIX) 
		SDLnoAlphaChannel=0;
		#else
		SDLnoAlphaChannel=1;
		#endif
		break;

	case 1:
		/* Open the display device window */
		SDLdisplay = SDL_SetVideoMode(w, h, bpp, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_ANYFORMAT|SDL_HWPALETTE|SDL_SRCALPHA);//|SDL_ASYNCBLIT
		SDL_WM_SetCaption("sdlBasic",NULL );
		if ( SDLdisplay == NULL ) {
			display_mode=1;
			SAFERES();
			autoback(25);
			error_description="SDLengine error - setDisplay: Can't set requested video mode ";
			error_type=1;
			SDLerr(stderr, "SDLengine error - setDisplay: Can't set video mode: %d ", mode);
			return -1;

		}
		break;

	case 2:
		/* Open the display device window */
		SDLdisplay = SDL_SetVideoMode(w, h, bpp, SDL_HWSURFACE|SDL_RESIZABLE|SDL_DOUBLEBUF|SDL_ANYFORMAT|SDL_HWPALETTE|SDL_SRCALPHA);//|SDL_ASYNCBLIT
		SDL_WM_SetCaption("sdlBasic",NULL );
		if ( SDLdisplay == NULL ) {
			display_mode=1;
			SAFERES();
			autoback(25);
			error_description="SDLengine error - setDisplay: Can't set requested video mode ";
			error_type=1;
			SDLerr(stderr, "SDLengine error - setDisplay: Can't set video mode: %d ", mode);
			return -1;
		}
		break;

	case 3:
		/* Open the display device full screen software mode*/
		SDLdisplay = SDL_SetVideoMode(w, h, bpp, SDL_FULLSCREEN|SDL_SRCALPHA);//|SDL_ASYNCBLIT
		if ( SDLdisplay == NULL ) {
			display_mode=1;
			SAFERES();
			autoback(25);
			error_description="SDLengine error - setDisplay: Can't set requested video mode ";
			error_type=1;
			SDLerr(stderr, "SDLengine error - setDisplay: Can't set video mode: %d ",mode);
			return -1;
		}
		break;

	case 4:
		/* Open the display device window */
		SDLdisplay = SDL_SetVideoMode(w, h, bpp, SDL_HWSURFACE|SDL_NOFRAME|SDL_DOUBLEBUF|SDL_ANYFORMAT|SDL_HWPALETTE|SDL_SRCALPHA);//|SDL_ASYNCBLIT
		if ( SDLdisplay == NULL ) {
			display_mode=1;
			SAFERES();
			autoback(25);
			error_description="SDLengine error - setDisplay: Can't set requested video mode ";
			error_type=1;
			SDLerr(stderr, "SDLengine error - setDisplay: Can't set video mode: %d ", mode);
			return -1;

		}
		break;
		
		
		
	default:
		display_mode=1;
		error_description="SDLengine error - setDisplay: invalid video mode ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - setDisplay: %d is not a valid video mode ",mode);
		return -1;
		break;
	}

	SDL_FillRect(SDLdisplay,NULL,0);

	switch (SDLdisplay->format->BytesPerPixel){
	case 1:
			getpixel=getpixel8;
			putpixel=putpixel8;
			rrgb=rrgb8;
			enablePalette=0;
			break;
	case 2:
			getpixel=getpixel16;
			putpixel=putpixel16;
			rrgb=rrgb16;
			enablePalette=0;
			break;
	case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN){
				getpixel=getpixel24BE;
				putpixel=putpixel24BE;
				rrgb=rrgb24;
			}
			else{
				getpixel=getpixel24;
				putpixel=putpixel24;
				rrgb=rrgb24;
			}
			enablePalette=0;
			break;
	case 4:
			getpixel=getpixel32;
			putpixel=putpixel32;
			rrgb=rrgb32;
			enablePalette=0;
			break;
	default:
			error_description="SDLengine error - setDisplay: specified video bpp is not valid ";
			error_type=1;
			SDLerr(stderr, "SDLengine error - setDisplay: %d is not a valid video bpp ",bpp);
			return -1;
			break;
	}

	SDLautobacktime=chrono()+400;
	screenopen(0,SDLdisplay->w,SDLdisplay->h,0,0,SDLdisplay->w,SDLdisplay->h,0);
	spriteclip(0,0,SDLdisplay->w,SDLdisplay->h);

	/* set the pointer */
	if ( mode==0)
	changemouse(1);
	else
	changemouse(0);

	if (autotimer()!=0)return -1;
	return 0;
}
//_______________________________________________________________________________________________________________________

//setalphachannel(v)							: activate deactivate alpha channel trasparency
int setalphachannel(int v)
{
    SDLnoAlphaChannel=1-v;
    return SDLnoAlphaChannel;
}
//_______________________________________________________________________________________________________________________

//setcaption(title)						: change the display window title
int setcaption(char *title)
{
    SDL_WM_SetCaption(title, title);
    if (autotimer()!=0)return -1;
    return 0;
}
//_______________________________________________________________________________________________________________________

//caption()							: return the display window title
int caption(char **title)
{
    char **icon;

    icon=NULL;
    SDL_WM_GetCaption(title,icon);
    if (autotimer()!=0)return -1;

    return 0;
}
//_______________________________________________________________________________________________________________________

//systemwidth				: return the native screen width
int systemwidth()
{
	return SystemWidth; 
}
//_______________________________________________________________________________________________________________________

//systemheight				: return the native screen height
int systemheight()
{
	return SystemHeight; 	
}
//_______________________________________________________________________________________________________________________

//displaymode()						: return the display mode
int displaymode()
{
	return display_mode;
}
//_______________________________________________________________________________________________________________________

//displaywidth()						: return the display width
int displaywidth()
{
	return SDLdisplay->w;
}
//_______________________________________________________________________________________________________________________

//displayheight()						: return the display height
int displayheight()
{
	return SDLdisplay->h;
}
//_______________________________________________________________________________________________________________________

//display.bpp							: return the display color depth
int displaybpp()
{
	return (SDLdisplay->format->BytesPerPixel * 8);
}

//_______________________________________________________________________________________________________________________

//screen n							: set the logic screen n  with n=-1 return the current screen
int screen (int n)
{
	if (n==-1)return c_screen;

	if (SDLscreen_live[n]!=0){
		c_screen=n;
	}
	else{
		error_description="SDLengine error - screen: screen does not exist ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - screen: Screen %d does not exist ", n);
		return -1;
	}

	if (autotimer()!=0)return -1;
	return 0;
}
//_______________________________________________________________________________________________________________________

//screenz(n,z)								: set the zorder position of screen if z =-1 report actual z position
int screenz(int n,int z)
{

    int i,oldz;

    if (z>SDLlastscreen-1)z=SDLlastscreen-1;

    oldz=-1;
    for(i=0;i<SDLlastscreen;i++)
	if(SDLscreen_z[i]==n)oldz = i;
    if (oldz==-1)return -1;

    if (z==-1)
	return oldz;
    else{
	if (z==oldz)return 0;
	if (z>oldz){
	    for(i=oldz;i<=z-1;i++)
		SDLscreen_z[i]=SDLscreen_z[i+1];
	    SDLscreen_z[z]=n;

	}
	else{
    	    for(i=oldz;i>=z;i--)
		SDLscreen_z[i]=SDLscreen_z[i-1];
	    SDLscreen_z[z]=n;

	}
    }
    return 0;

}
//_______________________________________________________________________________________________________________________

//lastscreen								: return the last screen open
int lastscreen()
{
    if (SDLlastscreen!=0)return SDLlastscreen-1;
	return SDLlastscreen;
}
//_______________________________________________________________________________________________________________________

// directscreen 						: direct drawing on display like a screen(more fast but sprite and offset does not works)
int directscreen ()
{
	if (SDLscreen_live[0]==1){
		SDL_FreeSurface(SDLscreen[0]);
	}

	SDLscreen[0]=SDLdisplay;
	SDLscreen_live[0]=-1;
	return 0;
}
//_______________________________________________________________________________________________________________________

//screenopen n,w,h,dx,dy,dw,dh,flag				: open the logic screen n of dimension w,h in display coordinates dx,dy,dw,dh
int screenopen (int n,int w,int h,int dx,int dy,int dw,int dh,int flag)
{
	SDL_Surface *temp;
	int bpp;

	if (n<0 ||n>8){
			error_description="SDLengine error - screenOpen: Invalid screen number. Valid screens range from 0 to 8 ";
			error_type=1;
			SDLerr(stderr, "SDLengine error - screenOpen: %d is an invalid screen number. Valid screens range from 0 to 8: ",n);
			return -1;
	}

	if (SDLscreen_live[n]!=0){
		SDL_FreeSurface(SDLscreen[n]);
		SDLscreen_live[n]=0;
	}

	if (SDLscreen_live[n]==0){

		temp = SDL_CreateRGBSurface(SDL_HWSURFACE, w, h,displaybpp(),0,0,0,0);

		if(temp  == NULL) {
			error_description="SDLengine error - screenOpen: Internal error. CreateRGBSurface failed ";
			error_type=1;
			SDLerr(stderr, "SDLengine error - screenOpen: Internal error. CreateRGBSurface failed: %s ", SDL_GetError());
			return -1;
		}

		if ( flag >1 ) {
			paper(0);
			SDL_FillRect(temp,NULL,0);
			if (SDL_MUSTLOCK(temp))
				SDL_LockSurface(temp);
			bpp = temp->format->BytesPerPixel;
			switch(bpp) {
				case 1:
					SDL_SetColorKey(temp, (SDL_SRCCOLORKEY),*(Uint8 *)temp->pixels);//|SDL_RLEACCEL
					break;
				case 2:
					SDL_SetColorKey(temp, (SDL_SRCCOLORKEY),*(Uint16 *)temp->pixels);//|SDL_RLEACCEL
					break;
				case 3:
					SDL_SetColorKey(temp, (SDL_SRCCOLORKEY),*(Uint32 *)temp->pixels);//|SDL_RLEACCEL
					break;
				case 4:
					SDL_SetColorKey(temp, (SDL_SRCCOLORKEY),*(Uint32 *)temp->pixels);//|SDL_RLEACCEL
					break;
			}
			if (SDL_MUSTLOCK(temp))
				SDL_UnlockSurface(temp);
		}


		SDLscreen[n]=SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);
		//SDLscreen[n]=temp;
		SDLoffx[n]=0;
		SDLoffy[n]=0;

		if (dw>w)dw=w;
		if (dh>h)dh=h;

		SDLscreen_rect[n].x=dx;
		SDLscreen_rect[n].y=dy;
		SDLscreen_rect[n].w=dw;
		SDLscreen_rect[n].h=dh;
		if (SDLoffx[c_screen]<0)
				SDLoffx[c_screen]=0;
		if (SDLoffx[c_screen]+SDLscreen_rect[c_screen].w >SDLscreen[c_screen]->w)
				SDLoffx[c_screen]=SDLscreen[c_screen]->w - SDLscreen_rect[c_screen].w;
		if (SDLoffy[c_screen]<0)
				SDLoffy[c_screen]=0;
		if (SDLoffy[c_screen]+SDLscreen_rect[c_screen].h >SDLscreen[c_screen]->h)
				SDLoffy[c_screen]=SDLscreen[c_screen]->h - SDLscreen_rect[c_screen].h;
		SDLscreen_flag[n]=flag;
		SDLscreen_live[n]=1;
		//printf("screenopen n=%d dx=%d dy=%d dw=%d dh=%d\n",n,dx,dy,dw,dh);
		SDL_FillRect(SDLscreen[n],NULL,0);

		screen(n);

		if (SDLlastscreen<=n)SDLlastscreen=n+1;

		if (SDLlastscreen>8)SDLlastscreen=8;


	if (autotimer()!=0)return -1;
	return 0;
	}
	else{
			error_description="SDLengine error: specified screen is yet opened ";
			error_type=1;
			SDLerr(stderr, "SDLengine error: Screen %d is yet opened ", n);
			return -1;
	}
}
//_______________________________________________________________________________________________________________________

//screenclose n							: close the logic screen n
int screenclose (int n)
{
	int i;

	if(c_screen==n){
		cursoff();
		for(i=7;i>=0;i--){
			if(SDLscreen_live[i]!=0 &&n!=i){
				c_screen=i;
				break;

			}
		}
	}

	if (c_screen!=n){
		if (SDLscreen[n]!=NULL){
			SDL_FreeSurface(SDLscreen[n]);
			SDLscreen_live[n]=0;
			return 0;
		}
		else{
			error_description="SDLengine error - screenClose: screen not yet opened ";
			error_type=1;
			SDLerr(stderr, "SDLengine error - screenClose: screen %d not yet opened ", n);
			return -1;
		}
	}
	else {
		error_description="SDLengine error - screenClose: can't close screen, surface in use ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - screenClose: can't close screen %d, surface in use ", n);
		return -1;
	}

	i=SDLlastscreen;
	while(SDLscreen_live[i]==0){
	    i--;
    	    screenz(i,i);

	}
	SDLlastscreen=i+1;



	if (autotimer()!=0)return -1;
	return 0;
}
//_______________________________________________________________________________________________________________________

//screenclone n,s,x,y,w,h,flag					: create a  new viewport in logic screen s
int screenclone(int n,int s,int x,int y,int w,int h,int flag)
{
	if (SDLscreen[s]!=NULL){
		SDLscreen[n]= SDLscreen[s];
		SDLoffx[n]=0;
		SDLoffy[n]=0;
		SDLscreen_rect[n].x=x;
		SDLscreen_rect[n].y=y;
		SDLscreen_rect[n].w=w;
		SDLscreen_rect[n].h=h;
		SDLscreen_flag[n]=flag;
		SDLscreen_live[n]=1;
		screen(n);
		if(SDLlastscreen<=n)SDLlastscreen=n+1;
		return 0;
	}else{
		error_description="SDLengine error - screenClone: screen not yet opened ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - screenClone: screen %d not yet opened ", s);
		return -1;
		}
}
//_______________________________________________________________________________________________________________________

//screencopy(n,x,y,w,h,nd,xd,yd)						: copy a portion of screen n in a screen nd
int screencopy(int n,int x,int y,int w,int h,int nd,int xd,int yd)
{


	SDL_Rect s;
	SDL_Rect d;

	s.x=x;
	s.y=y;
	s.w=w;
	s.h=h;

	d.x=xd;
	d.y=yd;
	d.w=w;
	d.h=h;

	if (SDLscreen[n]!=NULL && SDLscreen[nd]!=NULL){
		SDL_BlitSurface( SDLscreen[n], &s ,SDLscreen[nd], &d);
	}
	else {
		if (SDLscreen[n]==NULL){
			error_description="SDLengine error - screenCopy: source screen does not exist ";
			error_type=1;
			SDLerr(stderr, "SDLengine error - screenCopy: source screen %d does not exist ", n);
			return -1;
		}else{
			error_description="SDLengine error - screenCopy: destination screen does not exist ";
			error_type=1;
			SDLerr(stderr, "SDLengine error - screenCopy: destination screen %d does not exist ", nd);
			return -1;
		}
	}

	if (autotimer()!=0)return -1;
	return 0;
}
//_______________________________________________________________________________________________________________________

//screenfade(n,t)								: fade the screen n in t time
int screenfade(int n,int t)
{
	if (autotimer()!=0)return -1;
	if(t==-1)return fadeflag[n];

	if (SDLscreen[n]!=NULL){
		fade(n,SDLscreen[n],SDLscreen[n],t,1);
	return 0;
	}
	else{
		error_description="SDLengine error - screenFadeOut: specified screen does not exist ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - screenFadeOut: Screen %d does not exist", n);
		return -1;
	}
}
//_______________________________________________________________________________________________________________________

//screenfadein(n,i,t)								: fade the screen n to image i in t time
int screenfadein(int n,int i,int t)
{
	if (autotimer()!=0)return -1;
 	if(t==-1)return fadeflag[n];

	if(imageexists(i)==0){
		error_description="SDLengine error - screenFadeIn: specified image slot is empty ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - screenFadeIn: image slot %d is empty", i);
		return -1;
	}

	if (SDLscreen[n]!=NULL){
		fade(n,SDLscreen[n],SDLimage[i],t,0);
	return 0;
	}
	else{
		error_description="SDLengine error - screenFadeIn: specified screen does not exist ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - screenFadeIn: screen %d does not exist", n);
		return -1;
	}
}
//_______________________________________________________________________________________________________________________

//screencrossfade(n,i,t)							: fade the screen n from current screen  to image i in t time
int screencrossfade(int n,int i,int t)
{
	SDL_Surface *tmp;

	if (autotimer()!=0)return -1;
	if(t==-1)return crossfadeflag[n];

	if(imageexists(i)==0){
		error_description="SDLengine error - screenCrossFade: specified image slot is empty ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - screenCrossFade: image slot %d is empty", i);
		return -1;
	}
	if(t==0 || t<-1){
		error_description="SDLengine error - screenCrossFade: invalid fade duration value";
		error_type=1;
		SDLerr(stderr, "SDLengine error - screenCrossFade: %d is not a valid fade duration value", t);
		return -1;
	}

	if (SDLscreen[n]!=NULL){
		tmp=SDL_DisplayFormat(SDLscreen[n]);
		crossfade(n,SDLscreen[n],tmp,SDLimage[i],t);
	return 0;
	}
	else{
		error_description="SDLengine error - screenCrossFade: specified screen does not exist ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - screenCrossFade: screen %d does not exist", n);
		return -1;
	}
}
//_______________________________________________________________________________________________________________________

//screenalpha(n,a)								: set alpha(trasparency) of screen n
int screenalpha(int n,int a)
{
	if ( SDLscreen[n] != NULL ) {
		SDL_SetAlpha (SDLscreen[n], SDL_SRCALPHA, a);
	if (autotimer()!=0)return -1;
		return 0;
	}
	else
	{
		error_description="SDLengine error - screenAlpha: specified screen does not exist ";
		error_type=1;
		SDLerr(stderr,"SDLengine error - screenAlpha: screen %d does not exist ", n);
		return -1;
	}

}
//_______________________________________________________________________________________________________________________

//screenlock(n)								: lock the  screen n for direct graphics access
int screenlock(int n)
{
    if (SDL_MUSTLOCK(SDLscreen[n]))
	SDL_LockSurface(SDLscreen[n]);
    return 0;
}
//_______________________________________________________________________________________________________________________

//screenunlock(n)							: unlock the  screen n for direct graphics access
int screenunlock(int n)
{
    if (SDL_MUSTLOCK(SDLscreen[n]))
	SDL_UnlockSurface(SDLscreen[n]);
    return 0;
}
//_______________________________________________________________________________________________________________________

//screenrect(x,y,w,h,flag)						: change the display output coordinates of the current screen
int screenrect (int x,int y,int w,int h,int flag)
{
	SDLscreen_rect[c_screen].x=x;
	SDLscreen_rect[c_screen].y=y;
	SDLscreen_rect[c_screen].w=w;
	SDLscreen_rect[c_screen].h=h;
	SDLscreen_flag[c_screen]=flag;

	if (SDLoffx[c_screen]<0)
		SDLoffx[c_screen]=0;
	if (SDLoffx[c_screen]+SDLscreen_rect[c_screen].w >SDLscreen[c_screen]->w)
		SDLoffx[c_screen]=SDLscreen[c_screen]->w - SDLscreen_rect[c_screen].w;
	if (SDLoffy[c_screen]<0)
		SDLoffy[c_screen]=0;
	if (SDLoffy[c_screen]+SDLscreen_rect[c_screen].h >SDLscreen[c_screen]->h)
		SDLoffy[c_screen]=SDLscreen[c_screen]->h - SDLscreen_rect[c_screen].h;


	if (autotimer()!=0)return -1;
	return 0;
}
//_______________________________________________________________________________________________________________________

//xscreenrect								: return the x coordinate of current screen viewport
int xscreenrect()
{
	return SDLscreen_rect[c_screen].x;
}
//_______________________________________________________________________________________________________________________

//yscreenrect								: return the y coordinate of current screen viewport
int yscreenrect()
{
	return SDLscreen_rect[c_screen].y;
}
//_______________________________________________________________________________________________________________________

//wscreenrect								: return the w value of current screen viewport
int wscreenrect()
{
	return SDLscreen_rect[c_screen].w;
}
//_______________________________________________________________________________________________________________________

//hscreenrect								: return the h value of current screen viewport
int hscreenrect()
{
	return SDLscreen_rect[c_screen].h;
}
//_______________________________________________________________________________________________________________________

//flagscreenrect							: return the flag value of current screen viewport
int flagscreenrect()
{
	return SDLscreen_flag[c_screen];
}
//_______________________________________________________________________________________________________________________

//screenwidth								: return the current screen width
int screenwidth()
{
	return SDLscreen[c_screen]->w;
}
//_______________________________________________________________________________________________________________________

//screenheight								: return the current screen height
int screenheight()
{
	return SDLscreen[c_screen]->h;
}
//_______________________________________________________________________________________________________________________

//offset(x,y)								: set the logical current screen position
int offset(int x,int y)
{
	SDLoffx[c_screen]=x;
	SDLoffy[c_screen]=y;
	if (SDLoffx[c_screen]<0)
		SDLoffx[c_screen]=0;
	if (SDLoffx[c_screen]+SDLscreen_rect[c_screen].w >SDLscreen[c_screen]->w)
		SDLoffx[c_screen]=SDLscreen[c_screen]->w - SDLscreen_rect[c_screen].w;
	if (SDLoffy[c_screen]<0)
		SDLoffy[c_screen]=0;
	if (SDLoffy[c_screen]+SDLscreen_rect[c_screen].h >SDLscreen[c_screen]->h)
		SDLoffy[c_screen]=SDLscreen[c_screen]->h - SDLscreen_rect[c_screen].h;

	if (autotimer()!=0)return -1;
	return 0;
}
//_______________________________________________________________________________________________________________________

//xoffset								: return the x coordinate offset in current screen
int xoffset()
{
	return SDLoffx[c_screen];
}
//_______________________________________________________________________________________________________________________

//yoffset								: return the y coordinate offset in current screen
int yoffset()
{
	return SDLoffy[c_screen];
}
//_______________________________________________________________________________________________________________________

//cls 									: clear the current logic screen
int cls()
{
    int r,g,b;
	b = paper_color & 255;
	g =( paper_color / 256) & 255 ;
	r =( paper_color / (256*256)) & 255;

	stx[c_screen]=0;
	sty[c_screen]=0;
	SDL_FillRect(SDLscreen[c_screen],NULL,(Uint32)SDL_MapRGB(SDLdisplay->format,r,g,b));
	if (autotimer()!=0)return -1;
	return 0;
}
//_______________________________________________________________________________________________________________________

//screenswap								: update display,bobsystem,spritesystem
int screenswap()
{

	SDL_Rect d;
	SDL_Rect s;
	int i,iz;

	getevent();
	if (stopkey()==-1)return -1;


	/* the negative mode of screenswap (autoback(-15))*/
	if (SDLautoback<0){
		while (chrono()<SDLautobacktime){
			SDL_Delay(5);			
			getevent();
		}
		SDLautobacktime=chrono()+abs(SDLautoback);
	}


	if (vbl!=-1){
	    vbl=-1;

	/* if mouse cursor is software update sprite 0 with image 0 as mouse pointer */
	if (mousepointer>0 && mousestate!=0)
	    sprite(0,xmouse(),ymouse(),0);

	/* update the textprint cursor system */
	/*
		states of textprint cursor system:
		0:disable
		1:on enable
		2:enable
		3:on desable (will be change)
	*/

	    for(i=0;i<SDLlastscreen;i++){
		if(cursore_state[i]>0) {

		    if (cursore_state[i]==1){
			SDLcursore_preserve[i] = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_HWACCEL, XPRINT_SIZE,PRINT_SIZE*2,32,0,0,0,0);
			if(SDLcursore_preserve[i]  == NULL) {
			    error_description="SDLengine error: CreateRGBSurface failed ";
			    error_type=1;
			    SDLerr(stderr, "SDLengine error: CreateRGBSurface failed: %s\n", SDL_GetError());
			    return -1;
			}
			cursore_state[i]=2;
		    }

		    if (cursore_state[i]>2){
		    	SDL_FreeSurface(SDLcursore_preserve[i]);
			cursore_state[i]=0;
		    }
		    if(cursore_state[i]==2) {
			oldstx[i]=stx[i];
			oldsty[i]=sty[i];

			//print the textprint cursor and  update the frame animation
			d.x=oldstx[i]*XPRINT_SIZE;
			d.y=oldsty[i]*(PRINT_SIZE+1);
			d.w=XPRINT_SIZE;
			d.h=PRINT_SIZE*2;
			s.x=0;
			s.y=0;
			s.w= XPRINT_SIZE;
			s.h= PRINT_SIZE*2;
			//preserve cursor background in cursor 0 anim
			SDL_BlitSurface( SDLscreen[i], &d, SDLcursore_preserve[i], NULL);

			SDL_BlitSurface(SDLcursore[cursore_anim[i]], NULL, SDLscreen[i], &d );

			cursore_anim[i]++;
			if (cursore_anim[i]>14)cursore_anim[i]=0;
		    }
		}
	}
	/***************************/



	/* update the bob system */
	if (SDLupdatebob!=0){

		//take the background
		for (iz=0;iz<SDLlastbob;iz++){
			i=SDLbobz[iz];
			if (SDLboblive[i]==1){
				if (SDLbobback[i]==NULL)
				{
					d.x=SDLbobxold[i];
					d.y=SDLbobyold[i];
					d.w=SDLimageCC[SDLbobfr[i]]->w;
					d.h=SDLimageCC[SDLbobfr[i]]->h;

					s.x=0;
					s.y=0;
					s.w= d.w;
					s.h= d.h;
					SDLbobback[i] = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_HWACCEL, s.w, s.h,32,0,0,0,0);
					if(SDLbobback[i]  == NULL) {
						error_description="SDLengine error: CreateRGBSurface failed ";
						error_type=1;
						SDLerr(stderr, "SDLengine error: CreateRGBSurface failed: %s\n", SDL_GetError());
						return -1;
					}
					//SDLbobback[i]=SDL_DisplayFormat(SDLbobback[i]);
				}

				if (SDLimageCC[SDLbobfr[i]]->w !=SDLbobback[i]->w || SDLimageCC[SDLbobfr[i]]->h !=SDLbobback[i]->h){
					SDL_FreeSurface(SDLbobback[i]);

					d.x=SDLbobxold[i];
					d.y=SDLbobyold[i];
					d.w=SDLimageCC[SDLbobfr[i]]->w;
					d.h=SDLimageCC[SDLbobfr[i]]->h;

					s.x=0;
					s.y=0;
					s.w= d.w;
					s.h= d.h;

					SDLbobback[i] = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_HWACCEL, s.w, s.h,32,0,0,0,0);
					if(SDLbobback[i]  == NULL) {
						error_description="SDLengine error: CreateRGBSurface failed ";
						error_type=1;
						SDLerr(stderr, "SDLengine error: CreateRGBSurface failed: %s\n", SDL_GetError());
						return -1;
					}
					//SDLbobback[i]=SDL_DisplayFormat(SDLbobback[i]);
				}


				SDLbobxold[i]=SDLbobx[i];
				SDLbobyold[i]=SDLboby[i];

				d.x=SDLbobxold[i];
				d.y=SDLbobyold[i];
				d.w=SDLimageCC[SDLbobfr[i]]->w;
				d.h=SDLimageCC[SDLbobfr[i]]->h;

				s.x=0;
				s.y=0;
				s.w= d.w;
				s.h= d.h;


				d.x=SDLbobxold[i];
				d.y=SDLbobyold[i];
				SDL_BlitSurface(SDLscreen[SDLbobscreen[i]], &d, SDLbobback[i], &s );
			}//end if
		}//end for

		//paste the bob
		for (iz=0;iz<SDLlastbob;iz++){
			i=SDLbobz[iz];
			if (SDLboblive[i]==1){

				d.x=SDLbobxold[i];
				d.y=SDLbobyold[i];
				d.w=SDLimageCC[SDLbobfr[i]]->w;
				d.h=SDLimageCC[SDLbobfr[i]]->h;

				s.x=0;
				s.y=0;
				s.w= d.w;
				s.h= d.h;

				if (SDLimageCC[SDLbobfr[i]]!=NULL){
					SDL_BlitSurface(SDLimageCC[SDLbobfr[i]], &s, SDLscreen[SDLbobscreen[i]], &d );
				}
				else {
					error_description="SDLengine error: bob image does not exist ";
					error_type=1;
					SDLerr(stderr, "SDLengine error: bob image does not exist");
					return -1;
				}//end if


			}//end if
		}//end for
	}//end if
	/***********************/


	/* update the display system under sprites*/
	for (iz=0;iz<SDLlastscreen;iz++){
		i=SDLscreen_z[iz];
		if (SDLscreen_live[i]==1){
			if ((SDLscreen_flag[i] & 1)==0){
				s.x=SDLoffx[i];
				s.y=SDLoffy[i];
				s.w=SDLscreen_rect[i].w;
				s.h=SDLscreen_rect[i].h;

				SDL_BlitSurface(SDLscreen[i],&s,SDLdisplay,&SDLscreen_rect[i]);
			}
		}
	}

	/* update the sprite system */
	if(SDLupdatesprite!=0){
		if(SDLupdatesprite==2)SDLupdatesprite=0;
		for (iz=1;iz<SDLlastsprite;iz++){
			i=SDLspritez[iz];
			if (SDLspritelive[i]==1){


				d.x=SDLspritex[i];
				d.y=SDLspritey[i];
				d.w=MIN(SDLimageCC[SDLspritefr[i]]->w,(SDLspriteclip.w+SDLspriteclip.x-d.x));
				d.h=MIN(SDLimageCC[SDLspritefr[i]]->h,(SDLspriteclip.h+SDLspriteclip.y- d.y));

				if (d.x <SDLspriteclip.x ){
					s.x=0-(d.x-SDLspriteclip.x);
					d.x=d.x+s.x;
				}
				else{
					s.x=0;
				}
				if (d.y < SDLspriteclip.y){
					s.y=0-(d.y-SDLspriteclip.y);
					d.y=d.y+s.y;
				}
				else{
					s.y=0;
				}

				s.w= d.w - s.x;
				s.h= d.h - s.y;

				//no check: we are in critical mission real time
				if(d.x<SDLspriteclip.w+SDLspriteclip.x)
					if(d.y<SDLspriteclip.h+SDLspriteclip.y)
						SDL_BlitSurface(SDLimageCC[SDLspritefr[i]], &s, SDLdisplay, &d );


			}//end if
		}//end for


	}//end if
	/***********************/

	/* update the display system on sprites*/

	if (SDLdualplayfield!=0){
		for (iz=0;iz<SDLlastscreen;iz++){
			i=SDLscreen_z[iz];
			if (SDLscreen_live[i]==1){
				if ((SDLscreen_flag[i] & 1)==1 ){
					s.x=SDLoffx[i];
					s.y=SDLoffy[i];
					s.w=SDLscreen_rect[i].w;
					s.h=SDLscreen_rect[i].h;

					SDL_BlitSurface(SDLscreen[i],&s,SDLdisplay,&SDLscreen_rect[i]);
				}
			}
		}
	}
	/***********************/


	/* screen debug */

	if (SDLscreen_live[8]==1){
	    if(cursore_state[8]>0) {
		if (cursore_state[8]==1){
		    SDLcursore_preserve[8] = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_HWACCEL, XPRINT_SIZE,PRINT_SIZE*2,32,0,0,0,0);
		    if(SDLcursore_preserve[8]  == NULL) {
			error_description="SDLengine error: CreateRGBSurface failed ";
			error_type=1;
			SDLerr(stderr, "SDLengine error: CreateRGBSurface failed: %s\n", SDL_GetError());
			return -1;
		    }
		    cursore_state[8]=2;
		}

		if (cursore_state[8]>2){
		    SDL_FreeSurface(SDLcursore_preserve[8]);
		    cursore_state[8]=0;
		}
		if(cursore_state[8]==2) {
		    oldstx[8]=stx[8];
		    oldsty[8]=sty[8];

		    //print the textprint cursor and  update the frame animation
		    d.x=oldstx[8]* XPRINT_SIZE;
		    d.y=oldsty[8]* PRINT_SIZE;
		    d.w=XPRINT_SIZE;
		    d.h=PRINT_SIZE*2;
		    s.x=0;
		    s.y=0;
		    s.w= XPRINT_SIZE;
		    s.h= PRINT_SIZE*2;
		    //preserve cursor background in cursor 0 anim
		    SDL_BlitSurface( SDLscreen[8], &d, SDLcursore_preserve[8], &s);

		    SDL_BlitSurface(SDLcursore[cursore_anim[8]], &s, SDLscreen[8], &d );

		    cursore_anim[8]++;
		    if (cursore_anim[8]>14)cursore_anim[8]=0;
		}
	    }

	    s.x=SDLoffx[8];
	    s.y=SDLoffy[8];
	    s.w=SDLscreen_rect[8].w;
	    s.h=SDLscreen_rect[8].h;
	    SDL_BlitSurface(SDLscreen[8],&s,SDLdisplay,&SDLscreen_rect[8]);
	}




	/* fps system */
	if(SDLfps_flag!=0){
	    if (SDLfps_time < SDL_GetTicks()){
			SDLfps=SDLfps_count;
			SDLfps_count=0;
			SDLfps_time=SDL_GetTicks()+1000;
	    }
	    else
		SDLfps_count++;
	}


	/* update sprite 0 alias the mouse pointer */
	if (SDLspritelive[0]==1){
	    d.x=SDLspritex[0];
	    d.y=SDLspritey[0];
	    d.w=MIN(SDLimageCC[SDLspritefr[0]]->w,(SDLspriteclip.w+SDLspriteclip.x-d.x));
	    d.h=MIN(SDLimageCC[SDLspritefr[0]]->h,(SDLspriteclip.h+SDLspriteclip.y- d.y));

	    if (d.x <SDLspriteclip.x ){
		s.x=0-(d.x-SDLspriteclip.x);
		d.x=d.x+s.x;
	    }
	    else{
		s.x=0;
	    }
	    if (d.y < SDLspriteclip.y){
		s.y=0-(d.y-SDLspriteclip.y);
		d.y=d.y+s.y;
	    }
	    else{
		s.y=0;
	    }

	    s.w= d.w - s.x;
	    s.h= d.h - s.y;

	    //no check: we are in critical mission real time

	    if(d.x<SDLspriteclip.w+SDLspriteclip.x)
		if(d.y<SDLspriteclip.h+SDLspriteclip.y)
		    SDL_BlitSurface(SDLimageCC[SDLspritefr[0]], &s, SDLdisplay, &d );


	}//end if


	SDL_Flip(SDLdisplay);


	// restore the background of bobs
	if (SDLupdatebob!=0){
		if (SDLupdatebob ==2)SDLupdatebob=0;
			//restore the background if exist
			for (iz=0;iz<SDLlastbob;iz++){
			    i=SDLbobz[iz];
			    if (SDLboblive[i]==1){

				if (SDLbobback[i]!=NULL){
					d.x=SDLbobxold[i];
					d.y=SDLbobyold[i];
					d.w=SDLbobback[i]->w;
					d.h=SDLbobback[i]->h;

					s.x=0;
					s.y=0;
					s.w= d.w;
					s.h= d.h;
					SDL_BlitSurface(SDLbobback[i], &s, SDLscreen[SDLbobscreen[i]], &d );
				}

			    }
			    else{
				if (SDLbobback[i]!=NULL){

					d.x=SDLbobxold[i];
					d.y=SDLbobyold[i];
					d.w=SDLbobback[i]->w;
					d.h=SDLbobback[i]->h;

					s.x=0;
					s.y=0;
					s.w= d.w;
					s.h= d.h;

					SDL_BlitSurface(SDLbobback[i], &s, SDLscreen[SDLbobscreen[i]], &d );
					SDL_FreeSurface(SDLbobback[i]);
					SDLbobback[i]=NULL;
					SDLbobscreen[i]=-1;
				}

			}
		}//end for
	    }//endif

	vbl=0;
	}
	    for(i=0;i<=SDLlastscreen;i++){
		    if(cursore_state[i]==2) {
			//print the textprint cursor 0
			d.x=(oldstx[i]*XPRINT_SIZE);
			d.y=oldsty[i]*(PRINT_SIZE+1);
			d.w=XPRINT_SIZE;
			d.h=PRINT_SIZE;
			s.x=0;
			s.y=0;
			s.w= XPRINT_SIZE;
			s.h= PRINT_SIZE*2;
			SDL_BlitSurface(SDLcursore_preserve[i], &s, SDLscreen[i], &d );
			//SDL_FillRect( SDLcursore_preserve[i],NULL,colorkey);
			//SDL_BlitSurface(SDLcursore[0], &s, SDLscreen[i], &d );
		    }
	    }
		/* cursore debug screen */
		if(cursore_state[8]==2) {
			//print the textprint cursor 0
			d.x=oldstx[8]*XPRINT_SIZE;
			d.y=oldsty[8]*(PRINT_SIZE+1);
			d.w=XPRINT_SIZE;
			d.h=PRINT_SIZE*2;
			s.x=0;
			s.y=0;
			s.w= XPRINT_SIZE;
			s.h= PRINT_SIZE*2;
			SDL_BlitSurface(SDLcursore_preserve[8], &s, SDLscreen[8], &d );
			//SDL_FillRect( SDLcursore_preserve[i],NULL,0);
			//SDL_BlitSurface(SDLcursore[0], &s, SDLscreen[i], &d );
		    }


	return 0;
}
//_______________________________________________________________________________________________________________________

//autoback(m)								: enable / disable automatic screenswap  m=0 disable m>0 wait m milliseconds and perform screenswap m<0 perform the invocate in code screenswap after m milliseconds
int autoback( int m)
{
	if (m!=-1){
		SDLautoback=m;
		if (m>0)
			SDLautobacktime=chrono()+m;
	}
	return SDLautoback;
}
//_______________________________________________________________________________________________________________________

//dualplayfield(m)							: set/unset automatic update of a screen upper sprite -1 return state
int dualplayfield(int m)
{
	if (m!=-1){
		SDLdualplayfield=m;
		if (autotimer()!=0)return -1;
		return 0;
	}
	else
		return SDLdualplayfield;

}
//_______________________________________________________________________________________________________________________

//waitvbl								: wait automatic screenswap
int waitvbl()
{
	if (autoback(-1)>0){

		vbl=1;
		while(vbl!=0){
			SDL_Delay(5);
			if (autotimer()!=0)return -1;
			}
	}
	return 0;
}
//_______________________________________________________________________________________________________________________

//fps(n)								: set/unset or return (with -1) the current frame rate counter (0/1/-1)
int fps(int n)
{
    if (n==-1)
		return SDLfps;
    else{
		SDLfps_flag=n;
		SDLfps_count=0;
		SDLfps=0;
		SDLfps_time=SDL_GetTicks()+1000;
    }
    return 0;
}
