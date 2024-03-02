@echo off
call vendor\premake\premake5.exe vs2022
IF %ERRORLEVEL% NEQ 0 (
    echo "Error generating projects"
    pause
    exit /b %ERRORLEVEL%
)