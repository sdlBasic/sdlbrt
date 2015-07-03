
CROSS=open2x-

SDK    = /opt/cross-tools/open2x
PREFIX = $(SDK)/open2x

OPATH := $(PATH)
PATH  := $(OPATH):$(SDK)/bin

prefix=$(PREFIX)

exec_prefix=$(prefix)/bin
font_prefix=/mnt/sd/sdlbasic/share/fonts/ttf

stripped=yes
compress=no

CC= $(CROSS)gcc
CPP= $(CROSS)g++
LD= $(CROSS)ld
NM= $(CROSS)nm
STRIP= $(CROSS)strip
AS= $(CROSS)as

INSTALL=/usr/bin/install
RM=rm

CFLAGS = -O3 -ffast-math -fomit-frame-pointer -mcpu=arm920t -static
CFLAGS += -I$(PREFIX)/include/SDL -D_REENTRAT -DPLAY_MOD -DUNIX -DGP2X -DBOBHIT_ISO

LIBS   = -L$(PREFIX)/lib  -lsmpeg -lSDL_mixer -lSDL_image -lSDL_ttf -lfreetype -lSDL_net -lSDL -lpng -ltiff -lz -ljpeg -lm -lpthread -lsqlite3

DEFINES= -DSDLENGINE_SUPPORT -DSOCKET_SUPPORT -DVIDEOMPEG_SUPPORT -DSQLITE_SUPPORT -DMEMORYBANK_SUPPORT
