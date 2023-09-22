@echo off
::===============================================
set "PATH="
set "PATH=C:\Users\tiaka\Downloads\eBin\winlibs\mingw64\bin"
::===============================================
gcc -c main.c -o build/main.o
gcc -o bin/readyapp.exe build/main.o
bin\readyapp.exe
::===============================================
