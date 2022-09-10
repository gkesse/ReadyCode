@echo off
::===============================================
set "PATH="
set "PATH=C:\Users\tiaka\Downloads\eTools\eBin\winlibs\mingw64\bin;%PATH%"
::===============================================
gcc -c src/main.c -o build/main.o -Isrc/manager
gcc -c src/manager/GHello.c -o build/GHello.o -Isrc/manager
gcc -o bin/main.exe build/main.o build/GHello.o
::===============================================
bin\main.exe
::===============================================
