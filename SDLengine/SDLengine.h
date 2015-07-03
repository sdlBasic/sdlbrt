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
/* ---- Defines */

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

#ifndef __APPLE__
#include "smpeg.h"
#else
#include "smpeg/smpeg.h"
#endif



#ifndef MIN
#define MIN(x,y)     (((x) < (y)) ? (x) : (y))
#define MAX(x,y)     (((x) > (y)) ? (x) : (y))
#define MID(x,y,z)   MAX((x), MIN((y), (z)))
#endif

#define PRINT_SIZE	12
#define XPRINT_SIZE	(PRINT_SIZE*3/4)

#define NUM_SCREENS	9
#define NUM_IMAGES	65536

#define NUM_SPRITES 	1024
#define NUM_BOBS 	1024

#define NUM_WAVES	1024

#define NUM_CD		8

#if defined(SOCKET_SUPPORT)
#define NUM_SOCKS	1024
#endif


#ifndef M_PI
#define M_PI	3.141592654
#endif

#define SMOOTHING_OFF		0
#define SMOOTHING_ON		1

//error print
#define SDLerr fprintf

//_________________________________________________________________________________________________________________________

//DECLARATIONS

//- SYSTEM --------------------------------------------------------------------------------------------------------------

extern const SDL_VideoInfo *SystemInfo;

extern int SystemWidth;
extern int SystemHeight;

//- SCREEN --------------------------------------------------------------------------------------------------------------

extern int nodebug;

extern SDL_Surface *SDLdisplay;
//extern int GL_display;

extern int SDLautoback;
extern float SDLautobacktime;
extern int vbl;
extern int display_mode;

extern int SDLupdatesprite;
extern int SDLupdatebob;
extern int SDLdualplayfield;
extern int SDLnoAlphaChannel;

extern int SDLfps;
extern int SDLfps_count;
extern int SDLfps_flag;
extern int SDLfps_time;

extern int c_screen;
extern SDL_Surface *SDLscreen[NUM_SCREENS];
extern int Palette[256];
extern int enablePalette;
extern int colorcycling_s;
extern int colorcycling_e;
extern int colorcycling_d;
extern int colorcycling_delay;
extern int colorcycling_next;



extern SDL_Rect SDLscreen_rect[NUM_SCREENS];
extern int SDLscreen_flag[NUM_SCREENS];
extern int SDLscreen_live[NUM_SCREENS];
extern int SDLscreen_z[NUM_SCREENS];
extern int SDLoffx[NUM_SCREENS];
extern int SDLoffy[NUM_SCREENS];
extern int SDLlastscreen;

extern SDL_Color SDLcol;

//FADE PARAM
extern int fadeflag[NUM_SCREENS];
extern SDL_Surface* p_surf_black[NUM_SCREENS];
extern SDL_Surface* p_surf_screen_copy[NUM_SCREENS];
extern Uint32 ui_old_time[NUM_SCREENS], ui_curr_time[NUM_SCREENS], ui_time_ms[NUM_SCREENS] ;
extern int fadedelay[NUM_SCREENS];
extern double f_alpha[NUM_SCREENS] ;

extern Uint32 ui_flags[NUM_SCREENS];
extern SDL_Surface* p_surf_screen[NUM_SCREENS];
extern SDL_Surface* p_surf_img[NUM_SCREENS];
extern Uint32 ui_seconds[NUM_SCREENS];
extern int b_fade_out[NUM_SCREENS];

extern int crossfadeflag[NUM_SCREENS];
extern SDL_Surface* p_surf_img1[NUM_SCREENS];
extern SDL_Surface* p_surf_img2[NUM_SCREENS];


//------------------------------------------------------------------------------------------------------------------------

//- IMAGES --------------------------------------------------------------------------------------------------------------

extern int SDL_hsx[NUM_IMAGES];
extern int SDL_hsy[NUM_IMAGES];

extern SDL_Surface *SDLimage[NUM_IMAGES];
extern SDL_Surface *SDLimageCC[NUM_IMAGES];
extern Uint32 colorkey;

//------------------------------------------------------------------------------------------------------------------------

//- SPRITES --------------------------------------------------------------------------------------------------------------

extern int SDLspritex[NUM_SPRITES];
extern int SDLspritey[NUM_SPRITES];
extern int SDLspritefr[NUM_SPRITES];
extern int SDLspritelive[NUM_SPRITES];
extern int SDLspritez[NUM_SPRITES];
extern SDL_Rect SDLspriteclip;
extern int SDLlastsprite;

