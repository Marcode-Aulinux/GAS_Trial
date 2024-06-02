@echo off
REM Get the process location
SET mypath=%~dp0
echo Current directory: %mypath:~0,-1%

REM Read first parameter which is a source
set src=%1
REM Read second parameter which is the location where to output built Project
set dest=%2

echo Source: %src%
echo Destination: %dest%

REM Log the full paths for source and destination for verification
echo Full source path: "%mypath:~0,-1%/%src%"
echo Full destination path: "%mypath:~0,-1%/%dest%"

REM Call the UAT tool provided by Unreal which builds a Win64 Project
REM And output its at the destination
echo Building the project...
RunUAT.bat BuildCookRun -project="%mypath:~0,-1%/%src%" -platform=Win64 -clientconfig=DebugGame -build -cook -stage -archive -archivedirectory="%mypath:~0,-1%/%dest%"
if %ERRORLEVEL% neq 0 (
    echo Error: Unreal Automation Tool (UAT) failed with error code %ERRORLEVEL%
    exit /b %ERRORLEVEL%
)

echo UAT Build completed successfully.

REM Zip the build into a publish.zip file
cd "%mypath:~0,-1%/%dest%"
if %ERRORLEVEL% neq 0 (
    echo Error: Failed to change directory to "%mypath:~0,-1%/%dest%"
    exit /b %ERRORLEVEL%
)

echo Current directory for zip: %CD%
powershell Compress-Archive -Path ./* -DestinationPath publish.zip -Force
if %ERRORLEVEL% neq 0 (
    echo Error: Failed to compress the directory into publish.zip
    exit /b %ERRORLEVEL%
)

echo Successfully created publish.zip in "%mypath:~0,-1%/%dest%"
