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

//JOYSTICK
//_________________________________________________________________________________________________________________________

//numjoysticks 								: Count available joysticks.
int numjoysticks()
{
    return num_joystick;
}
//_________________________________________________________________________________________________________________________

//namejoystick(index)							: Get joystick name.
char *namejoystick(int index)
{
    return (char *)SDL_JoystickName(index);
}
//_________________________________________________________________________________________________________________________

//numaxesjoystick 							: Get the number of joystick axes
int numaxesjoystick(int index)
{
    int ret;
    SDL_JoystickUpdate();
    if (SDLjoy[index])
	ret= SDL_JoystickNumAxes(SDLjoy[index]);
    else
	ret=-1;
    return ret;
}
//_________________________________________________________________________________________________________________________

//numballsjoystick(i) 							: Get the number of joystick trackballs
int numballsjoystick(int index)
{
    int ret;
    SDL_JoystickUpdate();
    if (SDLjoy[index])
	ret= SDL_JoystickNumBalls(SDLjoy[index]);
    else
	ret=-1;
    return ret;

}
//_________________________________________________________________________________________________________________________

//numhatsjoystick(i) 							: Get the number of joystick hats
int numhatsjoystick(int index)
{
    int ret;
    SDL_JoystickUpdate();
    if (SDLjoy[index])
	ret= SDL_JoystickNumHats(SDLjoy[index]);
    else
	ret=-1;
    return ret;
}
//_________________________________________________________________________________________________________________________

//numbuttonsjoystick(i) 						: Get the number of joysitck buttons
int numbuttonsjoystick(int index)
{
    int ret;
    SDL_JoystickUpdate();
    if (SDLjoy[index])
	ret= SDL_JoystickNumButtons(SDLjoy[index]);
    else
	ret=-1;
    return ret;
}
//_________________________________________________________________________________________________________________________

//getaxisjoystick(i,a) 							: Get the current state of an axis
int getaxisjoystick(int index,int axis)
{
    int ret;
    SDL_JoystickUpdate();
    if (SDLjoy[index])
	ret= SDL_JoystickGetAxis(SDLjoy[index],axis);
    else
	ret=0;
    return ret;
}
//_________________________________________________________________________________________________________________________

//gethatjoystick(i,a) 							: Get the current state of a joystick hat
int gethatjoystick(int index,int hat)
{
    int ret;
    SDL_JoystickUpdate();
    if (SDLjoy[index])
	ret= SDL_JoystickGetHat(SDLjoy[index],hat);
    else
	ret=-1;
    return ret;
}
//_________________________________________________________________________________________________________________________

//getbuttonjoystick(i,a)						: Get the current state of a given button on a given joystick
int getbuttonjoystick(int index,int button)
{
    int ret;
    SDL_JoystickUpdate();
    if (SDLjoy[index])
	ret= SDL_JoystickGetButton(SDLjoy[index],button);
    else
	ret=-1;
    return ret;
}

//_________________________________________________________________________________________________________________________

//xgetballjoystick(i,a) 							: Get relative x trackball motion
int xgetballjoystick(int index,int ball)
{
    int x,y;
    int ret;
    SDL_JoystickUpdate();
    if (SDLjoy[index])
	ret= SDL_JoystickGetBall(SDLjoy[index],ball,&x,&y);
    else
	ret=-1;
    if (ret!=-1)
	return x;
    else
	return ret;
}

//_________________________________________________________________________________________________________________________

//ygetballjoystick(i,a) 							: Get relative y trackball motion
int ygetballjoystick(int index,int ball)
{
    int x,y;
    int ret;
    SDL_JoystickUpdate();
    if (SDLjoy[index])
	ret= SDL_JoystickGetBall(SDLjoy[index],ball,&x,&y);
    else
	ret=-1;
    if (ret!=-1)
	return y;
    else
	return ret;
}

//_________________________________________________________________________________________________________________________

