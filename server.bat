@echo off

REM Checking if npm is installed by checking its version
call npm -v > nul 2>&1
if %ERRORLEVEL% neq 0 (
    echo Npm was not found in the PATH environment variable.
    echo Please install Node.js ^(which includes npm^) and ensure npm is added to PATH, then try again.
    pause
    exit /b
    exit /b
)

cd /d %~dp0

REM Checking if node_modules folder exists
IF NOT EXIST node_modules (
    echo Dependencies are not installed yet. Starting installation...
    call npm install
)

REM Running the server
echo Starting the server...
node server.js
pause
