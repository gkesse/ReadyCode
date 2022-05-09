@echo off
::===============================================
call %*
goto :eof
::===============================================
:run
set "lKey=%2"
if "%lKey%" == "makecab/help" ( call :runMakecabHelp %*
) else ( if "%lKey%" == "cab/install" ( call :runCabInstall %*
) else ( if "%lKey%" == "cab/create" ( call :runCabCreate %*
)))
goto :eof
::===============================================
:runMakecabHelp
makecab
goto :eof
::===============================================
:runCabInstall
set "lCabPath=path/to/your/CABfile.cab"
dism /online /add-package /packagepath:"%lCabPath%"
goto :eof
::===============================================
:runCabCreate
set "lSourceFile="
set "lCabPath="
makecab %lSourceFile% %lCabPath%
goto :eof
::===============================================
