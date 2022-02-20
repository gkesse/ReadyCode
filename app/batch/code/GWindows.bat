@echo off
::===============================================
call %*
goto :eof
::===============================================
:run
set "lKey=%2"
if "%lKey%" == "activate" ( call :runActivate %*
) else ( if "%lKey%" == "sub" ( call :runActivate %*
))
goto :eof
::===============================================
:runActivate
slmgr /xpr
goto :eof
::===============================================
