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

    vroby65
    vroby.mail@gmail.com

_________________________________________________________________________________________________________________________
*/
#pragma GCC diagnostic ignored "-Warray-bounds"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>


#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_net.h"
#include "../unzip/unzip.h"

#include "SDLengine.h"



//error print
#define SDLerr fprintf

//_________________________________________________________________________________________________________________________

//DECLARATIONS

//- SYSTEM --------------------------------------------------------------------------------------------------------------

const SDL_VideoInfo *SystemInfo;
int SystemWidth;
int SystemHeight;

//- SCREEN --------------------------------------------------------------------------------------------------------------

SDL_Surface *SDLdisplay;

//int GL_display;


int SDLautoback;
float SDLautobacktime;
int vbl;
int display_mode;

int SDLupdatesprite;
int SDLupdatebob;
int SDLdualplayfield;
int SDLnoAlphaChannel;

int SDLfps;
int SDLfps_count;
int SDLfps_flag;
int SDLfps_time;

int c_screen;
SDL_Surface *SDLscreen[NUM_SCREENS];
int Palette[256];
int enablePalette;
int colorcycling_s;
int colorcycling_e;
int colorcycling_d;
int colorcycling_delay;
int colorcycling_next;

SDL_Rect SDLscreen_rect[NUM_SCREENS];
int SDLscreen_z[NUM_SCREENS];
int SDLscreen_flag[NUM_SCREENS];
int SDLscreen_live[NUM_SCREENS];
int SDLoffx[NUM_SCREENS];
int SDLoffy[NUM_SCREENS];
int SDLlastscreen;

SDL_Color SDLcol;

//FADE PARAM
int fadeflag[NUM_SCREENS];
SDL_Surface* p_surf_black[NUM_SCREENS];
SDL_Surface* p_surf_screen_copy[NUM_SCREENS];
Uint32 ui_old_time[NUM_SCREENS], ui_curr_time[NUM_SCREENS], ui_time_ms[NUM_SCREENS] ;
int fadedelay[NUM_SCREENS];
double f_alpha[NUM_SCREENS] ;

Uint32 ui_flags[NUM_SCREENS];
SDL_Surface* p_surf_screen[NUM_SCREENS];
SDL_Surface* p_surf_img[NUM_SCREENS];
Uint32 ui_seconds[NUM_SCREENS];
int b_fade_out[NUM_SCREENS];

int crossfadeflag[NUM_SCREENS];
SDL_Surface* p_surf_img1[NUM_SCREENS];
SDL_Surface* p_surf_img2[NUM_SCREENS];





//------------------------------------------------------------------------------------------------------------------------

//- IMAGES --------------------------------------------------------------------------------------------------------------

int SDL_hsx[NUM_IMAGES];
int SDL_hsy[NUM_IMAGES];

SDL_Surface *SDLimage[NUM_IMAGES];
SDL_Surface *SDLimageCC[NUM_IMAGES];
Uint32 colorkey;

//------------------------------------------------------------------------------------------------------------------------

//- SPRITES --------------------------------------------------------------------------------------------------------------

int SDLspritex[NUM_SPRITES];
int SDLspritey[NUM_SPRITES];
int SDLspritefr[NUM_SPRITES];
int SDLspritelive[NUM_SPRITES];
int SDLspritez[NUM_SPRITES];

SDL_Rect SDLspriteclip;
int SDLlastsprite;

//------------------------------------------------------------------------------------------------------------------------

//- BOBS -----------------------------------------------------------------------------------------------------------------

int SDLbobscreen[NUM_BOBS];
int SDLbobx[NUM_BOBS];
int SDLboby[NUM_BOBS];
int SDLbobxold[NUM_BOBS];
int SDLbobyold[NUM_BOBS];
int SDLbobfr[NUM_BOBS];
int SDLboblive[NUM_BOBS];
int SDLbobz[NUM_BOBS];
SDL_Surface *SDLbobback[NUM_BOBS];
int SDLlastbob;

//------------------------------------------------------------------------------------------------------------------------

//- SOUND AND MUSIC ------------------------------------------------------------------------------------------------------

int enabledsound;
Mix_Chunk *SDLsound[NUM_WAVES];
Mix_Music *SDLmusic;

//------------------------------------------------------------------------------------------------------------------------

//- CD SUPPORT -----------------------------------------------------------------------------------------------------------

SDL_CD *SDLcd[NUM_CD];

//------------------------------------------------------------------------------------------------------------------------

//- VIDEO MPEG ---------------------------------------------------------------------------------------------------------------------

