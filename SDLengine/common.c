/*
_________________________________________________________________________________________________________________________

    SDLengine core of sdlBasic
    common.c

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
#pragma GCC diagnostic ignored "-Wformat-security"

#include "SDLengine.h"


//________________________________________________________________________________________________________________________________________

// COMMON INTERNAL RUTINES
//________________________________________________________________________________________________________________________________________


//________________________________________________________________________________________________________________________________________

//stopkey					:terminate program if press ctrl+c
int stopkey()
{
    Uint8 *keystate;
    getevent();
    keystate = SDL_GetKeyState(NULL);

    if (keystate[306] && keystate[99]){
		error_description="ctrl+c pressed by the user\n";
		error_type=2;
		SDLerr(stderr,"%s",error_description);
	return -1;
    }
    return 0;
}
//________________________________________________________________________________________________________________________________________

//getevent					: eventhandling
int getevent()
{
	SDL_Event event;

	while ( SDL_PollEvent(&event) )
		{
		switch(event.type){
		  case SDL_QUIT:
			terminate();
			exit(2);
			return 0;
			break;

		  case SDL_KEYDOWN:

			lastkey = event.key.keysym.unicode;
			if (lastkey==0){
				switch(event.key.keysym.sym){

				case 127:
					lastkey=127;
					break;
				case 256:
					lastkey=48;
					break;
				case 257:
					lastkey=49;
					break;
				case 258:
					lastkey=50;
					break;
				case 259:
					lastkey=51;
					break;
				case 260:
					lastkey=52;
					break;
				case 261:
					lastkey=53;
					break;
				case 262:
					lastkey=54;
					break;
				case 263:
					lastkey=55;
					break;
				case 264:
					lastkey=56;
					break;
				case 265:
					lastkey=57;
					break;
				case 266:
					lastkey=46;
					break;
				case 267:
					lastkey=47;
					break;
				case 271:
					lastkey=13;
					break;
				default:
					lastkey=0;
					break;
				}
			}
			break;

		  case SDL_KEYUP :
			lastkey=0;
			break;
		}
	}
	SDL_PumpEvents();
	return 0;
}
//________________________________________________________________________________________________________________________________________

// autotimer 				: collaborative automatic multitasking
int autotimer()
{
    int i;
	/* autofade handler */
	for(i=0;i<NUM_SCREENS;i++){
	    if (fadedelay[i]!=0){
		if (SDL_GetTicks()>fadedelay[i]){
		    fadedelay[i]=SDL_GetTicks()+10;
		    if (fadeflag[i]>0)
			fadehandler(i);
		    if (crossfadeflag[i]>0)
			crossfadehandler(i);
		}
	    }
	}

	/* musicfade handler */
	if (fademusic_t>0)
		if (chrono()>fademusic_delay)
		    fademusichandler();

	/* colorcycling handler */
	if (colorcycling_delay>0)
		if (colorcycling_next<chrono() ){
			colorcyclinghandler();
		}

	/* autoback handler */
	if (SDLautoback>0)
	    if (chrono()>SDLautobacktime){
			if (screenswap()==-1)
				return -1;
		SDLautobacktime=chrono()+SDLautoback;
	}
	return 0;
}
//________________________________________________________________________________________________________________________________________
