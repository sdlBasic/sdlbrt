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

//GRAPHICS
//_________________________________________________________________________________________________________________________

//rgb(r,g,b)								: return current color in Uint32 format
int rgb(int colR,int colG,int colB)
{
    int c;
    c=colB + (colG * 256)+(colR*256*256);
    return c;
}
//_________________________________________________________________________________________________________________________

//enablepalette(state=0|1|-1 disable|enable|check)   			: enable disable and check the palettemode in 8 bit display
int enablepalette(int state)
{
    int i;

    switch(state)
    {
	case 0:
	    if (enablePalette!=0)enablePalette=0;
	    break;
	case 1:
    	    if (enablePalette==0)
		enablePalette=1;
	    for(i=0;i<256;i++)
		color(i,Palette[i]);
	    break;
	default:
	    return enablePalette;
    }
    return 0;
}


//_________________________________________________________________________________________________________________________

//color (c,optional v)							: set  palette color c with value v se missing return the current color c
int color(int c,int v)
{
    SDL_Color c_color;
    if (v !=-1 ){
	if (c<0)return -1;
	if (c>255)return -1;
	Palette[c]=v;

	if (enablePalette!=0){
	    c_color.b = v & 255;
	    c_color.g =( v / 256) & 255 ;
	    c_color.r =( v / (256*256)) & 255;

	    /* Set palette */
	    SDL_SetPalette(SDLdisplay, SDL_LOGPAL|SDL_PHYSPAL, &c_color, c, 1);
	}
    return 0;
    }
    else{
	return Palette[c];
    }
}
//_________________________________________________________________________________________________________________________

//colorcycling(s,e,d=0|1,delay)			: move the palettecolor one color forward or back work only in 8bit display

int colorcycling(int s,int e,int d,int delay)
{
    if (s==-1){
	colorcycling_delay=0;
	return 0;
    }
    if (e>256)e=256;
    if (s<0)s=0;

    colorcycling_s=s;
    colorcycling_e=e;
    colorcycling_d=d;
    colorcycling_delay=delay;
    colorcycling_next=delay+SDL_GetTicks();

    if (delay==0)colorcyclinghandler();
    return delay;
}

void colorcyclinghandler()
{
    int s,e,d;
    SDL_Color colors[256];
    int i,c;

    s=colorcycling_s;
    e=colorcycling_e;
    d=colorcycling_d;

    if(d==0){
	c=Palette[s];
	for(i=s;i<=e;i++){
	    //color(i,Palette[i+1]);
	    colors[i].b = Palette[i+1] & 255;
	    colors[i].g =( Palette[i+1] / 256) & 255 ;
	    colors[i].r =( Palette[i+1] / (256*256)) & 255;
	    Palette[i]=	Palette[i+1];
	}
	//color(e,c);
	colors[e].b = c & 255;
	colors[e].g =( c / 256) & 255 ;
	colors[e].r =( c / (256*256)) & 255;
	Palette[e]=c;
    }
    else{
	c=Palette[e];
	for(i=e;i>=s;i--){
	    //color(i,Palette[i-1]);
	    colors[i].b = Palette[i-1] & 255;
	    colors[i].g =( Palette[i-1] / 256) & 255 ;
	    colors[i].r =( Palette[i-1] / (256*256)) & 255;
	    Palette[i]=	Palette[i-1];
	}
	//color(s,c);
	colors[s].b = c & 255;
	colors[s].g =( c / 256) & 255 ;
	colors[s].r =( c / (256*256)) & 255;
	Palette[s]=c;
    }
    /* Set palette */
    SDL_SetPalette(SDLdisplay, SDL_LOGPAL|SDL_PHYSPAL, &colors[s], s, e-s);

    colorcycling_next=colorcycling_delay+chrono();
}

//_________________________________________________________________________________________________________________________

//ink(c)								: select the current color in Uint32 format
int ink( int c)
{
    if (c==-1){
	return (Uint32)SDL_MapRGB(SDLdisplay->format,SDLcol.r,SDLcol.g,SDLcol.b);
    }
    else{
	SDLcol.b = c & 255;
	SDLcol.g =( c / 256) & 255 ;
	SDLcol.r =( c / (256*256)) & 255;
    }
    return 0;
}
//_______________________________________________________________________________________________________________________

