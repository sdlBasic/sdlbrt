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

// SPRITE SYSTEM
//_________________________________________________________________________________________________________________________

//spriteclip(x,y,w,h)							: set the visibilty area of sprites
int spriteclip(int x,int y,int w,int h)
{
	SDLspriteclip.x=x;
	SDLspriteclip.y=y;
	SDLspriteclip.w=w;
	SDLspriteclip.h=h;
	return 0;
}
//__________________________________________________________________________________________________________________________

//sprite(n,x,y,fr)							: set or move the sprite n at x,y with image fr
int sprite(int n,int x,int y,int fr)
{
	if (n>NUM_SPRITES || n<0 ){
		error_description="SDLengine error - sprite: invalid sprite number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - sprite: %d is an invalid sprite number", n);
		return -1;
	}
	if (SDLimageCC[fr]!=NULL) {
		SDLspritelive[n]=1;
		SDLspritex[n]=x-SDL_hsx[fr];
		SDLspritey[n]=y-SDL_hsy[fr];
		SDLspritefr[n]=fr;

	}
	else {

		error_description="SDLengine error - sprite: specified image slot is empty ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - sprite: image slot %d is empty", n);
		return -1;
	}
	if (SDLlastsprite<=n)SDLlastsprite=n+1;


	if (autotimer()!=0)return -1;
	return 0;

}
//__________________________________________________________________________________________________________________________

//deletesprite(n)							: unset sprite n
int deletesprite(int n)
{
	if (n>NUM_SPRITES || n<0 ){
		error_description="SDLengine error - deleteSprite: invalid sprite number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - deleteSprite: %d is an invalid sprite number", n);
		return -1;
	}

	SDLspritelive[n]=0; //morto!!
	SDLspritex[n]=0;
	SDLspritey[n]=0;
	SDLspritefr[n]=-1;

	if (SDLlastsprite==n+1)
	    while (SDLspritelive[SDLlastsprite-1]==0){
		spritez(SDLlastsprite-1,SDLlastsprite-1);
		SDLlastsprite--;
	    }
	if (autotimer()!=0)return -1;
	return SDLspritelive[n];
}
//__________________________________________________________________________________________________________________________

//xsprite(n)								: return the x of sprite n
int xsprite(int n)
{
	if (n>NUM_SPRITES || n<0 ){
		error_description="SDLengine error - spriteX: invalid sprite number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - spriteX: %d is an invalid sprite number ", n);
		return -1;
	}
	if (autotimer()!=0)return -1;
		return SDLspritex[n]+SDL_hsx[SDLspritefr[n]];
}
//_________________________________________________________________________________________________________________________

//ysprite(n)								: return the y of sprite n
int ysprite(int n)
{
	if (n>NUM_SPRITES || n<0 ){
		error_description="SDLengine error - spriteY: invalid sprite number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - spriteY: %d is an invalid sprite number ", n);
		return -1;
	}
	if (autotimer()!=0)return -1;
		return SDLspritey[n]+SDL_hsy[SDLspritefr[n]];
}
//_________________________________________________________________________________________________________________________

//spritewidth(n)							: return the width of sprite n
int spritewidth(int n)
{
	if (n>NUM_SPRITES || n<0 ){
		error_description="SDLengine error - spriteWidth: invalid sprite number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - spriteWidth: %d is an invalid sprite number ", n);
		return -1;
	}
	if (autotimer()!=0)return -1;
	if (SDLspritefr[n]!=-1)
		return SDLimageCC[SDLspritefr[n]]->w;
	return 0;
}
//_________________________________________________________________________________________________________________________

//spriteheight(n)							: return the height of sprite n
int spriteheight(int n)
{
	if (n>NUM_SPRITES || n<0 ){
		error_description="SDLengine error - spriteHeight: invalid sprite number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - spriteHeight: %d is an invalid sprite number ", n);
		return -1;
	}
	if (autotimer()!=0)return -1;
	if (SDLspritefr[n]!=-1)
		return SDLimageCC[SDLspritefr[n]]->h;
	return 0;
}
//_________________________________________________________________________________________________________________________

//frsprite(n)								: return the frame of sprite n
int frsprite(int n)
{
	if (n>NUM_SPRITES || n<0 ){
		error_description="SDLengine error - spriteImage: invalid sprite number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - spriteImage: %d is an invalid sprite number ", n);
		return -1;
	}
	if (autotimer()!=0)return -1;
		return SDLspritefr[n];
}
//_________________________________________________________________________________________________________________________

