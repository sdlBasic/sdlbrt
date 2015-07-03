/*
_________________________________________________________________________________________________________________________

    BASengine core of sdlBasic

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

//- datafunction ---------------------------------------------------------------------------------

extern char *dataarray[10000];
extern int dataenter,datapointer;

void init_data();
void loaddata(char *datavalue);
char *readdata();
//--------------------------------------------------------------------------------------------------

//- dir --------------------------------------------------------------------------------------------

#define LVLDIR 8

#if defined(UNIX) || defined(__MORPHOS__) || defined(__amigaos4__)
	#include <unistd.h>
	#include <dirent.h>
	extern DIR *hDir[LVLDIR];
	extern struct dirent *s_file[LVLDIR];
#else
	#include <direct.h>
	#include <io.h>
	extern struct _finddata_t c_file[LVLDIR];
	extern struct _finddata_t c_dir;
	extern long n_file[LVLDIR];
#endif


extern char dir_path[255];
extern char ext[LVLDIR][1024];
extern char prefix[LVLDIR][1024];
extern int lvldir;

extern char *dir();
extern char *dirfirst(char *path);
extern char *dirnext();
extern int direxists(char *path);
extern int isdir(char *path);
//--------------------------------------------------------------------------------------------------

//- file -------------------------------------------------------------------------------------------

#define FILE_MODE_INPUT     0
#define FILE_MODE_OUTPUT    1
#define FILE_MODE_APPEND    2
#define FILE_MAX_HANDLE     16
#define FILE_BUFFER_MAX     1024

/* handles are 1 relative */
extern FILE    *fileHandles[FILE_MAX_HANDLE+1];
extern int     fileMode[FILE_MAX_HANDLE+1];

extern void fileCheckHandle( int handle, int mustBeOpen );
extern int fileFree(void);
extern void fileOpen( char *name, int mode, int handle );
extern void fileClose( int handle );
extern void fileCloseAll(void);
extern char *fileLineInput( int handle );
extern void filePrintString( int handle, char *text );
extern int fileEof( int handle );
extern int fileReadByte( int handle );
extern void fileWriteByte( int handle, char c );
extern long fileSeek( int handle, long pos );
extern long fileSize( int handle );
extern long filePosition( int handle );
extern int FileExists( char *name );

extern int filecopy(char *source,char *dest);
extern int filemove(char *source,char *dest);
extern int filerename(char *source,char *dest);
//--------------------------------------------------------------------------------------------------

//- strings ----------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

//STRINGS RUTINES
int asc(char *string);
char *chr(int v);
void format();
char *insert(char *source, char *target,int position);
int instr(int start,char *find, char *search);
char *lcase(char *string);
char *left(char *string,int pos);
int len(char *string);
char *ltrim(char *string);
char *mid(char *string,int i,int n);
char *replace(char *src,char *rep, int i);
char *replacesubstr(int start,char *source,char *replace, char *with);
char *reverse(char *string);
char *right(char *string,int pos);
int rinstr(char *search,char *find,int start);
char *rtrim(char *string);
char *space(int n);
char *str(int v);
char *string(int n, char *string);
int tally(char *src,char *sub,int start);
char *trim( char *string);
char *ucase(char *string);
double val(char *string);


#ifdef __cplusplus
}
#endif
//--------------------------------------------------------------------------------------------------

//-- membank ---------------------------------------------------------------------------------------
#define NUM_MEMBANKS 255

extern char *membank[NUM_MEMBANKS];
extern int banksize[NUM_MEMBANKS];
extern int curbank;

/*----- Error system ---*/
extern char *error_description;
extern int error_type;

//--Internal ---------------------------------------------------
extern void init_membank();

//--Base ---------------------------------------------------
extern int reservebank(int bank,int size);
extern int baseimage(int bank,int n);
extern int baseimageCC(int bank,int n);
extern int basescreen(int bank,int n);
extern int basesound(int bank,int n);

extern int freebase(int bank);
extern int freebank(int bank);
extern int copybank(int s,int d);
extern int loadbank(char *filename,int bank);
extern int savebank(char *filename,int bank);

extern int setbank(int bank);
extern int sizebank(int bank);

//--poke ---------------------------------------------------
extern int poke(int bank,int address,unsigned char byte);
extern int doke(int bank,int address,unsigned short byte);
extern int loke(int bank,int address,unsigned int byte);

//--peek ---------------------------------------------------
extern int peek(int bank,int address);
extern int deek(int bank,int address);
extern int leek(int bank,int address);

//--fastcopy ---------------------------------------------------
extern int memcopy(int sbank,int s ,int dbank,int d,int size);
//--------------------------------------------------------------------------------------------------

//- math -------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

char *bin(int i);
char *hex(int i);
void randomize(int seed);
double rnd(int upper);
double round(double n1);
int sgn(double  n);
double Min( double a, double b );
double Max( double a, double b );
int bitwiseand(int a, int b);
int bitwiseor(int a, int b);
int bitwisexor(int a, int b);

#ifdef __cplusplus
}
#endif

//--------------------------------------------------------------------------------------------------
