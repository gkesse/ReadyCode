@echo off
::===============================================
set "g_state=init"
set "g_tab=    "
::===============================================
call %*
goto :eof
::===============================================
:strlen
setlocal enabledelayedexpansion
:strlenLoop
if not "!%1:~%len%!" == "" ( set /a "len+=1" & goto :strlenLoop )
endlocal & ( set "%2=%len%" )
goto :eof
::===============================================
