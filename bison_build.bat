@echo off
@path %PATH%;c:\programmi\gnuwin32\bin
bison -y sdlBrt_tab.y
del y_tab.c
ren y.tab.c y_tab.c
