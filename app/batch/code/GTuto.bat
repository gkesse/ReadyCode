@echo off
::===============================================
set "g_state=init"
set "g_tab=    "
::===============================================
call %*
goto :eof
::===============================================
:run
set "lKey=%2"
if "%lKey%" == "add" ( call :runAdd %*
) else ( if "%lKey%" == "sub" ( call :runSub %*
) else ( if "%lKey%" == "mul" ( call :runMul %*
) else ( if "%lKey%" == "div" ( call :runDiv %*
) else ( if "%lKey%" == "mod" ( call :runMod %*
) else ( if "%lKey%" == "arg/read" ( call :runArgRead un deux trois
) else ( if "%lKey%" == "var/show" ( call :runVarShow
) else ( if "%lKey%" == "var/global" ( call :runVarGlobalLocal
) else ( if "%lKey%" == "var/local" ( call :runVarGlobalLocal
) else ( if "%lKey%" == "env/read" ( call :runEnvRead
) else ( if "%lKey%" == "str/empty" ( call :runStrEmpty
) else ( if "%lKey%" == "str/concat" ( call :runStrConcat
) else ( if "%lKey%" == "str/len" ( call :runStrLen
) else ( if "%lKey%" == "str/int" ( call :runStrInt
) else ( if "%lKey%" == "str/skip" ( call :runStrSkip
) else ( if "%lKey%" == "str/skipn" ( call :runStrSkipN
) else ( if "%lKey%" == "str/skipk" ( call :runStrSkipKeep
) else ( if "%lKey%" == "str/skipkpn" ( call :runStrSkipKeepPN
) else ( if "%lKey%" == "str/skipknp" ( call :runStrSkipKeepNP
) else ( if "%lKey%" == "str/skipknn" ( call :runStrSkipKeepNN
) else ( if "%lKey%" == "str/alignl" ( call :runStrAlignLeft
) else ( if "%lKey%" == "str/alignr" ( call :runStrAlignRight
))))))))))))))))))))))
goto :eof
::===============================================
:runAdd
SET /a "a = 5"
SET /a "b = 10" 
SET /a "c = %a% + %b%" 
echo %a% + %b% = %c%
goto :eof
::===============================================
:runSub
SET /a "a = 5"
SET /a "b = 10" 
SET /a "c = %a% - %b%" 
echo %a% - %b% = %c%
goto :eof
::===============================================
:runMul
SET /a "a = 5"
SET /a "b = 10" 
SET /a "c = %a% * %b%" 
echo %a% * %b% = %c%
goto :eof
::===============================================
:runDiv
SET /A "a = 3"
SET /A "b = 10" 
SET /A "c = %b% / %a%" 
echo %b% / %a% = %c%
goto :eof
::===============================================
:runMod
SET /a "a = 4"
SET /a "b = 10" 
SET /a "c = %b% %% %a%" 
echo %b% %% %a% = %c%
goto :eof
::===============================================
:runArgRead
echo %1
echo %2
echo %3
goto :eof
::===============================================
:runVarShow
set "message=Bonjour tout le monde"
echo %message%
goto :eof
::===============================================
:runVarGlobalLocal
set "gVar=1000"
setlocal
set "lVar=500"
echo lVar = %lVar%
echo gVar = %gVar%
endlocal
echo lVar = %lVar%
echo gVar = %gVar%
goto :eof
::===============================================
:runEnvRead
echo %JAVA_HOME%
goto :eof
::===============================================
:runStrEmpty
set "a="
echo a = [%a%]
goto :eof
::===============================================
:runStrConcat
set "a=Bonjour"
set "b=tout le monde"
set "c=%a% %b%"
echo %c%
goto :eof
::===============================================
:runStrLen
set "a=Bonjour tout le monde"
call GString :strlen a b
echo strlen(%a%) = %b%
goto :eof
::===============================================
:runStrInt
set "a=1000"
set /a "b=%a%"
echo "%a%" = %b%
goto :eof
::===============================================
:runStrSkip
set "a=Bonjour"
set "b=%a:~1%"
echo skip(%a%, 1) = %b%
goto :eof
::===============================================
:runStrSkipN
set "a=Bonjour"
set "b=%a:~-3%"
echo skipN(%a%, -3) = %b%
goto :eof
::===============================================
:runStrSkipKeep
set "a=Bonjour"
set "b=%a:~1,3%"
echo skipKeep(%a%, 1, 3) = %b%
goto :eof
::===============================================
:runStrSkipKeepPN
set "a=Bonjour"
set "b=%a:~1,-1%"
echo skipKeepPN(%a%, 1, -1) = %b%
goto :eof
::===============================================
:runStrSkipKeepNP
set "a=Bonjour"
set "b=%a:~-4,3%"
echo skipKeepNP(%a%, -4, 3) = %b%
goto :eof
::===============================================
:runStrSkipKeepNN
set "a=Bonjour"
set "b=%a:~-4,-1%"
echo skipKeepNP(%a%, -4, -1) = %b%
goto :eof
::===============================================
:runStrAlignRight
set "x=1000"
set "y= 1"
set "y= %y%"
echo %x% 
set "y=%y:~-5%"
echo %y%
goto :eof
::===============================================
