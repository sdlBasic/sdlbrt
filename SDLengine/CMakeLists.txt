###############
# (C) 2012 by Matteo Pasotti <matteo.pasotti@gmail.com>
# License: GPLv3
###############


#INCLUDE_DIRECTORIES( ${GLIB_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${SDL_INCLUDE_DIR} )

#set ( FONT_PREFIX ${CMAKE_INSTALL_PREFIX}/share/fonts/ttf )
#set ( EXEC_PREFIX ${CMAKE_INSTALL_PREFIX}/bin )
#
#IF (UNIX)
#	add_definitions(-DUNIX=BOOL:1)
#ELSE(UNIX)
#	add_definitions(-DUNIX=BOOL:0)
#ENDIF (UNIX)

#configure_file (
#	"${PROJECT_SOURCE_DIR}/SDLengine/sdlbrtconfig.h.in"
#	"${PROJECT_BINARY_DIR}/SDLengine/sdlbrtconfig.h"
#	)

#include_directories("${PROJECT_BINARY_DIR}")

#add_definitions( -DFONT_PREFIX="${CMAKE_INSTALL_PREFIX}/share/fonts/ttf" )

link_libraries ( ${SDL_LIBRARY} ${SDLTTF_LIBRARY} ${SDLNET_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLMIXER_LIBRARY} ${GLIB_LIBRARY} ${SMPEG_LIBRARIES} ${M_LIB} unzip )

add_library(SDLengine STATIC SDLengine.c common.c SDL_extension.c screen.c graphics.c file_io.c image_manipulation.c blitting.c sprite_system.c bob_system.c text_draw.c print_screen.c sound.c cd_support.c video_mpeg.c keyboard.c joystick.c mouse.c time.c socket.c)
