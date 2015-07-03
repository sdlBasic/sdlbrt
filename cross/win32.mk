

CROSS=i386-mingw32msvc
SDK    = /opt/cross-tools/mingw
#CROSS=i386-mingw32msvc
#SDK    = /opt/cross-tools/mingw-old

PREFIX = $(SDK)/$(CROSS)

OPATH := $(PATH)
PATH  := $(OPATH):$(SDK)/bin

prefix=$(PREFIX)

exec_prefix=$(prefix)/bin
font_prefix=$(prefix)/share/fonts/ttf

stripped=yes
compress=no

CC= $(CROSS)-gcc
CPP= $(CROSS)-g++
LD= $(CROSS)-ld
NM= $(CROSS)-nm
STRIP= $(CROSS)-strip
WINDRES=$(CROSS)-windres
AS= $(CROSS)-as

TARGETEXE=sdlbrt.exe
RC=sdlbrt.o

INSTALL=/usr/bin/install
RM=rm

CFLAGS =  -Wall -mwindows -g -O2 -static -I$(PREFIX)/include
CFLAGS += -I$(PREFIX)/include/SDL  -Dmain=SDL_main -D_REENTRAT -DPLAY_MOD

LIBS   = -L$(PREFIX)/lib  -lmingw32 -lSDLmain -mwindows -lsmpeg -lSDL_mixer -lSDL_image -lSDL_ttf -lfreetype -lSDL_net -lSDL -lpng -ltiff -lz -ljpeg -lm -lwinmm -ldxguid -lwsock32 -lsqlite3 


DEFINES= -DSDLENGINE_SUPPORT -DCD_SUPPORT -DVIDEOMPEG_SUPPORT -DSOCKET_SUPPORT -DSQLITE_SUPPORT -DMEMORYBANK_SUPPORT