//joy									: return joystick boolean coordinate
int joy(int index)
{
    int ret,tmp;
    if (index>=SDL_NumJoysticks())return -1;
    SDL_JoystickUpdate();
    ret=0;
    if (SDLjoy[index] && SDL_JoystickNumAxes(SDLjoy[index])>=2 ){
	tmp= SDL_JoystickGetAxis(SDLjoy[index],0);
	if (tmp<0)
	    ret+=1;
	if (tmp>0)
	    ret+=2;
	tmp= SDL_JoystickGetAxis(SDLjoy[index],1);
	if (tmp<0)
	    ret+=4;
	if (tmp>0)
	    ret+=8;
    }
    if (SDLjoy[index] && SDL_JoystickNumHats(SDLjoy[index])>0 ){
	ret+=SDL_JoystickGetHat(SDLjoy[index],0);
    }
    if (autotimer()!=0)return -1;
    return ret;
}
//_________________________________________________________________________________________________________________________

//bjoy									: return joystick buttons pressed in boolean expression
int bjoy(int index)
{
    int ret,i,a;
    if (index>=SDL_NumJoysticks())return emulate_bjoy(index);
    ret=0;
    a=1;
    SDL_JoystickUpdate();
    for(i=0;i<SDL_JoystickNumButtons(SDLjoy[index]);i++){
	if(SDL_JoystickGetButton(SDLjoy[index],i))ret+=a;
	a*=2;
    }
    if (autotimer()!=0)return -1;
    return ret;
}
//_________________________________________________________________________________________________________________________

//emulate_bjoy									: return emulate joystick buttons in keyboard keys
int emulate_bjoy(int index)
{
    Uint8 *keystate;
    if (autotimer()!=0)return -1;
    getevent();
    keystate = SDL_GetKeyState(NULL);


    int ret,a;
    ret=0;
    a=1;

    if(keystate[273] || keystate[264])ret+=a; 				//gp2x_north 		cursup 			or keypad 8
    a*=2;
    if((keystate[273] && keystate[276]) || keystate[263])ret+=a; 	//gp2x_northwest        cursup+cursleft 	or keypad 7
    a*=2;
    if(keystate[276] || keystate[260])ret+=a; 				//gp2x_west		cursleft		or keypad 4
    a*=2;
    if((keystate[274] && keystate[276]) || keystate[257])ret+=a; 	//gp2x_southwest	cursdown+cursleft	or keypad 1
    a*=2;
    if(keystate[274] || keystate[258])ret+=a; 				//gp2x_south		cursdown		or keypad 2
    a*=2;
    if((keystate[274] && keystate[275]) || keystate[259])ret+=a; 	//gp2x_southeast	cursdown+cursright	or keypad 3
    a*=2;
    if(keystate[275] || keystate[262])ret+=a;				//gp2x_east		cursright		or keypad 6
    a*=2;
    if((keystate[273] && keystate[275]) || keystate[265])ret+=a;	//gp2x_northeast	cursup+cursright	or keypad 9
    a*=2;


    if(keystate[13])ret+=a; 						//gp2x_start		enter
    a*=2;
    if(keystate[32])ret+=a;						//gp2x_select		space
    a*=2;

    if(keystate[304])ret+=a;						//gp2x_topleft		left shift
    a*=2;
    if(keystate[303])ret+=a;						//gp2x_topright		right shift
    a*=2;

    if(keystate[97])ret+=a;						//gp2x_a		a
    a*=2;
    if(keystate[115])ret+=a;						//gp2x_b		s
    a*=2;
    if(keystate[100])ret+=a;						//gp2x_x		d
    a*=2;
    if(keystate[102])ret+=a;						//gp2x_y		f
    a*=2;



    if(keystate[280])ret+=a;						//gp2x_volup		pageup
    a*=2;
    if(keystate[281])ret+=a;						//gp2x_voldown		pagedown
    a*=2;

    if(keystate[261])ret+=a;						//gp2x_center		keypad 5
    a*=2;

    //printf( "emulate joy=%d\n",ret);     //DEBUG!!!
    return ret;
}
//_________________________________________________________________________________________________________________________

//waitbjoy									: wait the pression of a joystick button (or emulate in keyboard)
int waitbjoy(int joy,int jbutton){
	if (jbutton==0)
		while(bjoy(joy)==0){
		    if (autotimer()!=0)return -1;
		}
	else
		while(bjoy(joy)!=jbutton){
		    if (autotimer()!=0)return -1;
		}
	return 0;
}
