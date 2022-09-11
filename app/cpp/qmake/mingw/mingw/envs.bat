@echo off
::===============================================
set "GPROJECT_ROOT=C:\Users\tiaka\Downloads\eTools\ePrograms"
::===============================================
set "PATH=C:\Qt\6.3.1\mingw_64\bin;%PATH%"
set "PATH=C:\Qt\Tools\mingw1120_64\bin;%PATH%"
set "PATH=%GPROJECT_ROOT%\ReadyLib\dev\mingw\bin;%PATH%"
::===============================================
set "GPROJECT_PATH=%GPROJECT_ROOT%\ReadyCode"
set "GPROJECT_MINGW=%GPROJECT_PATH%\app\cpp\qmake\mingw"
set "GPROJECT_SRC=%GPROJECT_MINGW%\code\src"
set "GPROJECT_DATA=%GPROJECT_SRC%\data"
set "GPROJECT_TMP=%GPROJECT_DATA%\tmp"
::===============================================
set "GPROJECT_ENV=TEST"
::===============================================
set "GGIT_URL=https://github.com/gkesse/ReadyCode.git"
set "GGIT_NAME=ReadyCode"
::===============================================
