@echo off
::===============================================
set "PATH="
set "PATH=C:\Users\tiaka\Downloads\eTools\eBin\winlibs\mingw64\bin;%PATH%"
::===============================================
g++ -c src/main.cpp -o build/main.o -Isrc/manager
g++ -c src/manager/GHello.cpp -o build/GHello.o -Isrc/manager
g++ -o bin/main.exe build/main.o build/GHello.o
::===============================================
bin\main.exe
::===============================================
