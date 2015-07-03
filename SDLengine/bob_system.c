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

//BOB SYSTEM
//_________________________________________________________________________________________________________________________

//setbob(n,scr)								: set bob n at logic screen scr
int setbob(int n,int scr)
{
	if (n>NUM_BOBS || n<0){
		error_description="SDLengine error - setBob: invalid bob number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - setBob: invalid bob number");
		return -1;
	}
	SDLbobscreen[n]=scr;
	if (autotimer()!=0)return -1;
	 return 0;
}
//_________________________________________________________________________________________________________________________

//bob(n,x,y,fr)								: set or move bob n at x,y with frame fr
int bob(int n,int x,int y,int fr)
{
	if (n>NUM_BOBS || n<0){
		error_description="SDLengine error - bob: invalid bob number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - bob: invalid bob number");
		return -1;
	}

	if (SDLimageCC[fr]!=NULL){
		SDLboblive[n]=1;
		SDLbobx[n]=x-SDL_hsx[fr];
		SDLboby[n]=y-SDL_hsy[fr];
		SDLbobfr[n]=fr;
	}
	else {
		error_description="SDLengine error - bob: given image slot is empty ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - bob: image slot %d is empty", fr);
		return -1;
	}
	if (SDLbobscreen[n]==-1)SDLbobscreen[n]=c_screen;

	if (SDLlastbob<=n)SDLlastbob=n+1;


	if (autotimer()!=0)return -1;
	return 0;
}
//__________________________________________________________________________________________________________________________

//deletebob(n)								: unset bob n
int deletebob(int n)
{
	if (n>NUM_BOBS || n<0){
		error_description="SDLengine error - deleteBob: invalid bob number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - deleteBob: %d is an invalid bob number", n);
		return -1;
	}
	SDLboblive[n]=0; //morto!!
	SDLbobx[n]=0;
	SDLboby[n]=0;
	SDLbobfr[n]=-1;

	if (SDLlastbob==n+1)
	    while (SDLboblive[SDLlastbob-1]==0){
		bobz(SDLlastbob-1,SDLlastbob-1);
		SDLlastbob--;
	    }
	if (autotimer()!=0)return -1;
	return SDLboblive[n];
}
//__________________________________________________________________________________________________________________________

//xbob(n)								: return x of bob n
int xbob(int n)
{
	if (n>NUM_BOBS || n<0){
		error_description="SDLengine error - bobX: invalid bob number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - bobX: %d is an invalid bob number", n);
		return -1;
	}
	if (autotimer()!=0)return -1;
		return SDLbobx[n]-SDL_hsx[SDLbobfr[n]];
}
//_________________________________________________________________________________________________________________________

//ybob(n)								: return y of bob n
int ybob(int n)
{
	if (n>NUM_BOBS || n<0){
		error_description="SDLengine error - bobY: invalid bob number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - bobY: %d is an invalid bob number", n);
		return -1;
	}
	if (autotimer()!=0)return -1;
		return SDLboby[n]-SDL_hsy[SDLbobfr[n]];
}
//_________________________________________________________________________________________________________________________

//bobwidth(n)								: return width of bob n
int bobwidth(int n)
{
	if (n>NUM_BOBS || n<0){
		error_description="SDLengine error - bobWidth: invalid bob number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - bobWidth: %d is an invalid bob number", n);
		return -1;
	}
	if (autotimer()!=0)return -1;
	if (SDLbobfr[n]!=-1)
		return SDLimageCC[SDLbobfr[n]]->w;
	return 0;
}
//_________________________________________________________________________________________________________________________

//bobheight(n)								: return height of bob n
int bobheight(int n)
{
	if (n>NUM_BOBS || n<0){
		error_description="SDLengine error - bobHeight: invalid bob number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - bobHeight: %d is an invalid bob number", n);
		return -1;
	}
	if (autotimer()!=0)return -1;
	if (SDLbobfr[n]!=-1)
		return SDLimageCC[SDLbobfr[n]]->h;
	return 0;
}
//_________________________________________________________________________________________________________________________

//frbob(n)								: return the frame of bob n
int frbob(int n)
{
	if (n>NUM_BOBS || n<0){
		error_description="SDLengine error - bobImage: invalid bob number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - bobImage: %d is an invalid bob number", n);
		return -1;
	}
	if (autotimer()!=0)return -1;
		return SDLbobfr[n];
}
//_________________________________________________________________________________________________________________________

