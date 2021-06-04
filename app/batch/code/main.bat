@echo off
::===============================================
set "g_state=init"
set "g_tab=    "
::===============================================
call :Main
goto :eof
::===============================================
:Main
if "%g_state%" == "init" ( call :Init
) else ( if "%g_state%" == "method" ( call :Method
) else ( if "%g_state%" == "choice" ( call :Choice
) else ( if "%g_state%" == "sqlite" ( call :SQLite
) else ( if "%g_state%" == "opencv" ( call :OpenCV
) else ( if "%g_state%" == "quit" ( call :Quit
) else ( goto :eof
))))))
goto :Main
::===============================================
:Init
echo.
echo ADMIN !!!
echo %g_tab%-q : quitter l'application
echo.
set "g_state=method"
goto :Main
::===============================================
:Method
echo ADMIN :
echo %g_tab% 1 : SQLite
echo %g_tab% 2 : OpenCV
echo.
set "g_state=choice"
goto :Main
::===============================================
:Choice
set "lAnswer="
set /p lAnswer="ADMIN ? "
if "%lAnswer%" == "-q" ( set "g_state=end" 
) else ( if "%lAnswer%" == "1" ( set "g_state=sqlite" 
) else ( if "%lAnswer%" == "2" ( set "g_state=opencv"
)))
goto :Main
::===============================================
:SQLite
echo.
echo Execution du module SQLite
set "g_state=quit"
goto :Main
::===============================================
:OpenCV
echo.
echo Execution du module OpenCV
set "g_state=quit"
goto :Main
::===============================================
:Quit
echo.
set "lAnswer="
set /p lAnswer="QUIT ? "
if "%lAnswer%" == "-q" ( set "g_state=end" 
) else ( if "%lAnswer%" == "" ( set "g_state=init" 
) else ( if "%lAnswer%" == "n" ( set "g_state=init"
) else ( if "%lAnswer%" == "o" ( set "g_state=end"
))))
::===============================================
