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

//SOUND
//_________________________________________________________________________________________________________________________

//isenabledsound()							: return 1 if sdlsound was enabled
int isenabledsound()
{
    return enabledsound;
}
//________________________________________________________________________________________________________________________________________

//soundexists(n)							: return 1 if the sound buffer n exist 0 if empty
int soundexists( int n )
{
	if (n>NUM_WAVES || n<0){
		error_description="SDLengine error - soundExists: invalid sound slot number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - soundExists: %d is an invalid sound slot number", n);
		return -1;
	}
	if ( SDLsound[n] == NULL ) {
		return(0);
	}
	return 1;
}
//________________________________________________________________________________________________________________________________________

//deletesound(n)							: delete from memory sound n
int deletesound(int n)
{
	if (n>NUM_WAVES || n<0){
		error_description="SDLengine error - deleteSound: invalid sound slot number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - deleteSound: %d is an invalid sound slot number", n);
		return -1;
	}
    	if ( SDLsound[n] != NULL ) {
		Mix_FreeChunk(SDLsound[n]);
		SDLsound[n]=NULL;
		return 0;
	}
	else
	{
		error_description="SDLengine error - deleteSound: sound slot is yet empty ";
		error_type=1;
		SDLerr(stderr,"SDLengine error - deleteSound: sound slot %d is yet empty", n);
		return -1;

	}


}
//________________________________________________________________________________________________________________________________________

//copysound(s,d)							: copy  sound bank s in sound bank d
int copysound(int s, int d)
{
	if (s>NUM_WAVES || s<0){
		error_description="SDLengine error - copySound: invalid source sound slot number";
		error_type=1;
		SDLerr(stderr, "SDLengine error - copySound: source slot %d is an invalid sound slot number", s);
		return -1;
	}
	if (d>NUM_WAVES || d<0){
		error_description="SDLengine error - copySound: invalid target sound slot number";
		error_type=1;
		SDLerr(stderr, "SDLengine error - copySound: destination slot %d is an invalid sound slot number", d);
		return -1;
	}

    	if ( SDLsound[s] != NULL ) {
		Mix_FreeChunk(SDLsound[d]);
		SDLsound[d]= Mix_QuickLoad_RAW(SDLsound[s]->abuf,SDLsound[s]->alen);
		return 0;
	}
	else
	{
		error_description="SDLengine error - copySound: source sound slot is empty ";
		error_type=1;
		SDLerr(stderr,"SDLengine error - copySound: source sound slot %d is empty", s);
		return -1;

	}
}
//________________________________________________________________________________________________________________________________________

//musicexists()								: return 1 if the music is load 0 if empty
int musicexists()
{
	if ( SDLmusic == NULL ) {
		return(0);
	}
	return 1;
}
//__________________________________________________________________________________________________________________________

//playsound(n,c,l)							: play the sound n in  channel c l loops
int playsound (int n,int c,int l)
{
	if (n>NUM_WAVES || n<0){
		error_description="SDLengine error - playSound: invalid sound slot number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - playSound: %d is an invalid sound slot number", n);
		return -1;
	}
	if (enabledsound==0){
		SDLerr(stderr, "Warning: sounds are not enabled");
		return 0;
	}
	if (SDLsound[n]!=NULL){
		Mix_PlayChannel(c,SDLsound[n], l);
		return 0;
	}
	else {
		error_description="SDLengine error - playSound: sound slot is empty ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - playSound: sound slot %d is empty", n);
		return -1;
	}
}
//_________________________________________________________________________________________________________________________

//playfreqsound(n,c,pitch,l)						: play the sound n in  channel c l loops at freq variation (negative number=low positive number =high)
int playfreqsound ( int n, int c, float pitch, int l)
{
    	if (n>NUM_WAVES || n<0){
		error_description="SDLengine error - playFreqSound: invalid sound slot number ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - playFreqSound: %d is an invalid sound slot number", n);
		return -1;
	}
	if (enabledsound==0){
		SDLerr(stderr, "Warning: sounds are not enbled\n");
		return 0;
	}
	if (SDLsound[n]!=NULL){
	    Mix_PlayChannel(c,Change_Pitch(SDLsound[n],pow(2 , 0-(pitch/12))), l);
	    return 0;
	}
	else {
		error_description="SDLengine error - playFreqSound: sound slot is empty ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - playFreqSound: sound slot %d is empty", n);
		return -1;
	}
}
//_______________________________________________________________________________________________________________________

//volumesound(c,v)							: change the volume of channel c (-1  all) at value v (0-128) with v = -1 return the current volume
int volumesound(int c,int v)
{
	if (enabledsound==0){
		SDLerr(stderr, "Warning: sounds are not enbled");
		return 0;
	}
	return Mix_Volume(c,v);
}
//_______________________________________________________________________________________________________________________

//stopsound(c)								: stop the  wave play in channel c (-1 =all)
int stopsound(c)
{
	if (enabledsound==0){
		SDLerr(stderr, "Warning: sounds are not enbled");
		return 0;
	}
    return Mix_HaltChannel(c);
}
//_______________________________________________________________________________________________________________________