//livebob(n)								: return 1 if bob n is "live"
int livebob(int n)
{
	if (n>NUM_BOBS || n<0){
		error_description="SDLengine error - bobExist: invalid bob number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - bobExist: %d is an invalid bob number", n);
		return -1;
	}
	if (autotimer()!=0)return -1;
		return SDLboblive[n];
}
//_________________________________________________________________________________________________________________________

//bobhit(n,x)								: return 1 if bob n have a collision with bob x if x=-1 with any
int bobhit(int n,int x)
{
    int xa1,ya1,xa2,ya2;
    int xb1,yb1,xb2,yb2;
	int i,ret;

	if (n>NUM_BOBS || n<0){
		error_description="SDLengine error - bobHit: invalid bob number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - bobHit: %d is an invalid bob number", n);
		return -1;
	}

    xa1=SDLbobx[n];
    ya1=SDLboby[n];
    xa2=xa1+bobwidth(n);
    ya2=ya1+bobheight(n);

    if (x!=-1){
		if (x>NUM_BOBS || x<0){
		    error_description="SDLengine error - bobHit: invalid bob numberd as target ";
		    error_type=1;
		    SDLerr(stderr, "SDLengine error - bobHit: collision target bob %d is an invalid bob number", x);
		    return -1;
		}
		if (SDLboblive[x]==1){
			xb1=SDLbobx[x];
			yb1=SDLboby[x];
			xb2=xb1+bobwidth(x);
			yb2=yb1+bobheight(x);

			if (xb2<xa1)return 0;
			if (yb2<ya1)return 0;
			if (xa2<xb1)return 0;
			if (ya2<yb1)return 0;
			//return 1;
			return hit_pixelperfect(SDLimageCC[SDLbobfr[n]],xa1,ya1,xa2,ya2,SDLimageCC[SDLbobfr[x]],xb1,yb1,xb2,yb2);
		}

    }
    else{
		for (i=0;i<NUM_BOBS;i++){
			if (n != i){
				if (SDLboblive[i]==1){
					xb1=SDLbobx[i];
					yb1=SDLboby[i];
					xb2=xb1+bobwidth(i);
					yb2=yb1+bobheight(i);

					ret=1;
					if (xb2<xa1)ret=0;
					if (yb2<ya1)ret=0;
					if (xa2<xb1)ret=0;
					if (ya2<yb1)ret=0;
					//if (ret==1)return 1;
					if (ret==1)return hit_pixelperfect(SDLimageCC[SDLbobfr[n]],xa1,ya1,xa2,ya2,SDLimageCC[SDLbobfr[i]],xb1,yb1,xb2,yb2);
				}
			}
		}

    }
    return 0;
}

//_________________________________________________________________________________________________________________________

// bobz(n,z)								: set the zorder position of bob if z =-1 report actual z position
int bobz(int n,int z)
{

    int i,oldz;

    if (z>SDLlastbob-1)z=SDLlastbob-1;

    oldz=-1;
    for(i=0;i<SDLlastbob;i++)
	if(SDLbobz[i]==n)oldz = i;
    if (oldz==-1)return -1;

    if (z==-1)
	return oldz;
    else{
	if (z==oldz)return 0;
	if (z>oldz){
	    for(i=oldz;i<=z-1;i++)
		SDLbobz[i]=SDLbobz[i+1];
	    SDLbobz[z]=n;

	}
	else{
    	    for(i=oldz;i>=z;i--)
		SDLbobz[i]=SDLbobz[i-1];
	    SDLbobz[z]=n;

	}
    }
    return 0;
}
//_________________________________________________________________________________________________________________________

//lastbob								: return the last bob active
int lastbob()
{
    if (SDLlastbob!=0)return SDLlastbob-1;
	return SDLlastbob;
}
//_________________________________________________________________________________________________________________________

//autoupdatebob(m) 							: set/ unset automatic bobs update at screenswap
int autoupdatebob(int m)
{
	SDLupdatebob=m;
	if (autotimer()!=0)return -1;
	return SDLupdatebob;

}
//_________________________________________________________________________________________________________________________

//updatebob  								:  manual bobs updates at next screenswap
int updatebob()
{
	SDLupdatebob=2;
	if (autotimer()!=0)return -1;
	return SDLupdatebob;

}

