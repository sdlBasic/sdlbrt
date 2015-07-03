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

//CD SUPPORT
//_________________________________________________________________________________________________________________________

//numdrivescd 				: returns the number of cd-rom drives on the system.
int numdrivescd()
{
	return SDL_CDNumDrives();
}
//_________________________________________________________________________________________________________________________

//namecd(drive)				: returns a human-readable, system-dependent identifier for the cd-rom.
int namecd(char name[255],int drive)
{
    char *pname;
    pname =(char *)SDL_CDName(drive);
    strcpy(name,pname);
    if (name==NULL)return -1;
    return 0;
}
//_________________________________________________________________________________________________________________________

//getfreecd				: return first free channel Cd
int getfreecd()
{
    int i;
    for(i=0; i<NUM_CD; i++ )
	if(SDLcd[i]==NULL)return i;
    return -1;
}
//_________________________________________________________________________________________________________________________

//opencd(n,drive)			: opens a cd-rom drive for access.
int opencd(int n, int drive)
{
    if(n==-1)n=getfreecd();
    if(n<0 ||n>NUM_CD)return -1;

    if(SDLcd[n]!=NULL)free(SDLcd[n]);

    SDLcd[n]=SDL_CDOpen(drive);

    if(SDLcd[n]!=NULL)
	return n;
    else
	return -1;
}
//_________________________________________________________________________________________________________________________

//indrivecd(n)					: return 1 if cd is in driver
int indrivecd(int n)
{
    if(n<0 ||n>NUM_CD)return -1;

    if(CD_INDRIVE(SDL_CDStatus(SDLcd[n])))
	return 1;
    else
	return 0;
}
//_________________________________________________________________________________________________________________________

//trackscd(cd) 				: returns the number of tracks in cd.
int trackscd(int n)
{
    if (n<0 ||n>NUM_CD)return -1;
    if (SDLcd[n]==NULL)return -1;
    return SDLcd[n]->numtracks;
}
//_________________________________________________________________________________________________________________________

//curtrackcd(n)				: return the current track in cd
int curtrackcd(int n)
{
    if( n<0 ||n>NUM_CD)return -1;
    if (SDLcd[n]==NULL)return -1;
    SDL_CDStatus(SDLcd[n]);
    return SDLcd[n]->cur_track;
}
//_________________________________________________________________________________________________________________________

//curframecd(n)				: return the current frame in cd
int curframecd(int n)
{
    if( n<0 ||n>NUM_CD)return -1;
    if (SDLcd[n]==NULL)return -1;
    SDL_CDStatus(SDLcd[n]);
    return SDLcd[n]->cur_frame;
}
//_________________________________________________________________________________________________________________________

//playcd(n,s,l)				: play a cd
int playcd(int n,int s,int l)
{
    if( n<0 ||n>NUM_CD)return -1;
    if (SDLcd[n]==NULL)return -1;
    if (CD_INDRIVE(SDL_CDStatus(SDLcd[n])))
	return SDL_CDPlay(SDLcd[n],s,l);
    return 0;
}
//_________________________________________________________________________________________________________________________

//playtrackscd(n,trk1,fr1,ntrks,nfrs)	: play the given cd track(s)0=all
int playtrackscd(int n,int trk1,int fr1,int ntrks,int nfrs)
{
    if( n<0 ||n>NUM_CD)return -1;
    if (SDLcd[n]==NULL)return -1;

    if(CD_INDRIVE(SDL_CDStatus(SDLcd[n])))
	return SDL_CDPlayTracks(SDLcd[n], trk1, fr1, ntrks, nfrs);
    return 0;
}
//_________________________________________________________________________________________________________________________

//pausecd(n) 				: pauses a cdrom
int pausecd(int n)
{
    if( n<0 ||n>NUM_CD)return -1;
    if (SDLcd[n]==NULL)return -1;
    if (!CD_INDRIVE(SDL_CDStatus(SDLcd[n])))return -1;

    return SDL_CDPause(SDLcd[n]);
}

//_________________________________________________________________________________________________________________________

//resumecd(n) 				: resumes a cdrom
int resumecd(int n)
{
    if( n<0 ||n>NUM_CD)return -1;
    if (SDLcd[n]==NULL)return -1;
    if (!CD_INDRIVE(SDL_CDStatus(SDLcd[n])))return -1;

    return SDL_CDResume(SDLcd[n]);
}

//_________________________________________________________________________________________________________________________

//stopcd(n)				: stops a cdrom
int stopcd(int n)
{
    if( n<0 ||n>NUM_CD)return -1;
    if (SDLcd[n]==NULL)return -1;
    if (!CD_INDRIVE(SDL_CDStatus(SDLcd[n])))return -1;

    return SDL_CDStop(SDLcd[n]);
}
//_________________________________________________________________________________________________________________________

//ejectcd(n) 				: ejects a cdrom
int ejectcd(int n)
{
    if( n<0 ||n>NUM_CD)return -1;
    if (SDLcd[n]==NULL)return -1;

    return SDL_CDEject(SDLcd[n]);
}
//_________________________________________________________________________________________________________________________

//closecd(n)				: closes a cd handle
int closecd(int n)
{
    if( n<0 ||n>NUM_CD)return -1;
    if (SDLcd[n]==NULL)return -1;

    SDL_CDClose(SDLcd[n]);
    return 0;
}
//_________________________________________________________________________________________________________________________

//tracktypecd(n,t)			: return SDL_AUDIO_TRACK(0...) or SDL_DATA_TRACK(1...)
int tracktypecd(int n,int t)
{
    if( n<0 ||n>NUM_CD)return -1;
    if(SDLcd[n]==NULL)return -1;
    if (!CD_INDRIVE(SDL_CDStatus(SDLcd[n])))return -1;
    if (t<0 || t > (SDLcd[n]->numtracks))return -1;
    return SDLcd[n]->track[t].type;
}
//_________________________________________________________________________________________________________________________

//tracklengthcd(n,t)			: return the length of track t
int tracklengthcd(int n,int t)
{
    if( n<0 ||n>NUM_CD)return -1;
    if(SDLcd[n]==NULL)return -1;
    if (!CD_INDRIVE(SDL_CDStatus(SDLcd[n])))return -1;
    if (t<0 || t>(SDLcd[n]->numtracks))return -1;
    return SDLcd[n]->track[t].length;
}
//_________________________________________________________________________________________________________________________

//trackoffsetcd(n,t)			: return the offset to the beginning of this track in frames
int trackoffsetcd(int n,int t)
{
    if( n<0 ||n>NUM_CD)return -1;
    if(SDLcd[n]==NULL)return -1;
    if (!CD_INDRIVE(SDL_CDStatus(SDLcd[n])))return -1;
    if (t<0 || t>(SDLcd[n]->numtracks))return -1;
    return SDLcd[n]->track[t].offset;
}