//------------------------------------------------------------------------------------------------------------------------

//- BOBS -----------------------------------------------------------------------------------------------------------------

extern int SDLbobscreen[NUM_BOBS];
extern int SDLbobx[NUM_BOBS];
extern int SDLboby[NUM_BOBS];
extern int SDLbobxold[NUM_BOBS];
extern int SDLbobyold[NUM_BOBS];
extern int SDLbobfr[NUM_BOBS];
extern int SDLboblive[NUM_BOBS];
extern int SDLbobz[NUM_BOBS];
extern SDL_Surface *SDLbobback[NUM_BOBS];
extern int SDLlastbob;

//------------------------------------------------------------------------------------------------------------------------

//- SOUND AND MUSIC ------------------------------------------------------------------------------------------------------

extern int enabledsound;
extern Mix_Chunk *SDLsound[NUM_WAVES];
extern Mix_Music *SDLmusic;

//------------------------------------------------------------------------------------------------------------------------

//- CD SUPPORT -----------------------------------------------------------------------------------------------------------

extern SDL_CD *SDLcd[NUM_CD];

//------------------------------------------------------------------------------------------------------------------------

//- VIDEO MPEG ---------------------------------------------------------------------------------------------------------------------

#if defined(VIDEOMPEG_SUPPORT)
extern SMPEG *mpeg;
extern SMPEG_Info info;
extern int mpeg_audio;
#endif

//------------------------------------------------------------------------------------------------------------------------

//- TEXT AND PRINT -------------------------------------------------------------------------------------------------------

extern char *fontPath;
extern TTF_Font *font;
extern SDL_Surface *SDLtext;

//extern TTF_Font *font_mono;
//extern char *fontPathMono;
extern SDL_Surface *SDLfont_mono[0xff];
extern int stx[NUM_SCREENS];
extern int sty[NUM_SCREENS];
extern int pen_color;
extern int paper_color;

extern int oldstx[NUM_SCREENS];
extern int oldsty[NUM_SCREENS];
extern SDL_Surface *SDLcursore[16];

extern int cursore_state[NUM_SCREENS];
extern SDL_Surface *SDLcursore_preserve[NUM_SCREENS];
extern int cursore_anim[NUM_SCREENS];

//------------------------------------------------------------------------------------------------------------------------

//- KEYBOARD --------------------------------------------------------------------------------------------------------------

extern int lastkey;

//------------------------------------------------------------------------------------------------------------------------

//- MOUSE --------------------------------------------------------------------------------------------------------------

extern int mousepointer;
extern int mousestate;

//------------------------------------------------------------------------------------------------------------------------

//- JOYSTICK ------------------------------------------------------------------------------------------------------

extern int num_joystick;
extern SDL_Joystick *SDLjoy[16];

//------------------------------------------------------------------------------------------------------------------------

//- SOCKS ----------------------------------------------------------------------------------------------------------------
#if defined(SOCKET_SUPPORT)
extern int enabledsock;
extern TCPsocket SDLsock[NUM_SOCKS];
#endif

//------------------------------------------------------------------------------------------------------------------------
/*----- Error system ---*/
extern char *error_description;
extern int error_type;



//_________________________________________________________________________________________________________________________

/* ---- Structures */

  typedef struct tColorRGBA
  {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
  }
  tColorRGBA;

  typedef struct tColorY
  {
    Uint8 y;
  }
  tColorY;

//_________________________________________________________________________________________________________________________


