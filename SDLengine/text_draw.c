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

// TEXT DRAW
//_________________________________________________________________________________________________________________________

//text(x,y,s,text)							: print the text testo  on current screen with s size
int text ( int x, int y, int s, char *testo,int option)
{
	SDL_Rect d;
	int w,h;
	SDL_Color bg;


	if (fileExist(fontPath))
	    font = TTF_OpenFont(fontPath,s);
	else
	    font=NULL;

	if (font ==NULL) {
		error_description="SDLengine: Warning Can't open true type font ";
		error_type=1;
		SDLerr(stderr,"SDLengine: Warning Can't open true type font.  %s\n",SDL_GetError());
		return -1;
	}

	switch(option){
	    case 1:
		bg.b = paper_color & 255;
		bg.g =( paper_color / 256) & 255 ;
		bg.r =( paper_color / (256*256)) & 255;
		SDLtext = TTF_RenderUTF8_Shaded(font,testo,SDLcol,bg);
		break;
	    case 2:
		SDLtext = TTF_RenderUTF8_Blended(font,testo,SDLcol);
		break;
	    default:
		SDLtext = TTF_RenderUTF8_Blended(font,testo,SDLcol);//SOLID DOES NOT WORK NOW
		break;
	}

	TTF_SizeText(font, testo, &w, &h);

	d.x=x;
	d.y=y;
	d.w=w;
	d.h=h;

	SDL_BlitSurface(SDLtext, NULL, SDLscreen[c_screen], &d );
	SDL_FreeSurface(SDLtext);
	TTF_CloseFont(font);
	if (autotimer()!=0)return -1;
	return 0;
}
//_______________________________________________________________________________________________________________________

//setfont(path)								: select the font
int setfont(char *path)
{
	if (fileExist(path)) {


		fontPath=path;
	}
	else {
		error_description="SDLengine error: file not found ";
		error_type=1;
		SDLerr(stderr,"SDLengine error: file not found.  %s\n",SDL_GetError());
		return -1;
	}
	return 0;
}
//_______________________________________________________________________________________________________________________

//getfont()								: get the font selected
char *getfont()
{
	return fontPath;
}
//_______________________________________________________________________________________________________________________

//textrender(text,s,n)							: make an image slot n with the text  write with a current font and size s
int textrender (char *testo,int s,int n, int option)
{
	SDL_Color bg;
	int w,h;

	if (strlen(testo)==0)strcpy(testo," ");//bugfix if string are empty does not work


	if (n==-1)
		n=getfreeimage();

	if (n>NUM_IMAGES){
		error_description="SDLengine error - textRender: image number exceed maximum image bank number ";
		error_type=1;
		SDLerr(stderr,"SDLengine error - textRender: image %d exceed maximum image bank number", n);
		return -1;
	}

	if (fileExist(fontPath))
	    font = TTF_OpenFont(fontPath,s);
	else
	    font=NULL;
	if (font == NULL) {
		error_description="SDLengine error - textRender: Can't open true type font. Please verify installation";
		error_type=1;
		SDLerr(stderr,"SDLengine error - textRender: Can't open true type font. Please verify installation %s\n",SDL_GetError());
		return -1;
	}

	SDL_FreeSurface(SDLimage[n]);
	SDL_FreeSurface(SDLimageCC[n]);

	TTF_SizeText(font, testo, &w, &h);


    	switch(option){
	    case 1:
		bg.b = paper_color & 255;
		bg.g =( paper_color / 256) & 255 ;
		bg.r =( paper_color / (256*256)) & 255;
		SDLimage[n] = TTF_RenderUTF8_Shaded(font,testo,SDLcol,bg);
		SDLimageCC[n] = TTF_RenderUTF8_Shaded(font,testo,SDLcol,bg);
		break;
	    case 2:
		SDLimage[n] = TTF_RenderUTF8_Blended(font,testo,SDLcol);
		SDLimageCC[n] = TTF_RenderUTF8_Blended(font,testo,SDLcol);
		break;
	    default:
		SDLimage[n] = TTF_RenderUTF8_Blended(font,testo,SDLcol);//SOLID DOES NOT WORK NOW
		SDLimageCC[n] = TTF_RenderUTF8_Blended(font,testo,SDLcol);
		break;
	}

	if (SDLimage[n] ==NULL || SDLimageCC[n] ==NULL){
		error_description="SDLengine error - render failed";
		error_type=1;
		SDLerr(stderr,"SDLengine error - RenderFailed:  %s\n",SDL_GetError());
		return -1;
	}

	TTF_CloseFont(font);
	if (autotimer()!=0)return -1;
	return n;
}

