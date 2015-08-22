
@echo now compiling sdlBasic: please wait

rem WARNING!!! verify the correct path of mingGw
set MINGWPATH=mingw

@path %MINGWPATH%\bin;%PATH%

rem make.exe cleanall
del ../BASengine/*.o
del ../SDLengine/*.o
del ../sqlite3/*.o
del ../unzip/*.o
del ../*.o
del sdlbrt.exe
make.exe
@echo compilation complete
