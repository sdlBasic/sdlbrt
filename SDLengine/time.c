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

// TIME
//_________________________________________________________________________________________________________________________

//waitTime(t)								: wait t milliseconds
int waitTime(int t)
{
	 Uint32 ticks;
	ticks=SDL_GetTicks()+t;
	while(ticks>SDL_GetTicks()){
		SDL_Delay(5);
		getevent();
		if (stopkey()==-1)return -1;
	if (autotimer()!=0)return -1;
	}
	return 0;
}
//_________________________________________________________________________________________________________________________

//timer									: return the current tick
int chrono()
{
	 Uint32 ticks;
	ticks=SDL_GetTicks();
	return ticks;
}
//_________________________________________________________________________________________________________________________