#ifdef __cplusplus
extern "C" {
#endif

//_________________________________________________________________________________________________________________________

//INTERNAL RUTINES

int stopkey();
int getevent();
int autotimer();
//_________________________________________________________________________________________________________________________

// SDL_EXTENSION

int fileExist( char *name );
SDL_Surface *Load_Image(char *datafile, int transparent);
SDL_Surface *Load_zip_Image(char *zipfile,char *datafile, int transparent);
int Save_Image(char *datafile, SDL_Surface *image);
void Image_colorkey(SDL_Surface *image);
Mix_Chunk* Change_Pitch(Mix_Chunk *Input_Sample, float Factor);
int zoomSurfaceRGBA (SDL_Surface * src, SDL_Surface * dst, int smooth);
int zoomSurfaceY (SDL_Surface * src, SDL_Surface * dst);
void transformSurfaceRGBA (SDL_Surface * src, SDL_Surface * dst, int cx, int cy,int isin, int icos, int smooth);
void transformSurfaceY (SDL_Surface * src, SDL_Surface * dst, int cx, int cy,int isin, int icos);
SDL_Surface * rotozoomSurface (SDL_Surface * src, double angle, double zoom, int smooth);
SDL_Surface *zoomSurface (SDL_Surface * src, double zoomx, double zoomy, int smooth);
void fade (int s,SDL_Surface* in_p_surf_screen, SDL_Surface* in_p_surf_img, Uint32 in_ui_seconds, int in_b_fade_out);
void fadehandler(int s);
void crossfade (int s,SDL_Surface* in_p_surf_screen, SDL_Surface* in_p_surf_img1, SDL_Surface* in_p_surf_img2, Uint32 in_ui_seconds);
void crossfadehandler(int s);
int hit_pixelperfect(SDL_Surface *imga,int xa1,int ya1,int xa2,int ya2,SDL_Surface *imgb,int xb1,int yb1,int xb2,int yb2);

Uint32(*getpixel)(SDL_Surface *surface, int x, int y);
Uint32 getpixel8(SDL_Surface *surface, int x, int y);
Uint32 getpixel16(SDL_Surface *surface, int x, int y);
Uint32 getpixel24BE(SDL_Surface *surface, int x, int y);
Uint32 getpixel24(SDL_Surface *surface, int x, int y);
Uint32 getpixel32(SDL_Surface *surface, int x, int y);

void (*putpixel)(SDL_Surface *surface, int x, int y, Uint32 col );
void putpixel8(SDL_Surface *surface, int x, int y, Uint32 col );
void putpixel16(SDL_Surface *surface, int x, int y, Uint32 col );
void putpixel24BE(SDL_Surface *surface, int x, int y, Uint32 col );
void putpixel24(SDL_Surface *surface, int x, int y, Uint32 col );
void putpixel32(SDL_Surface *surface, int x, int y, Uint32 col );
void putpixelDX(SDL_Surface *surface, int x, int y, Uint32 col );

void draw_line(SDL_Surface * surface,int x1, int y1, int x2, int y2,Uint32 color);
void draw_box(SDL_Surface *surface,int x1,int y1,int x2,int y2,Uint32 color);
void draw_circle(SDL_Surface *surface,int vx,int vy, int r,Uint32 color);
void draw_fillcircle(SDL_Surface *surface,int vx,int vy, int r,Uint32 color);
void draw_ellipse(SDL_Surface *surface,int vx,int vy,int Xradius,int Yradius,Uint32 color);
void draw_fillellipse(SDL_Surface *surface,int vx,int vy,int Xradius,int Yradius,Uint32 color);

Uint32 (*rrgb)(int col);
Uint32 rrgb8(int col);
Uint32 rrgb16(int col);
Uint32 rrgb24(int col);
Uint32 rrgb32(int col);

int createfont();
int put_char(unsigned char n);
int createcursor();
void _input(char *instring,int x, int y, int displen);
//_________________________________________________________________________________________________________________________

//STARTING AND CLOSE

//initialize								: Start the engine and set the default parameter
int initialize(int audio,int socket,int defaults);

//terminate								: Stop the engine and reset parameter
int terminate();

//_________________________________________________________________________________________________________________________

//SCREEN

//setdefaults(w,h,bpp,0=screen|1=window |2=resizable)			: open the display, perform initializations on cursor and fonts and sets default values on sprites, bobs and screens system.
int setdefaults(int w,int h,int bpp, int mode);

//setdisplay(w,h,bpp,0=screen|1=window |2=resizable)			: open the screen/window in double buffer.
int setdisplay(int w,int h,int bpp, int mode);

//setalphachannel(v)									: activate deactivate alpha channel trasparency
int setalphachannel(int v);

//setcaption(title)									: change the display window title
int setcaption(char *title);

//caption(title)										: return the display window title
int caption(char **title);

//systemwidth										: return the native screen width
int systemwidth();

//systemheight										: return the native screen height
int systemheight();

//displaymode()										: return the display mode
int displaymode();

//displaywidth										: return the display width
int displaywidth();

//displayheight										: return the display height
int displayheight();

//displaybpp										: return the display color depth
int displaybpp();

//screen(n)											: set the logic screen n  with n=-1 return the current screen
int screen (int n);

//screenz(n,z)										: set the zorder position of screen if z =-1 report actual z position
int screenz(int n,int z);

//lastscreen										: return the last screen open
int lastscreen();

// directscreen 										: direct drawing on display like a screen(more fast but sprite and offset does not works)
int directscreen ();

//screenopen(n,w,h,dx,dy,dw,dh,flag)						: open the logic screen n of dimension w,h in display coordinates dx,dy,dw,dh
int screenopen (int n,int w,int h,int dx,int dy,int dw,int dh,int flag);

//screenclose(n)										: close the logic screen n
int screenclose (int n);


//screenclone(n,s,x,y,w,h,flag)							: create a  new viewport in logic screen s
int screenclone(int n,int s,int x,int y,int w,int h,int flag);

//screencopy(n,x,y,w,h,nd,xd,yd)							: copy a portion of screen n in a screen nd
int screencopy(int n,int x,int y,int w,int h,int nd,int xd,int yd);

//screenfade(n,t)										: fade the screen n in t time
int screenfade(int n,int t);

//screenfadein(n,i,t)									: fade the screen n to image i in t time
int screenfadein(int n,int i,int t);

//screencrossfade(n,i,t)								: fade the screen n from current screen  to image i in t time
int screencrossfade(int n,int i,int t);

//screenalpha(n,a)									: set alpha(trasparency) of screen n
int screenalpha(int n,int a);

//screenlock(n)										: lock the  screen n for direct graphics access
int screenlock(int n);

//screenunlock(n)									: unlock the  screen n for direct graphics access
int screenunlock(int n);


//screenrect(x,y,w,h,flag)								: change the display output coordinates of the current screen
int screenrect (int x,int y,int w,int h,int flag);

//xscreenrect										: return the x coordinate of current screen viewport
int xscreenrect();

//yscreenrect										: return the y coordinate of current screen viewport
int yscreenrect();

//wscreenrect										: return the w value of current screen viewport
int wscreenrect();

//hscreenrect										: return the h value of current screen viewport
int hscreenrect();

//flagscreenrect										: return the flag value of current screen viewport
int flagscreenrect();


//screenwidth										: return the current screen width
int screenwidth();

//screenheight										: return the current screen height
int screenheight();

//offset(x,y)											: set the logical current screen position
int offset(int x,int y);

//xoffset											: return the x coordinate offset in current screen
int xoffset();

//yoffset											: return the y coordinate offset in current screen
int yoffset();

//cls 												: clear the current logic screen
int cls();

//screenswap										: update display,bobsystem,spritesystem
int screenswap();

//autoback(m)										: enable / disable automatic screenswap  m=0 disable m>0 wait m milliseconds and perform screenswap m<0 perform the invocate in code screenswap after m milliseconds
int autoback(int m);

//dualplayfield(m)									: set/unset automatic update of a screen upper sprite -1 return state
int dualplayfield(int m);

//waitvbl											: wait automatic screenswap
int waitvbl();

//fps(n)											: set/unset or return (with -1) the current frame rate counter (0/1/-1)
int fps(int n);
//_________________________________________________________________________________________________________________________

//GRAPHICS

//rgb(r,g,b)								: return current color in Uint32 format
int rgb(int colR,int colG,int colB);

//enablepalette(state=0|1|-1 disable|enable|check)   			: enable disable and check the palettemode in 8 bit display
int enablepalette(int state);

//color (c,optional v)							: set  palette color c with value v se missing return the current color c
int color(int c,int v);

//colorcycling(s,e,d=0|1,delay)						: move the palettecolor one color forward or back work only in 8bit display
int colorcycling(int s,int e,int d,int delay);
void colorcyclinghandler();

//ink(c)								: select the current color in Uint32 format
int ink(int c);

//point(x,y)								: return the color of x,y point
int point(int x,int y);

//dot(x,y)								: write x,y point with a current color
int dot(int x,int y);

//dot_ex(x,y,c)								: write x,y point with a c color
int dot_ex(int x,int y,int c);

//line(x,y,x1,y1)							: write a line
int line(int x,int y,int x1,int y1);

//box(x,y,x1,y1)							: write a empty rettangle
int box(int x,int y,int x1,int y1);

//bar(x,y,x1,y1)							: write a fill rettangle
int bar(int x,int y,int x1,int y1);

//rectangle(x,y,w,h,mode)						: write a rettangle w and h are the sizes mode=0 empty 1=filled
int rectangle(int x,int y,int w,int h,int mode);

//circle(x,y,r)								: write a circle
int circle(int x,int y,int r);

//fillcircle(x,y,r)							: write a fill circle
int fillcircle(int x,int y,int r);

//ellipse(x,y,rx,ry)							: write a ellipse
int ellipse(int x,int y,int rx,int ry);

//fillellipse(x,y,rx,ry)						: write a fill ellipse
int fillellipse(int x,int y,int rx,int ry);

//paint(x,y)								: fill a close area
int paint(int x,int y);

//triangle(xa,ya,xb,yb,xc,yc)						: draw a filled triangle
int triangle(int xa,int ya,int xb,int yb,int xc,int yc);

//_________________________________________________________________________________________________________________________

// FILE INPUT OUTPUT

//getfreeimage								: return a number of image bank free
int getfreeimage();

//loadimage(filename,n)							: load a graphics file in a slot n if n=-1 use the first free and return as n
int loadimage(char *filename,int n);

//loadzipimage(zipfile,filename,opt n)					: load a graphics file stored in a zip archive in a slot n if n=-1 use the first free and return as n
int loadzipimage(char *zipfile,char *filename,int n);

// map image(blob) from memory
int mapblobimage(unsigned char *blob, int bsize, int n);
SDL_Surface *Map_blob_Image(unsigned char *blob, int bsize, int transparent);

//saveimage(filename,n)							: save slot n in a graphics file(only bmp)
int saveimage(char *filename,int n);

//getfreesound()							: return a number of first sound bank free
int getfreesound();

//loadsound(filename,n)							: load a wave file in a sound slot n if n=-1  use and return the first free
int loadsound(char *filename,int n);

//loadzipsound(zipfile,filename,n)					: load a wave zipped file in a sound slot n if n=-1  use and return the first free
int loadzipsound(char *zipfile,char *filename,int n);

//savesound(filename,n)							: save a wave file from sound slot n
int savesound(char *filename, int n);

//loadmusic(filename)							: load a music module (xm,mod,ogg and only for linux mp3)
int loadmusic(char *filename);

//loadzipmusic(zipfile,filename)					: load a zipped music module (xm,mod,ogg and only for linux mp3)
int loadzipmusic(char *zipfile,char *filename);
//_________________________________________________________________________________________________________________________

// IMAGE MANIPULATION

//hotspot(n,x,y)							: select the point of coordinates in a imageslot (n,0,0=up left(default) | n,1,1=center | n,2,2 =down right)n= image
int hotspot(int n,int x,int y);

//setcolorkey(c)							: set the colorkey for bitmap transparency if set -1 (default ) will be used the left-up corner color.
int setcolorkey(int c);

//imageexists(n)							: return 1 if the image buffer n exist 0 if empty
int imageexists(int n);

//imagewidth(n)								: return the image n width or error if image n if empty
int imagewidth(int n);

//imageheight(n)							: return the image n height or error if image n if empty
int imageheight(int n);

//deleteimage(n)							: erase the image n of the memory
int deleteimage(int n);

//copyimage(s,d)  							: copy image s to image d
int copyimage(int s,int d);

//setalpha(n,a)								: set trasparency
int setalpha(int n,int a);

//zoomimage(n,zoomx,zoomy)						: zoom image
int zoomimage(int n,double zoomx,double zoomy);

//rotateimage(n,angle)							: rotate image
int rotateimage(int n,double angle);

//rotozoomimage(n,angle,zoom)						: rotate and zoom image
int rotozoomimage(int n,double angle,double zoom);

//mirrorimage(n,x,y)							:vertical-orizontal mirror
int mirrorimage(int n,int x,int y);

//_________________________________________________________________________________________________________________________


// BLITTING

//blt(n,sx,sy,sw,sh,dx,dy)						: copy a part of graphics slot in screen
int blt(int n,int sx,int sy,int sw,int sh,int dx,int dy);

//pastebob(x,y,n)							: copy on screen image n at x,y performing clip
int pastebob(int x,int y,int n);

//pasteicon(x,y,n)							: copy on screen image n at x,y without clipping
int pasteicon(int x,int y,int n);

//grab(n,x,y,w,h)							: grab a a selectarea and copy it in slot n
int grab(int n,int x,int y,int w,int h);
//_________________________________________________________________________________________________________________________

//SPRITE SYSTEM

//spriteclip(x,y,w,h)							: set the visibilty area of sprites
int spriteclip(int x,int y,int w,int h);

//sprite(n,x,y,fr)							: set or move the sprite n at x,y with image fr
int sprite(int n,int x,int y,int fr);

//deletesprite(n)							: unset sprite n
int deletesprite(int n);

//xsprite(n)								: return the x of sprite n
int xsprite(int n);

//ysprite(n)								: return the y of sprite n
int ysprite(int n);

//spritewidth(n)							: return the width of sprite n
int spritewidth(int n);

//spriteheight(n)							: return the height of sprite n
int spriteheight(int n);

//frsprite(n)								: return the frame of sprite n
int frsprite(int n);

//livesprite(n)								: return 1 if sprite n is "live"
int livesprite(int n);

//spritehit(n,x)							: return 1 if sprite n have a collission with sprite x if x=-1 with any
int spritehit(int n,int x);

// spritez(n,z)								: set the zorder position of sprite if z =-1 report actual z position
int spritez(int n,int z);

//lastsprite								: return the last sprite active
int lastsprite();

//autoupdatesprite(m)							: set/ unset automatic sprites update at screenswap
int autoupdatesprite(int m);

//updatesprite								: manual sprites updates at next screenswap
int updatesprite();

//_________________________________________________________________________________________________________________________

//BOB SYSTEM

//setbob(n,scr)								: set bob n at logic screen scr
int setbob(int n,int scr);

//bob(n,x,y,fr)								: set or move bob n at x,y with frame fr
int bob(int n,int x,int y,int fr);

//deletebob(n)								: unset bob n
int deletebob(int n);

//xbob(n)								: return x of bob n
int xbob(int n);

//ybob(n)								: return y of bob n
int ybob(int n);

//bobwidth(n)								: return width of bob n
int bobwidth(int n);

//bobheight(n)								: return height of bob n
int bobheight(int n);

//frbob(n)								: return the frame of bob n
int frbob(int n);

//livebob(n)								: return 1 if bob n is "live"
int livebob(int n);

//bobhit(n,x)								: return 1 if bob n have a collision with bob x if x=-1 with any
int bobhit(int n,int x);

// bobz(n,z)								: set the zorder position of bob if z =-1 report actual z position
int bobz(int n,int z);

//lastbob								: return the last bob active
int lastbob();

//autoupdatebob(m) 							: set/ unset automatic bobs update at screenswap
int autoupdatebob(int m);

//updatebob  								:  manual bobs updates at next screenswap
int updatebob();
//_________________________________________________________________________________________________________________________

// TEXT DRAW

//text(x,y,s,text,option)						: print the text testo  on current screen with s size
int text (int x, int y, int s, char *testo,int option);

//setfont(path)								: select the font
int setfont(char *path);

//getfont()								: get the font selected
char *getfont();

//textrender(text,s,n)							: make an image slot n with the text  write with a current font and size s
int textrender (char *testo,int s,int n,int option);
//_________________________________________________________________________________________________________________________

// PRINT SCREEN

//pen(c)								: set prints color (with -1 parameter return the current color)
int pen(int c);

//paper(c)								: set caractere back color (with -1 parameter return the current color)
int paper(int c);

//fprints(text)								: print a text monospace without cariage return
int fprints(char *testo);

//prints(text)								: print a text monospace
int prints(char *testo);

//locate(x,y)								: move the cursor at x y
int locate(int x,int y);

//atx									: return x of cursor
int atx();

//aty									: return y of cursor
int aty();

//curson								: show the text cursor on screen at(atx,aty)
int curson();

//cursoff								: hide the text cursor
int cursoff();

//inputs(prompt,defs)							: return the string insert to keyboard(default is default text)
int inputS(char *request,char *defs);

//zoneinputs(x,y,l,default)						: return the string insert to keyboard in  x,y coordinates with l lenght
int zoneinputs(int x,int y,int l,char defs[255]);

//_________________________________________________________________________________________________________________________

//SOUND

//isenabledsound()							: return 1 if sdlsound was enabled
int isenabledsound();

//soundexists(n)							: return 1 if the sound buffer n exist 0 if empty
int soundexists(int n);

//deletesound(n)							: delete from memory sound n
int deletesound(int n);

//copysound(s,d)							: copy  sound bank s in sound bank d
int copysound(int s, int d);


//musicexists()								: return 1 if the music is load 0 if empty
int musicexists();


//playsound(n,c,l)							: play the sound n in  channel c l loops
int playsound(int n,int c,int l);

//playfreqsound(n,c,pitch,l)						: play the sound n in  channel c l loops at freq variation (negative number=low positive number =high)
int playfreqsound(int n,int c,float pitch,int l);

//volumesound(c,v)							: change the volume of channel c (-1  = all) at value v (0-128) with v = -1 return the current volume
int volumesound(int c,int v);

//stopsound(c)								: stop the  wave play in channel c (-1  =all)
int stopsound(int c);

//pausesound(c)								: paused channel c (-1  = all)
int pausesound(int c);

//resumesound(c)							: unpaused channel c (-1  = all)
int resumesound(int c);

//vumetersound(c)							: return the current state of sound channel (-1 =all)
int vumetersound(int c);

//positionsound(c,angle,dist)						: position sound in 3d space
int positionsound(int c,int angle,int dist);

//soundchannels(n)							: dinamically change the number of channells managed by sdlBasic
int soundchannels(int n);

//playmusic(n)								: play track xm,mod,ogg,mp3 n=number of ripetition(-1 always)
int playmusic ( int n);

//positionmusic(p)							: move the execution at p second
int positionmusic(int p);

//stopmusic								: terminate the music play
int stopmusic();

//pausemusic								: set pause of the current music
int pausemusic();

//resumemusic								: unset pause of musica
int resumemusic();

//rewindmusic								: rewind at start the music
int rewindmusic();

//fademusic(t)								: music fade
extern int fademusic_t, fademusic_delay;
int fademusic(int t);
void fademusichandler();

//volumemusic(v)							: change the volume of music (0-128) -1 return the current volume
int volumemusic(int v);

//speedmusic(v)								: change the speed of music
int speedmusic(int v);

//_________________________________________________________________________________________________________________________

//CD support

//numdrivescd 				: returns the number of cd-rom drives on the system.
int numdrivescd();

//namecd(drive)				: returns a human-readable, system-dependent identifier for the cd-rom.
int namecd(char *name,int drive);

//getfreecd				: return first free channel Cd
int getfreecd();

//opencd(n,drive)			: opens a cd-rom drive for access.
int opencd(int n, int drive);

//indrivecd(n)				: return 1 if cd is in driver
int indrivecd(int n);

//trackscd(cd) 				: returns the number of tracks in cd.
int trackscd(int n);

//curtrackcd(n)				: return the current track in cd
int curtrackcd(int n);

//curframecd(n)				: return the current frame in cd
int curframecd(int n);

//playcd(n,s,l)				: play a cd
int playcd(int n,int s,int l);

//playtrackscd(n,trk1,fr1,ntrks,nfrs)	: play the given cd track(s)0=all
int playtrackscd(int n,int trk1,int fr1,int ntrks,int nfrs);

//pausecd(n) 				: pauses a cdrom
int pausecd(int n);

//resumecd(n) 				: resumes a cdrom
int resumecd(int n);

//stopcd(n)				: stops a cdrom
int stopcd(int n);

//ejectcd(n) 				: ejects a cdrom
int ejectcd(int n);

//closecd(n)				: closes a cd handle
int closecd(int n);

//tracktypecd(n,t)			: return SDL_AUDIO_TRACK(0...) or SDL_DATA_TRACK(1...)
int tracktypecd(int n,int t);

//tracklengthcd(n,t)			: return the length of track t
int tracklengthcd(int n,int t);

//trackoffsetcd(n,t)			: return the offset to the beginning of this track in frames
int trackoffsetcd(int n,int t);

//_________________________________________________________________________________________________________________________

// VIDEO MPEG
#if defined(VIDEOMPEG_SUPPORT)

//loadmpeg(fname,usesound)		: load a mpeg video
int loadmpeg(char *filename,int useaudio);

//plaympeg(loop)			: play a mpeg1 video
int plaympeg(int loop);

//stopmpeg()				: terminate the video play
int stopmpeg();

//deletempeg()				: unload mpeg video
int deletempeg();

//pausempeg()				: Pause/Resume playback of an SMPEG object
int pausempeg();

//rewindmpeg()				: Rewind the play position of an SMPEG object to the beginning of the MPEG
int rewindmpeg();

//seekmpeg(p)				: Seek 'bytes' bytes in the MPEG stream
int seekmpeg(int p);

//skipmpeg(s)				: Skip 'seconds' seconds in the MPEG stream
int skipmpeg(int s);

//statusmpeg()				: return 1 if plaympeg work or 0 in other case
int statusmpeg();

#endif
//_________________________________________________________________________________________________________________________

// KEYBOARD

//key(keycode)								: return 1 if is press the key keycode
int key (int keycode);

//inkey									: return ascii code of key press
int inkey();

//waitkey(keycode)							: wait a key pression (-1 =any key)
int waitkey(int keycode);

//_________________________________________________________________________________________________________________________

//MOUSE

//xmouse								: return mouse x coordinate on display
int xmouse();

//ymouse								: return mouse y coordinate on display
int ymouse();

//xmousescreen(n)							: return mouse x coordinate on screen
int xmousescreen(int n);

//ymousescreen(n)							: return mouse y coordinate on screen
int ymousescreen(int n);

//bmouse 								: return the buttonclick on the mouse
int bmouse();

//changemouse(n)							: change mouse from default(0) to emulate with sprite 0 - image 0 (1,2,3)
int changemouse(int n);

//locatemouse(x,y)							: move mouse at x y coordinates
int locatemouse(int x, int y);

//mouseshow								: show the mouse cursor
int mouseshow();

//mousehide								: hide the mouse cursor
int mousehide();

//mousezone(x,y,w,h)							: return 1 if the mouse pointer is in rectangle(xy with size wh)
int mousezone(int x,int y,int w,int h);

//_________________________________________________________________________________________________________________________

//JOYSTIK

//numjoysticks 								: Count available joysticks
int numjoysticks();

//namejoystick(i)							: Get joystick name
char *namejoystick(int index);

//numaxesjoystick(i) 							: Get the number of joystick axes
int numaxesjoystick(int index);

//numballsjoystick(i) 							: Get the number of joystick trackballs
int numballsjoystick(int index);

//numhatsjoystick(i) 							: Get the number of joystick hats
int numhatsjoystick(int index);

//numbuttonsjoystick(i) 						: Get the number of joysitck buttons
int numbuttonsjoystick(int index);

//getaxisjoystick(i,a) 							: Get the current state of an axis
int getaxisjoystick(int index,int axis);

//gethatjoystick(i,a) 							: Get the current state of a joystick hat
int gethatjoystick(int index,int hat);

//getbuttonjoystick(i,a)						: Get the current state of a given button on a given joystick
int getbuttonjoystick(int index,int button);

//xgetballjoystick(i,a)							: Get relative x trackball motion
int xgetballjoystick(int index,int ball);

//ygetballjoystick(i,a)							: Get relative y trackball motion
int ygetballjoystick(int index,int ball);

//joy									: return joystick boolean coordinate
int joy(int index);

//bjoy(i)								: return joystick buttons pressed in boolean expression
int bjoy(int index);

//emulate_bjoy								: return emulate joystick buttons in keyboard keys
int emulate_bjoy(int index);

//waitbjoy (joy,jbutton)								: wait the pression of a joystick button (or emulate in keyboard)
int waitbjoy(int joy,int jbutton);

//_________________________________________________________________________________________________________________________

// TIME

//waitTime(t)								: wait t milliseconds
int waitTime(int t);

//timer									: return the current tick
int chrono();
//_________________________________________________________________________________________________________________________

//SOCKET
#if defined(SOCKET_SUPPORT)

//isenabledsock()							: return 1 if sdlnet was enabled
int isenabledsock();

// getfreesock								: return the first free sock in sdlSocket array
int getfreesock();

/* sock=OpenSock(port) 							: Server side socket sock is the stream. in sdlBasic \
									  there are 256 stream and sintax is very similar of \
									  file open close.*/
int opensock(int port);

//clientsock=AcceptSock(serversock)					: Accept the client connection
int acceptsock(int sock);

//IsServerReady(Sock)							: True/False if server is sending data    
int isserverready(int sock);

//sock=ConnectSock(ServerName,port)					: client side socket connection
int connectsock(char *servername,int port);

//ConnectionReadySock(sock)						: the server have accepted the connection
//not implemented

//IsClientReady(Sock)							: True/False if client is sending data
int isclientready(int Sock);

//CloseSock(sock)							: Close the socket connection. Works for client and server
int closesock(int sock);

//PeekSock(Sock, NumBytes)						: Peek information coming from socket, but do not clear.
//not implemented

//ReadSock(Sock, NumBytes)						: Read NumBytes
char * readsock(int sock,int numbytes);

//ReadByteSock(Sock)							: Read a single byte      
//char readbytesock(int sock);
int readbytesock(int sock);

//ReadLineSock(Sock)							: Read complete line
char* readlinesock(int sock);

//WriteSock(Sock, Message, NumBytes)					: Sends NumBytes from Message
int writesock(int sock,char *data,int len);

//WriteByteSock(Sock, Byte)						: Sends a single byte
int writebytesock(int sock,char byte);

//WriteLineSock(Sock, Message)						: Send Message
int writelinesock(int sock,char *message);

//getremoteip(sock)							: return the ip address of remote client connetted
char* getremoteip(int sock);

//getremoteport(sock)							: return the ip address of remote client connetted
int getremoteport(int sock);

//getlocalip()								: return the local ip
char *getlocalip();

#endif
//_________________________________________________________________________________________________________________________

#ifdef __cplusplus
}
#endif

