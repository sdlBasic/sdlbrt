TARGET= sdlbrt

ifndef prefix
    prefix=/usr
endif

exec_prefix=$(prefix)/bin
font_prefix=$(prefix)/share/fonts/ttf

stripped=yes
compress=no

CC= gcc
CPP=g++
INSTALL=/usr/bin/install
RM=rm
STRIP=strip

SDL_FLAGS=$(shell sdl-config --cflags)

SDL_LIBS=$(shell sdl-config --libs)

CFLAGS = -Wall -g -O3 $(SDL_FLAGS) -DPLAY_MOD -DUNIX  

LIBS = $(SDL_LIBS) -lSDL_mixer -lSDL_image -lSDL_ttf -lSDL_net -lsmpeg -lsqlite3

DEFINES= -DSDLENGINE_SUPPORT -DCD_SUPPORT -DVIDEOMPEG_SUPPORT  -DSOCKET_SUPPORT -DSQLITE_SUPPORT -DMEMORYBANK_SUPPORT

COMPILE=$(CPP) $(CFLAGS)


DEFINES += -Dfont_prefix=\"$(font_prefix)\"

CFLAGS += $(EXTRA_CFLAGS) $(DEFINES)
LIBS += $(EXTRA_LIBS)

SQLITE_SRC=$(wildcard sqlite3/*.c)
UNZIP_SRC= $(wildcard unzip/*.c)
SDLENGINE_SRC=$(wildcard SDLengine/*.c)
BASENGINE_SRC=$(wildcard BASengine/*.c)

BAS_SRC=sdlbrt.c

SRC =  $(UNZIP_SRC) $(SDLENGINE_SRC) $(BASENGINE_SRC) $(BAS_SRC) $(SQLITE_SRC)

OBJECT := $(SRC:%.c=%.o)

#OBJECT :=$(wildcard *.o)
#OBJECT +=$(wildcard unzip/*.o)
#OBJECT +=$(wildcard SDLengine/*.o)
#OBJECT +=$(wildcard BASengine/*.o)
#OBJECT +=$(wildcard sqlite3/*.o)



all: 		$(TARGET)

$(TARGET):	$(OBJECT) $(RC) 
	$(COMPILE) -o $(TARGET) $^ $(LIBS)
ifeq ($(stripped), yes)
	    $(STRIP) $(TARGET)
endif



$(OBJECT):		%.o: 	%.c
	$(CC) $(CFLAGS) -c $< -o $@


#sdlbrt.o:	sdlbrt.rc
	#$(WINDRES) sdlbrt.rc sdlbrt.o


cleanall:
	$(RM) -f $(OBJECT) 
	$(RM) -rf $(TARGET)
