@echo off
::===============================================
set "PATH="
set "PATH=C:\Users\tiaka\Downloads\eTools\eBin\winlibs\mingw64\bin;%PATH%"
::===============================================
g++ -c main.cpp -o main.o
g++ -o main.exe main.o
::===============================================
main.exe
::===============================================
