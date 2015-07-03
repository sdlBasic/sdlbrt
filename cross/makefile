#############################################################################
#  sdlbasic Makefile v1.07 for all  		                            #
#############################################################################
#
# syntax make OS=<targetplatform>
# [stripped=<yes/no>][compress=<no|gexe|upx>] [command]
#
################################################################################

# os is case insensitive

os=default
ifndef $(OS)
OS=$(os)
endif


TARGETEXE=sdlbrt

COMPILE=$(CPP) $(CFLAGS)

include cross/$(OS).mk

DEFINES += -Dfont_prefix=\"$(font_prefix)\"


CFLAGS += $(EXTRA_CFLAGS) $(DEFINES)
LIBS += $(EXTRA_LIBS)


STAGE    := ..
STAGEOS  := $(STAGE)/$(OS)
STAGEBIN := $(STAGEOS)/bin


TARGET=$(STAGEBIN)/$(TARGETEXE)

SQLITE_SRC=$(wildcard sqlite3/*.c)
UNZIP_SRC= $(wildcard unzip/*.c)
SDLENGINE_SRC=$(wildcard SDLengine/*.c)
BASENGINE_SRC=$(wildcard BASengine/*.c)

BAS_SRC=sdlbrt.c

SRC =  $(UNZIP_SRC) $(SDLENGINE_SRC) $(BASENGINE_SRC) $(BAS_SRC) $(SQLITE_SRC)

OBJECT := $(SRC:%.c=%-$(OS).o)

CROSSOBJECT :=$(wildcard *.o)
CROSSOBJECT +=$(wildcard unzip/*.o)
CROSSOBJECT +=$(wildcard SDLengine/*.o)
CROSSOBJECT +=$(wildcard BASengine/*.o)
CROSSOBJECT +=$(wildcard sqlite3/*.o)



all: 		$(TARGET)

$(TARGET):	$(OBJECT) $(RC) 
	mkdir -p $(STAGEBIN)
	cp -ru share $(STAGEOS)
	$(COMPILE) -o $(TARGET) $^ $(LIBS)
ifeq ($(stripped), yes)
	    $(STRIP) $(TARGET)
endif



$(OBJECT):		%-$(OS).o: 	%.c
	$(CC) $(CFLAGS) -c $< -o $@


sdlbrt.o:	sdlbrt.rc
	$(WINDRES) sdlbrt.rc sdlbrt.o


clean:
	$(RM) -f $(OBJECT) $(EXTRA_GEN)

cleanall:
	$(RM) -f $(CROSSOBJECT) $(EXTRA_GEN)
	$(RM) -rf $(STAGEOS)


