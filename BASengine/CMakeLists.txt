###############
# (C) 2012 by Matteo Pasotti <matteo.pasotti@gmail.com>
# License: GPLv3
###############


INCLUDE_DIRECTORIES( ${GLIB_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${SDL_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )

SET(CMAKE_CXX_INCLUDE_PATH ${CMAKE_C_INCLUDE_PATH})

link_libraries ( ${SDL_LIBRARY} ${SDLTTF_LIBRARY} ${SDLNET_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLMIXER_LIBRARY} ${GLIB_LIBRARY} ${SMPEG_LIBRARIES} ${M_LIB} SDLengine)

add_library(BASengine STATIC datafunction.c membank.c dir.c file.c strings.c math.c)