//point(x,y)								: return the color of x,y point
int point(int x,int y)
{
	Uint32 r;
    	if (SDL_MUSTLOCK(SDLscreen[c_screen]))
		SDL_LockSurface(SDLscreen[c_screen]);

	r=getpixel(SDLscreen[c_screen],x,y);

    	if (SDL_MUSTLOCK(SDLscreen[c_screen]))
		SDL_UnlockSurface(SDLscreen[c_screen]);

	return rrgb(r);


}
//_______________________________________________________________________________________________________________________

//dot(x,y)								: write x,y point with a current color
int dot(int x,int y)
{

    if (SDL_MUSTLOCK(SDLscreen[c_screen]) )
	    SDL_LockSurface(SDLscreen[c_screen]);

	putpixel( SDLscreen[c_screen], x, y,(Uint32)SDL_MapRGB(SDLdisplay->format,SDLcol.r,SDLcol.g,SDLcol.b));
	if (SDL_MUSTLOCK(SDLscreen[c_screen]) )
	    SDL_UnlockSurface(SDLscreen[c_screen]);

	if (autotimer()!=0)return -1;
	return 0;
}
//_______________________________________________________________________________________________________________________

//dot_ex(x,y,c)								: write x,y point with a c color
int dot_ex(int x,int y,int c)
{
	ink(c);
	if (autotimer()!=0)return -1;
	return dot(x,y);
}
//_______________________________________________________________________________________________________________________

//line(x,y,x1,y1)							: write a line
int line(int x,int y,int x1,int y1)
{
		if (SDL_MUSTLOCK(SDLscreen[c_screen]) )
			SDL_LockSurface(SDLscreen[c_screen]);

		draw_line(SDLscreen[c_screen],x,y,x1,y1,(Uint32)SDL_MapRGB(SDLdisplay->format,SDLcol.r,SDLcol.g,SDLcol.b));

		if (SDL_MUSTLOCK(SDLscreen[c_screen]) )
			SDL_UnlockSurface(SDLscreen[c_screen]);

	if (autotimer()!=0)return -1;
	return 0;
}
//_______________________________________________________________________________________________________________________


//box(x,y,x1,y1)							: write a empty rettangle
int box(int x,int y,int x1,int y1)
{
    int tmp;
	if (SDL_MUSTLOCK(SDLscreen[c_screen]))
		SDL_LockSurface(SDLscreen[c_screen]);

	if (x1<x){
	    tmp=x1;
	    x1=x;
	    x=tmp;
	}
	if (y1<y){
	    tmp=y1;
	    y1=y;
	    y=tmp;
	}

	draw_box(SDLscreen[c_screen],x,y,x1,y1,(Uint32)SDL_MapRGB(SDLdisplay->format,SDLcol.r,SDLcol.g,SDLcol.b));

	if (SDL_MUSTLOCK(SDLscreen[c_screen]))
		SDL_UnlockSurface(SDLscreen[c_screen]);

	if (autotimer()!=0)return -1;
	return 0;
}
//_______________________________________________________________________________________________________________________

//bar(x,y,x1,y1)							: write a fill rettangle
int bar(int x,int y,int x1,int y1)
{
	SDL_Rect d;
	int tmp;

	if (x1<x){
	    tmp=x1;
	    x1=x;
	    x=tmp;
	}
	if (y1<y){
	    tmp=y1;
	    y1=y;
	    y=tmp;
	}

	d.x=x;
	d.y=y;
	d.w=x1-x+1;
	d.h=y1-y+1;


    SDL_FillRect (SDLscreen[c_screen], &d,(Uint32)SDL_MapRGB(SDLdisplay->format,SDLcol.r,SDLcol.g,SDLcol.b));

    if (autotimer()!=0)return -1;

    return 0;
}
//_______________________________________________________________________________________________________________________

//rectangle(x,y,w,h,mode)						: write a rettangle w and h are the sizes mode=0 empty 1=filled

int rectangle(int x,int y,int w,int h,int mode)
{
    switch(mode){
	case 1:
	    return bar(x,y,x+w,y+h);
	    break;

	default:
	    return box(x,y,x+w,y+h);
	    break;

    }

}

