@echo off
::===============================================
set "PATH="
set "PATH=C:\Users\tiaka\Downloads\eBin\winlibs\mingw64\bin"
::===============================================
gcc -c main.c -o main.o
gcc -o readyapp.exe main.o
readyapp.exe
::===============================================