//pausesound(c)								: paused channel c (-1 =all)
int pausesound(int c)
{
	if (enabledsound==0){
		SDLerr(stderr, "Warning: sounds are not enbled");
		return 0;
	}
    Mix_Pause(c);
    return 0;
}
//_______________________________________________________________________________________________________________________

//resumesound(c)							: unpaused channel c (-1 =all)
int resumesound(int c)
{
	if (enabledsound==0){
		SDLerr(stderr, "Warning: sounds are not enbled");
		return 0;
	}
    Mix_Resume(c);
    return 0;
}
//_______________________________________________________________________________________________________________________

//vumetersound(c)							: return the current state of sound channel (-1 =all)
int vumetersound(int c)
{
	if (enabledsound==0){
		SDLerr(stderr, "Warning: sounds are not enbled");
		return 0;
	}
    return Mix_Playing(c);
}
//_______________________________________________________________________________________________________________________

//positionsound(c,angle,dist)						: position sound in 3d space
int positionsound(int c,int angle,int dist)
{
	if (enabledsound==0){
		SDLerr(stderr, "Warning: sounds are not enbled");
		return 0;
	}
    return Mix_SetPosition(c, (Sint16)angle, (Uint8) dist);
}
//_______________________________________________________________________________________________________________________

//soundchannels(n)							: dinamically change the number of channells managed by sdlBasic
int soundchannels(int n)
{
	if (enabledsound==0){
		SDLerr(stderr, "Warning: sounds are not enbled");
		return 0;
	}
    return Mix_AllocateChannels(n);
}
//_______________________________________________________________________________________________________________________

//playmusic(n)								: play track xm,mod,ogg,mp3 n=number of ripetition(-1 always)
int playmusic ( int n)
{
	if (enabledsound==0){
		SDLerr(stderr, "Warning: sounds are not enbled");
		return 0;
	}
	if (SDLmusic!=NULL){
		Mix_PlayMusic(SDLmusic, n);
		return 0;
	}
	else {
		error_description="SDLengine error - playMusic: music not loaded ";
		error_type=1;
		SDLerr(stderr, "SDLengine error - playMusic: music not loaded");
		return -1;
	}
}
//______________________________________________________________________________________________________________________

//positionmusic(p)							: move the execution at p second
int positionmusic(int p)
{
	if (enabledsound==0){
		SDLerr(stderr, "Warning: sounds are not enbled");
		return 0;
	}
        return Mix_SetMusicPosition((double) p);
}
//______________________________________________________________________________________________________________________

//stopmusic								: terminate the music play
int stopmusic()
{
	if (enabledsound==0){
		SDLerr(stderr, "Warning: sounds are not enbled");
		return 0;
	}
	Mix_HaltMusic();
	return 0;
}
//_______________________________________________________________________________________________________________________

//pausemusic								: set pause of the current music
int pausemusic()
{
	if (enabledsound==0){
		SDLerr(stderr, "Warning: sounds are not enbled");
		return 0;
	}
        Mix_PauseMusic();
        return 0;
}
//_______________________________________________________________________________________________________________________

//resumemusic								: unset pause of musica
int resumemusic()
{
	if (enabledsound==0){
		SDLerr(stderr, "Warning: sounds are not enbled");
		return 0;
	}
        Mix_ResumeMusic();
        return 0;
}
//_______________________________________________________________________________________________________________________

//rewindmusic								: rewind at start the music
int rewindmusic()
{
	if (enabledsound==0){
		SDLerr(stderr, "Warning: sounds are not enbled");
		return 0;
	}
       Mix_RewindMusic();
        return 0;
}
//_______________________________________________________________________________________________________________________

//fademusic(t)								: music fade

int fademusic_t,fademusic_delay;

int fademusic(int t)
{
	if (enabledsound==0){
		SDLerr(stderr, "Warning: sounds are not enbled");
		return 0;
	}

	if (t!=-1){
	    fademusic_t=(t*1000)/Mix_VolumeMusic(-1);
	    fademusic_delay=chrono()+fademusic_t;
	}
	return Mix_VolumeMusic(-1);

}

void fademusichandler()
{
    int t;
    t=fademusic_t;
 	Mix_VolumeMusic(Mix_VolumeMusic(-1)-1);
	fademusic_delay=chrono()+t;
	if (Mix_VolumeMusic(-1)<=0){
	    Mix_HaltMusic();
	    fademusic_t=0;
	}
}
//_______________________________________________________________________________________________________________________

//volumemusic(v)							: change the volume of music (0-128) -1 return the current volume
int volumemusic(int v)
{
	if (enabledsound==0){
		SDLerr(stderr, "Warning: sounds are not enbled");
		return 0;
	}
 	return Mix_VolumeMusic(v);

}
//_______________________________________________________________________________________________________________________

//speedmusic(v)								: change the speed of music
int speedmusic(int v)
{
	if (enabledsound==0){
		SDLerr(stderr, "Warning: sounds are not enbled");
		return 0;
	}
    return Mix_SetSynchroValue(v);
}