//_______________________________________________________________________________________________________________________

//circle(x,y,r)								: write a circle
int circle(int x,int y,int r)
{

	if (SDL_MUSTLOCK(SDLscreen[c_screen]))
		SDL_LockSurface(SDLscreen[c_screen]);

	draw_circle(SDLscreen[c_screen],x,y,r,(Uint32)SDL_MapRGB(SDLdisplay->format,SDLcol.r,SDLcol.g,SDLcol.b));

	if (SDL_MUSTLOCK(SDLscreen[c_screen]))
		SDL_UnlockSurface(SDLscreen[c_screen]);

	if (autotimer()!=0)return -1;
	return 0;
}
//_______________________________________________________________________________________________________________________

//fillcircle(x,y,r)							: write a fill circle
int fillcircle(int x,int y,int r)
{
	if (SDL_MUSTLOCK(SDLscreen[c_screen]))
		SDL_LockSurface(SDLscreen[c_screen]);

	draw_fillcircle(SDLscreen[c_screen],x,y,r,(Uint32)SDL_MapRGB(SDLdisplay->format,SDLcol.r,SDLcol.g,SDLcol.b));

	if (SDL_MUSTLOCK(SDLscreen[c_screen]))
		SDL_UnlockSurface(SDLscreen[c_screen]);

	if (autotimer()!=0)return -1;
	return 0;
}
//_______________________________________________________________________________________________________________________

//ellipse(x,y,rx,ry)							: write a ellipse
int ellipse(int x,int y,int rx,int ry)
{
	if (SDL_MUSTLOCK(SDLscreen[c_screen]))
		SDL_LockSurface(SDLscreen[c_screen]);

	draw_ellipse(SDLscreen[c_screen],x,y,rx,ry,(Uint32)SDL_MapRGB(SDLdisplay->format,SDLcol.r,SDLcol.g,SDLcol.b));

	if (SDL_MUSTLOCK(SDLscreen[c_screen]))
		SDL_UnlockSurface(SDLscreen[c_screen]);

	if (autotimer()!=0)return -1;
	return 0;
}
//_______________________________________________________________________________________________________________________

//fillellipse(x,y,rx,ry)						: write a fill ellipse
int fillellipse(int x,int y,int rx,int ry)
{
	if (SDL_MUSTLOCK(SDLscreen[c_screen]))
		SDL_LockSurface(SDLscreen[c_screen]);

	draw_fillellipse(SDLscreen[c_screen],x,y,rx,ry,(Uint32)SDL_MapRGB(SDLdisplay->format,SDLcol.r,SDLcol.g,SDLcol.b));

	if (SDL_MUSTLOCK(SDLscreen[c_screen]))
		SDL_UnlockSurface(SDLscreen[c_screen]);

	if (autotimer()!=0)return -1;
	return 0;
}
//_______________________________________________________________________________________________________________________

