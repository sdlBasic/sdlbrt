###############
# (C) 2012 by Matteo Pasotti <matteo.pasotti@gmail.com>
# License: GPLv3
###############


INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )

SET(CMAKE_CXX_INCLUDE_PATH ${CMAKE_C_INCLUDE_PATH})

add_library(sqlite3 STATIC wrap.c)

