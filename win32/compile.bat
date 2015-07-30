
@echo now compiling sdlBasic: please wait

rem WARNING!!! verify the correct path of mingGw
set MINGWPATH=mingw

@path %MINGWPATH%\bin;%PATH%

make.exe cleanall
make.exe
@echo compilation complete
