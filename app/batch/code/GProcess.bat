@echo off
::===============================================
call %*
goto :eof
::===============================================
:run
set "lKey=%1"
if "%lKey%" == "admin/system" ( call :runAdminSystem %*
) else ( if "%lKey%" == "windows" ( call :runWindows %*
) else ( if "%lKey%" == "cab" ( call :runCab %*
) else ( if "%lKey%" == "tuto" ( call :runTuto %*
))))
goto :eof
::===============================================
:runAdminSystem
call GAdmin :run
goto :eof
::===============================================
:runWindows
call GWindows :run %*
goto :eof
::===============================================
:runCab
call GCab :run %*
goto :eof
::===============================================
:runTuto
call GTuto :run %*
goto :eof
::===============================================
