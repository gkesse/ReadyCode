@echo off
::===============================================
set "g_state=init"
set "g_tab=    "
::===============================================
call %*
goto :eof
::===============================================
:run
call :main
goto :eof
::===============================================
:main
if "%g_state%" == "init" ( call :init
) else ( if "%g_state%" == "method" ( call :method
) else ( if "%g_state%" == "choice" ( call :choice
) else ( if "%g_state%" == "sqlite" ( call :sqlite
) else ( if "%g_state%" == "opencv" ( call :opencv
) else ( if "%g_state%" == "quit" ( call :quit
) else ( goto :eof
))))))
goto :main
::===============================================
:init
echo.
echo ADMIN !!!
echo %g_tab%-q : quitter l'application
echo.
set "g_state=method"
goto :main
::===============================================
:method
echo ADMIN :
echo %g_tab% 1 : sqlite
echo %g_tab% 2 : opencv
echo.
set "g_state=choice"
goto :main
::===============================================
:choice
set "lAnswer="
set /p lAnswer="ADMIN ? "
if "%lAnswer%" == "-q" ( set "g_state=end" 
) else ( if "%lAnswer%" == "1" ( set "g_state=sqlite" 
) else ( if "%lAnswer%" == "2" ( set "g_state=opencv"
)))
goto :main
::===============================================
:sqlite
echo.
echo Execution du module sqlite
set "g_state=quit"
goto :main
::===============================================
:opencv
echo.
echo Execution du module opencv
set "g_state=quit"
goto :main
::===============================================
:quit
echo.
set "lAnswer="
set /p lAnswer="QUIT ? "
if "%lAnswer%" == "-q" ( set "g_state=end" 
) else ( if "%lAnswer%" == "" ( set "g_state=init" 
) else ( if "%lAnswer%" == "n" ( set "g_state=init"
) else ( if "%lAnswer%" == "o" ( set "g_state=end"
))))
::===============================================
