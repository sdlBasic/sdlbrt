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

// KEYBOARD
//_________________________________________________________________________________________________________________________

//key(keycode)								: return 1 if is press the key keycode
int key (int keycode)
{
	Uint8 *keystate;

	if (keycode<1 ||keycode>512){
	    error_description="SDLengine error - key: invalid keycode value ";
	    error_type=1;
	    SDLerr(stderr, "SDLengine error- key: %d is an invalid keycode value", keycode);
	    return -1;
	}
	if (autotimer()!=0)return -1;
	getevent();
	keystate = SDL_GetKeyState(NULL);
	if (keystate[keycode])return 1;
	return 0;
}
//_______________________________________________________________________________________________________________________

//inkey									: return ascii code of key press
int inkey()
{
	if (autotimer()!=0)return -1;
	getevent();
	return lastkey;
}
//_______________________________________________________________________________________________________________________

//waitkey(keycode)							: wait a key pression (-1 =any key)
int waitkey(int keycode)
{
	if (keycode==0)
		while(inkey()==0){
			SDL_Delay(5);
			if (autotimer()!=0)return -1;
		}
	else
		while(inkey()!=keycode){
			SDL_Delay(5);
			if (autotimer()!=0)return -1;
		}
	return 0;
}
