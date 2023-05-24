@echo off
::===============================================
set "PATH=C:\Users\tiaka\Downloads\eBin\winlibs\mingw64\bin"
::===============================================
gcc -c main.c -o main.o -I.
gcc -o rdvc.exe main.o -L. -lhello
::===============================================
