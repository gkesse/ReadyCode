@echo off
::===============================================
set "PATH="
set "PATH=C:\Users\tiaka\Downloads\eTools\eBin\winlibs\mingw64\bin;%PATH%"
::===============================================
gcc -c main.c -o main.o
gcc -c GHello.c -o GHello.o
gcc -o main.exe main.o GHello.o
::===============================================
main.exe
::===============================================
