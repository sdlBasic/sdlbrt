#
# Makefile for installing the Mingw32 version of the SDL library

CWD := $(shell pwd)
CROSS_PATH := /usr/local/cross-tools/i386-mingw32msvc/
SDL_CONFIG := i386-mingw32msvc-sdl-config

all:
	@echo "Type \"make mingw\" to install to /usr/local"
	@echo "Type \"make cross\" to install to $(CROSS_PATH)"

mingw:
	make install-sdl prefix=/usr/local

cygwin:
	@echo "Cygwin installation not yet supported, please install from source."

cross:
	make install-sdl prefix=$(CROSS_PATH)

install-sdl:
	cp -rv bin include lib share $(prefix)/
	@sed -e 's,^prefix=.*,prefix=$(prefix),' <$(prefix)/bin/$(SDL_CONFIG) >$(prefix)/bin/$(SDL_CONFIG).new
	@mv $(prefix)/bin/$(SDL_CONFIG).new $(prefix)/bin/$(SDL_CONFIG)
	@(cd $(prefix)/bin; ln -sf i386-mingw32msvc-sdl-config $(prefix)/bin/sdl-config)

dist:
	@test -d bin || mkdir bin
	@(cd $(CROSS_PATH) && \
		cp -v bin/i386-mingw32msvc-sdl-config bin/SDL.dll $(CWD)/bin/)
	@test -d include || mkdir include
	@(cd $(CROSS_PATH) && \
		cp -av include/SDL $(CWD)/include/)
	@test -d lib || mkdir lib
	@(cd $(CROSS_PATH) && \
		cp -v lib/libSDL.a lib/libSDL.dll.a lib/libSDL.la lib/libSDLmain.a  $(CWD)/lib/)
	@test -d share/aclocal || mkdir -p share/aclocal
	@(cd $(CROSS_PATH) && \
		cp -v share/aclocal/sdl.m4 $(CWD)/share/aclocal)