//paint(x,y)								: fill a close area
int paint(int x,int y)
{
	char *paintmap;
	int xstart,ystart;
	int src_col,col;
	char pm;




	if (SDL_MUSTLOCK(SDLscreen[c_screen]))
		SDL_LockSurface(SDLscreen[c_screen]);

	paintmap= malloc(screenwidth()*screenheight());

	xstart=x;
	ystart=y;
	src_col=getpixel(SDLscreen[c_screen],x,y);//point(x,y);
	putpixel(SDLscreen[c_screen],x,y,(Uint32)SDL_MapRGB(SDLdisplay->format,SDLcol.r,SDLcol.g,SDLcol.b));//dot(x,y);
	col=getpixel(SDLscreen[c_screen],x,y);//point(x,y);
    pm=2;
    if (col==src_col)return -1;

    while(0==0) {
	//if (point(x,y)==src_col) {
	if (getpixel(SDLscreen[c_screen],x,y)== src_col) {
	putpixel(SDLscreen[c_screen],x,y,(Uint32)SDL_MapRGB(SDLdisplay->format,SDLcol.r,SDLcol.g,SDLcol.b));//dot(x,y);
		paintmap[y*screenwidth()+x]=pm;
    	}

	//if (point(x+1,y)==src_col && (x+1) < screenwidth()) {
	if (getpixel(SDLscreen[c_screen],x+1,y)==src_col && (x+1) < screenwidth()) {
		    x=x+1;
		    pm=1;
		}
	//else if (point(x-1,y)==src_col && (x-1) > 0 ) {
	else if (getpixel(SDLscreen[c_screen],x-1,y)==src_col && (x-1) >= 0 ) {
		    x=x-1;
		    pm=2;
		}
	//else if (point(x,y+1)==src_col && (y+1) < screenheight()) {
	else if (getpixel(SDLscreen[c_screen],x,y+1)==src_col && (y+1) < screenheight()) {
		    y=y+1;
		    pm=3;
		}
	//else if (point(x,y-1)==src_col && (y-1) > 0) {
	else if (getpixel(SDLscreen[c_screen],x,y-1)==src_col && (y-1) >= 0) {
		    y=y-1;
		    pm=4;
		}
	else
		{
		if (x==xstart && y==ystart)break;

		if (paintmap[y*screenwidth()+x]==1)
			x=x-1;
		else if (paintmap[y*screenwidth()+x]==2)
			x=x+1;
		else if (paintmap[y*screenwidth()+x]==3)
			y=y-1;
		else if (paintmap[y*screenwidth()+x]==4)
			y=y+1;
		}
	}
	free(paintmap);

	if (SDL_MUSTLOCK(SDLscreen[c_screen]) )
		SDL_UnlockSurface(SDLscreen[c_screen]);

	if (autotimer()!=0)return -1;
    return 0;
}
//_______________________________________________________________________________________________________________________

//triangle(xa,ya,xb,yb,xc,yc)					: draw a filled triangle
int triangle(int x1,int y1,int x2,int y2,int x3,int y3)
{
    int c,x,y;
    int dx,dy;
    double sl;

    //*

    dx = x2 - x1;  // change in x
    dy = y2 - y1;  // change in y

    sl = (double)dy / dx;

    if (abs(dx) >= abs(dy)) {
	// draw left/right - right/left
	c = (x1 <= x2) ? 1 : -1;
	for (x = x1; x != x2 + c; x += c) {
	    y = y1 + (int)( (x - x1) * sl + 0.5 );
	if (y>=0)
	    line(x,y,x3,y3);
	}
    }
    else
    {
	// draw top/bottom - bottom/top
	c = (y1 <= y2) ? 1 : -1;
	for (y = y1; y != y2 + c; y += c) {
	    x =(int) x1 + (int)( (y - y1) / sl + 0.5 );
	    line(x,y,x3,y3);
	}
    }

    dx = x3 - x2;  // change in x
    dy = y3 - y2;  // change in y

    sl = (double)dy / dx;

    if (abs(dx) >= abs(dy)) {
	// draw left/right - right/left
	c = (x2 <= x3) ? 1 : -1;
	for (x = x2; x != x3 + c; x += c) {
	    y = y2 + (int)( (x - x2) * sl + 0.5 );
	if (y>=0)
	    line(x,y,x1,y1);
	}
    }
    else
    {
	// draw top/bottom - bottom/top
	c = (y2 <= y3) ? 1 : -1;
	for (y = y2; y != y3 + c; y += c) {
	    x =(int) x2 + (int)( (y - y2) / sl + 0.5 );
	    line(x,y,x1,y1);
	}
    }

    dx = x1 - x3;  // change in x
    dy = y1 - y3;  // change in y

    sl = (double)dy / dx;

    if (abs(dx) >= abs(dy)) {
	// draw left/right - right/left
	c = (x3 <= x1) ? 1 : -1;
	for (x = x3; x != x1 + c; x += c) {
	    y = y3 + (int)( (x - x3) * sl + 0.5 );
	if (y>=0)
	    line(x,y,x2,y2);
	}
    }
    else
    {
	// draw top/bottom - bottom/top
	c = (y3 <= y1) ? 1 : -1;
	for (y = y3; y != y1 + c; y += c) {
	    x =(int) x3 + (int)( (y - y3) / sl + 0.5 );
	    line(x,y,x2,y2);
	}
    }


    //*/
    if (autotimer()!=0)return -1;
    return 0;
}
//_______________________________________________________________________________________________________________________