//livesprite(n)								: return 1 if sprite n is "live"
int livesprite(int n)
{
	if (n>NUM_SPRITES || n<0 ){
		error_description="SDLengine error - spriteExist: invalid sprite number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - spriteExist: %d is an invalid sprite number ", n);
		return -1;
	}
	if (autotimer()!=0)return -1;
		return SDLspritelive[n];
}
//_________________________________________________________________________________________________________________________

//spritehit(n,x)							: return 1 if sprite n have a collission with sprite x if x=-1 with any
int spritehit(int n,int x)
{
    int xa1,ya1,xa2,ya2;
    int xb1,yb1,xb2,yb2;
	int i,ret;

	if (n>NUM_SPRITES || n<0 ){
		error_description="SDLengine error - spriteHit: invalid sprite number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - spriteHit: %d is an invalid sprite number ", n);
		return -1;
	}

    xa1=SDLspritex[n];
    ya1=SDLspritey[n];
    xa2=xa1+spritewidth(n);
    ya2=ya1+spriteheight(n);

    if (x!=-1){
		if (x>NUM_SPRITES || x<0 ){
		    error_description="SDLengine error - spriteHit: invalid sprite number for collision target";
		    error_type=1;
		    SDLerr(stderr, "SDLengine error - spriteHit: collision target sprite %d is an invalid sprite number ", x);
		return -1;
		}

		if (SDLspritelive[x]==1){
			xb1=SDLspritex[x];
			yb1=SDLspritey[x];
			xb2=xb1+spritewidth(x);
			yb2=yb1+spriteheight(x);

			if (xb2<xa1)return 0;
			if (yb2<ya1)return 0;
			if (xa2<xb1)return 0;
			if (ya2<yb1)return 0;
			//return 1;
			return hit_pixelperfect(SDLimageCC[SDLspritefr[n]],xa1,ya1,xa2,ya2,SDLimageCC[SDLspritefr[x]],xb1,yb1,xb2,yb2);
		}

    }
    else{
		for (i=0;i<NUM_SPRITES;i++){
			if (n != i){
				if (SDLspritelive[i]==1){
					xb1=SDLspritex[i];
					yb1=SDLspritey[i];
					xb2=xb1+spritewidth(i);
					yb2=yb1+spriteheight(i);

					ret=1;
					if (xb2<xa1)ret=0;
					if (yb2<ya1)ret=0;
					if (xa2<xb1)ret=0;
					if (ya2<yb1)ret=0;
					//if (ret==1)return 1;
					if (ret==1)return hit_pixelperfect(SDLimageCC[SDLspritefr[n]],xa1,ya1,xa2,ya2,SDLimageCC[SDLspritefr[i]],xb1,yb1,xb2,yb2);

				}
			}
		}

    }
    return 0;
}
//_________________________________________________________________________________________________________________________

// spritez(n,z)								: set the zorder position of sprite if z =-1 report actual z position
int spritez(int n,int z)
{

    int i,oldz;

    if (z>SDLlastsprite-1)z=SDLlastsprite-1;

    oldz=-1;
    for(i=0;i<SDLlastsprite;i++)
	if(SDLspritez[i]==n)oldz = i;
    if (oldz==-1)return -1;

    if (z==-1)
	return oldz;
    else{
	if (z==oldz)return 0;
	if (z>oldz){
	    for(i=oldz;i<=z-1;i++)
		SDLspritez[i]=SDLspritez[i+1];
	    SDLspritez[z]=n;

	}
	else{
    	    for(i=oldz;i>=z;i--)
		SDLspritez[i]=SDLspritez[i-1];
	    SDLspritez[z]=n;

	}
    }
    return 0;
}
//_________________________________________________________________________________________________________________________

//lastsprite								: return the last sprite active
int lastsprite()
{
    if (SDLlastsprite!=0)return SDLlastsprite-1;
	return SDLlastsprite;
}
//_________________________________________________________________________________________________________________________

//autoupdatesprite(m)							: set/ unset automatic sprites update at screenswap
int autoupdatesprite(int m)
{
	if (autotimer()!=0)return -1;
	SDLupdatesprite = m;
	return SDLupdatesprite;

}
//_________________________________________________________________________________________________________________________

//updatesprite								: manual sprites updates at next screenswap
int updatesprite()
{
	SDLupdatesprite = 2;
	if (autotimer()!=0)return -1;
	return SDLupdatesprite;

}