#if defined(VIDEOMPEG_SUPPORT)
SMPEG *mpeg;
SMPEG_Info info;
int mpeg_audio;
#endif

//------------------------------------------------------------------------------------------------------------------------

//- TEXT AND PRINT -------------------------------------------------------------------------------------------------------

char *fontPath;
TTF_Font *font;
SDL_Surface *SDLtext;

//TTF_Font *font_mono;
//char *fontPathMono;

SDL_Surface *SDLfont_mono[0xff];
int stx[NUM_SCREENS];
int sty[NUM_SCREENS];
int pen_color;
int paper_color;

int oldstx[NUM_SCREENS];
int oldsty[NUM_SCREENS];
SDL_Surface *SDLcursore[16];

int cursore_state[NUM_SCREENS];
SDL_Surface *SDLcursore_preserve[NUM_SCREENS];
int cursore_anim[NUM_SCREENS];

//------------------------------------------------------------------------------------------------------------------------

//- KEYBOARD --------------------------------------------------------------------------------------------------------------

int lastkey;

//------------------------------------------------------------------------------------------------------------------------

//- MOUSE --------------------------------------------------------------------------------------------------------------

int mousepointer;
int mousestate;

//------------------------------------------------------------------------------------------------------------------------

//- JOYSTICK ------------------------------------------------------------------------------------------------------
int num_joystick;
SDL_Joystick *SDLjoy[16];

//------------------------------------------------------------------------------------------------------------------------

//- SOCKS ----------------------------------------------------------------------------------------------------------------

#if defined(SOCKET_SUPPORT)
int enabledsock;
TCPsocket SDLsock[NUM_SOCKS];
#endif

//------------------------------------------------------------------------------------------------------------------------

/*----- Error system ---*/
char *error_description;
int error_type;





//==========================================================================================================================================
//							STARTING AND CLOSING SDLENGINE
//==========================================================================================================================================

//________________________________________________________________________________________________________________________________________

//initialize								: Start the engine and set the default parameter
int initialize(int audio,int socket,int defaults)
{
    int i;

	/*reset error_description */
	error_description=NULL;
	error_type=0;

	/* Initialize the SDL library */
	if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
		SDLerr(stderr, "Can't initialize SDL: %s\n",SDL_GetError());
		exit(2);
	}
	atexit(SDL_Quit);

	if (audio!=0){
	    /* Open the audio device */
	    // parameters: 11025 | 22050 | 44100 - AUDIO_U8 | AUDIO_S16SYS - 1 | 2 - 512 | 8192
	    if ( Mix_OpenAudio(44100, AUDIO_S16SYS,	2, 8192) < 0 ) {
		SDLerr(stderr,"Warning: Can't set 44100 Hz 16-bit stereo audio\n- Reason: %s\n",SDL_GetError());
		enabledsound=0;
	    }
	    else{
		Mix_AllocateChannels(16);
		enabledsound=1;
	    }
	}
	else{
		enabledsound=0;
	}


	//joystick
  	num_joystick=SDL_NumJoysticks();
	if (num_joystick!=0){
	    for (i=0;i<num_joystick;i++){
		    SDLjoy[i]=SDL_JoystickOpen(i);
	    }
	}

#if defined(WIN32)
	fontPath=(char *)malloc(256);
	strcpy(fontPath,getenv("WINDIR"));
	strcat(fontPath,"\\fonts\\DejaVuSans.ttf\0");
	if (!fileExist(fontPath))fontPath=".\\DejaVuSans.ttf";
#else
	fontPath=(char *) malloc(256);
	strcpy(fontPath,font_prefix);
	strcat(fontPath,"/dejavu/DejaVuSans.ttf\0");
	if (!fileExist(fontPath))fontPath="./DejaVuSans.ttf";
#endif



/*
	if (!fileExist(fontPath)){
		error_description="Fatal: DejaVuSans.ttf fonts not found ";
		error_type=1;
		SDLerr(stderr,"Fatal: DejaVuSans.ttf fonts not found \n ");
		return 1;
	}
//*/
	if ( TTF_Init() != 0 ) {
		SDLerr(stderr,"Warning: Can't initialize true type %s errror: %s\n",fontPath,SDL_GetError());

	}
	else
	{

		/* enabled unicode*/
		SDL_EnableUNICODE(1);

		/* enabled autorepeat keys */
		SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
	}

