TARGET= sdlbrt.exe

ifndef prefix
    prefix=c:/windows
endif

exec_prefix=$(prefix)/bin
font_prefix=$(prefix)/share/fonts/ttf

stripped=yes
compressed=no

CC= gcc
CPP=g++
RM=rm
WINDRES=windres
STRIP=strip
COMPRESS=upx

SDL_FLAGS=$(shell sdl-config --cflags)


#CFLAGS = -Wall -g -O2 $(SDL_FLAGS) -DPLAY_MOD -DUNIX  

#LIBS = $(SDL_LIBS) -lSDL_mixer -lSDL_image -lSDL_ttf -lSDL_net -lsmpeg -lsqlite3


CFLAGS =  -Wall -mwindows -g -O3 -Waggressive-loop-optimizations -I$(PREFIX)/include
CFLAGS += -I$(PREFIX)/include/SDL  -Dmain=SDL_main -D_REENTRAT -DPLAY_MOD 

LIBS   = -L$(PREFIX)/lib  -lmingw32 -lSDLmain -lSDL -mwindows -lsmpeg -lSDL_mixer -lSDL_image -lSDL_ttf -lfreetype -lSDL_net -lSDL -lpng -ltiff -lz -ljpeg -lm -lwinmm -ldxguid -lwsock32 -lsqlite3




DEFINES= -DSDLENGINE_SUPPORT -DCD_SUPPORT -DVIDEOMPEG_SUPPORT  -DSOCKET_SUPPORT -DSQLITE_SUPPORT -DMEMORYBANK_SUPPORT

COMPILE=$(CPP) $(CFLAGS)


DEFINES += -Dfont_prefix=\"$(font_prefix)\"

CFLAGS += $(EXTRA_CFLAGS) $(DEFINES)
LIBS += $(EXTRA_LIBS)

SQLITE_SRC=$(wildcard ../sqlite3/*.c)
UNZIP_SRC= $(wildcard ../unzip/*.c)
SDLENGINE_SRC=$(wildcard ../SDLengine/*.c)
BASENGINE_SRC=$(wildcard ../BASengine/*.c)

BAS_SRC=../sdlbrt.c

SRC =  $(UNZIP_SRC) $(SDLENGINE_SRC) $(BASENGINE_SRC) $(BAS_SRC) $(SQLITE_SRC)

OBJECT := $(SRC:%.c=%.o)

#OBJECT :=$(wildcard *.o)
#OBJECT +=$(wildcard unzip/*.o)
#OBJECT +=$(wildcard SDLengine/*.o)
#OBJECT +=$(wildcard BASengine/*.o)
#OBJECT +=$(wildcard sqlite3/*.o)

RC= ../rc.o


all: 		$(TARGET)

$(TARGET):	$(OBJECT) $(RC) 
	$(COMPILE) -o $(TARGET) $^ $(LIBS)
ifeq ($(stripped), yes)
	    $(STRIP) $(TARGET)
endif
ifeq ($(compressed), yes)
	    $(COMPRESS) $(TARGET)
endif



$(OBJECT):		%.o: 	%.c
	$(CC) $(CFLAGS) -c $< -o $@


$(RC):
	$(WINDRES) ../sdlbrt.rc ../rc.o


cleanall:
	$(RM) /f $(OBJECT) 
	$(RM) /rf $(TARGET)
