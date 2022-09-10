@echo off
::===============================================
set "PATH="
set "PATH=C:\Users\tiaka\Downloads\eTools\eBin\winlibs\mingw64\bin;%PATH%"
::===============================================
g++ -c main.cpp -o main.o
g++ -c GHello.cpp -o GHello.o
g++ -o main.exe main.o GHello.o
::===============================================
main.exe
::===============================================