#if defined(SOCKET_SUPPORT)
	if (socket!=0){
	    /* net initializing */
	    if ( SDLNet_Init() != 0 ) {
		SDLerr(stderr,"Warning: Can't initialize net system: %s\n",SDL_GetError());
		enabledsock=0;
	    }
	    else{
		enabledsock=1;
	    }
	}
	else{
	    enabledsock=0;
	}
#endif
	
	
	for (i=0;i<NUM_SCREENS;i++){
	    fadeflag[i]=0;
	    crossfadeflag[i]=0;
	    fadedelay[i]=0;
	}

	/* reset the image bank */
	for (i=0;i<NUM_IMAGES;i++){
		SDLimage[i]=NULL;
		SDLimageCC[i]=NULL;
	}

	/* reset the sound bank */
	for (i=0;i<NUM_WAVES;i++)
		SDLsound[i]=NULL;

	/* reset the screen  bank */
	for (i=0;i<=NUM_SCREENS;i++){
		SDLscreen[i]=NULL;
		SDLscreen_rect[i].x=0;
		SDLscreen_rect[i].y=0;
		SDLscreen_rect[i].w=0;
		SDLscreen_rect[i].h=0;
		SDLscreen_flag[i]=0;
		SDLscreen_live[i]=0;
		//zorder reset
		SDLscreen_z[i]=i;

		cursore_state[i]=0;
		cursore_anim[i]=0;


	}
	SDLlastscreen=1;

	/*reset the sprites  */
	for (i=0;i<NUM_SPRITES;i++){
		SDLspritelive[i]=0;
		SDLspritefr[i]=-1;
		SDLspritex[i]=0;
		SDLspritey[i]=0;
		//zorder reset
		SDLspritez[i]=i;
	}
	SDLlastsprite=1;

	/*reset the bobs  */
	for (i=0;i<NUM_BOBS;i++){
		SDLbobscreen[i]=-1;
		SDLbobback[i]=NULL;
		SDLboblive[i]=0;
		SDLbobfr[i]=-1;
		SDLbobx[i]=0;
		SDLboby[i]=0;
		//zorder reset
    		SDLbobz[i]=i;
	}
	SDLlastbob=1;

	/* set default palette*/
	for (i=0;i<255;i++)
	    color(i,rgb(255-i,255-i,255-i));

	color(0,0); //black
	color(1,rgb(0,0,255)); //blue
	color(2,rgb(0,255,0)); //green
	color(3,rgb(192,192,255)); //azzurro
	color(4,rgb(255,0,0)); //red
	color(5,rgb(255,255,0)); //magenta
	color(6,rgb(128,80,40)); //brown
	color(7,rgb(255,255,255)); //white
	color(8,rgb(128,128,128)); //grigio
	color(9,rgb(128,128,255)); //blu chiaro
	color(10,rgb(128,255,128)); //verde chiaro
	color(11,rgb(128,128,255)); //azzurro chiaro
	color(12,rgb(255,128,128)); //red chiaro
	color(13,rgb(255,255,128)); //magenta chiaro
	color(14,rgb(255,255,0)); //giallo
	color(15,rgb(255,255,255)); //white


	/*default colorkey */
	colorkey=-1;
	
	/* using SDL_GetVideoInfo to find SystemWidth and SystemHeight 
	SystemInfo = SDL_GetVideoInfo(); 
	SystemWidth =  SystemInfo->current_w; 
	SystemHeight = SystemInfo->current_h; 

	/* the color default is white */
	SDLcol.r=(Uint8)255;
	SDLcol.g=(Uint8)255;
	SDLcol.b=(Uint8)255;

	/*default settings*/
	if (defaults!=0){
		setdisplay(640,480,0,1);
		autoback(25);

		/* create and initialize print font */
		createfont();

		/* create and initialize print cursor */
		createcursor();

		autoupdatesprite(1);
		autoupdatebob(1);
		dualplayfield(0);
		getevent();
		mouseshow();
	}else{
		getevent();
	}
    return 0;
}
//________________________________________________________________________________________________________________________________________

//terminate								: Stop the engine and reset parameter
int terminate()
{
	/* close all socks opens */
        int i;
	
#if defined(SOCKET_SUPPORT)	
	for (i=1;i<NUM_SOCKS;i++)
	    closesock(i);
#endif
	
	/* close the joystic opens */
	if (num_joystick!=0){
	    for (i=0;i<num_joystick;i++){
		SDL_JoystickClose(SDLjoy[i]);
	    }
	}

	SDLNet_Quit();
	TTF_Quit();
	Mix_CloseAudio();
	atexit(SDL_Quit);
	//exit(0);
    return 0;
}
//_________________________________________________________________________________________________________________________









