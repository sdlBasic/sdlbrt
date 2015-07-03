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

#ifdef VIDEOMPEG_SUPPORT
//_________________________________________________________________________________________________________________________

// VIDEO MPEG
//_________________________________________________________________________________________________________________________


void updatempeg(SDL_Surface *screen, Sint32 x, Sint32 y, Uint32 w, Uint32 h)
{

    if ( screen->flags & SDL_DOUBLEBUF ) {
      SDL_Flip(screen);
    }
}
//_________________________________________________________________________________________________________________________

//loadmpeg(fname,usesound)		: load a mpeg video
int loadmpeg(char *filename,int useaudio)
{
    int use_video;
    SMPEG_Filter *filter;

    use_video = 1;
    mpeg_audio=useaudio;

    if (mpeg_audio==1 )
	Mix_CloseAudio();

    mpeg = SMPEG_new(filename, &info, mpeg_audio);
    if ( SMPEG_error(mpeg) ) {
	fprintf(stderr, "%s: %s\n", filename, SMPEG_error(mpeg));
	SMPEG_delete(mpeg);
	exit(2);
    }

    SMPEG_enableaudio(mpeg, mpeg_audio);
    SMPEG_enablevideo(mpeg, use_video);
    SMPEG_setvolume(mpeg, volumemusic(-1));

    //*
    filter = SMPEGfilter_bilinear();
    filter = SMPEG_filter( mpeg, filter );
    filter->destroy(filter);
    //*/

    return 0;
}

//_________________________________________________________________________________________________________________________

//plaympeg(filename,usesound,optional loop)	: play a mpeg1 video: Warning work only in windows
int plaympeg(int loop)
{
    SMPEG_setdisplay(mpeg, SDLscreen[c_screen], NULL, updatempeg);
    SMPEG_scaleXY(mpeg, SDLscreen[c_screen]->w, SDLscreen[c_screen]->h);
    if ( loop) {
	SMPEG_loop(mpeg, 1);
    }

    SMPEG_play(mpeg);
    return 0;
}
//_________________________________________________________________________________________________________________________

//stopmpeg()					: terminate the video play
int stopmpeg()
{
    SMPEG_stop(mpeg);
    return 0;
}
//_________________________________________________________________________________________________________________________

//deletempeg()				: unload mpeg video
int deletempeg()
{

    SMPEG_delete(mpeg);
    if (mpeg_audio==1){
	if ( Mix_OpenAudio(44100, AUDIO_S16SYS,	2, 8192) < 0 ) {
		enabledsound=0;
	}
	else{
	    Mix_AllocateChannels(16);
	    enabledsound=1;
	}
    }
    return 0;
}
//_________________________________________________________________________________________________________________________

//pausempeg()				: Pause/Resume playback of an SMPEG object
int pausempeg()
{
    SMPEG_pause(mpeg);
    return 0;
}
//_________________________________________________________________________________________________________________________

//rewindmpeg()				: Rewind the play position of an SMPEG object to the beginning of the MPEG
int rewindmpeg()
{
    SMPEG_rewind( mpeg );
    SMPEG_play(mpeg);
    return 0;
}
//_________________________________________________________________________________________________________________________

//seekmpeg(p)				: Seek 'bytes' bytes in the MPEG stream
int seekmpeg(int p)
{
    SMPEG_seek( mpeg, p);
    return 0;
}
//_________________________________________________________________________________________________________________________

//skipmpeg(s)				: Skip 'seconds' seconds in the MPEG stream
int skipmpeg(int s)
{
    SMPEG_skip( mpeg, (float) s );
    return 0;
}
//_________________________________________________________________________________________________________________________

//statusmpeg()				: return 1 if plaympeg work or 0 in other case
int statusmpeg()
{
    SMPEGstatus status;
    status=SMPEG_status( mpeg );
    if (status ==1)return 1;
    return 0;
}
#endif

